#include <stdint.h>
#include "stm32l4xx_hal.h"

#define HMC_ADDR8        (0x1E << 1)
#define HMC_REG_CRA      0x00
#define HMC_REG_CRB      0x01
#define HMC_REG_MODE     0x02
#define HMC_REG_OUT_X_M  0x03
#define HMC_REG_IDA      0x0A

extern I2C_HandleTypeDef hi2c2;
extern float Mx, My, Mz; // in gauss (scaled)