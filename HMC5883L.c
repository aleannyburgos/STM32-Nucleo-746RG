#include "HMC5883L.h"
float Mx, My, Mz;


//returns status of write/read operation
static HAL_StatusTypeDef hmc_write(uint8_t reg, uint8_t v){
  return HAL_I2C_Mem_Write(&hi2c2, HMC_ADDR8, reg, I2C_MEMADD_SIZE_8BIT, &v, 1, 100);
}
static HAL_StatusTypeDef hmc_read(uint8_t reg, uint8_t *buf, uint16_t n){
  return HAL_I2C_Mem_Read(&hi2c2, HMC_ADDR8, reg, I2C_MEMADD_SIZE_8BIT, buf, n, 100);
}


// here we set the config registers and mode
HAL_StatusTypeDef HMC_Init(void){
  uint8_t id[3];
  if (hmc_read(HMC_REG_IDA, id, 3) != HAL_OK) return HAL_ERROR;

  //for setting the data output rate and measurement configuration. These are set to default.
  if (hmc_write(HMC_REG_CRA,  0x70) != HAL_OK) return HAL_ERROR;// configure: 8x avg, 15Hz
  if (hmc_write(HMC_REG_CRB,  0x20) != HAL_OK) return HAL_ERROR;// gain = 1.3Ga
  if (hmc_write(HMC_REG_MODE, 0x00) != HAL_OK) return HAL_ERROR;//continuous measurement mode
  return HAL_OK;
}

HAL_StatusTypeDef HMC_ReadGauss(void){
  uint8_t b[6];
  if (hmc_read(HMC_REG_OUT_X_M, b, 6) != HAL_OK) return HAL_ERROR;
  int16_t x = (int16_t)((b[0]<<8) | b[1]);
  int16_t z = (int16_t)((b[2]<<8) | b[3]);
  int16_t y = (int16_t)((b[4]<<8) | b[5]);
  const float lsb_per_gauss = 1090.0f; // for CRB=0x20
  Mx = x / lsb_per_gauss;
  My = y / lsb_per_gauss;
  Mz = z / lsb_per_gauss;
  return HAL_OK;
}