#ifndef __I2C_H
#define __I2C_H

#define OLED_I2C_SDA_Pin         GPIO_Pin_11
#define OLED_I2C_SDA_GPIO        GPIOB
#define OLED_I2C_SDA_GPIO_CLK    RCC_APB2Periph_GPIOB

#define OLED_I2C_SCL_Pin         GPIO_Pin_10
#define OLED_I2C_SCL_GPIO        GPIOB
#define OLED_I2C_SCL_GPIO_CLK    RCC_APB2Periph_GPIOB

void OLED_I2C_Init(void);

void OLED_I2C_SDA_High(void);
void OLED_I2C_SDA_Low(void);

void OLED_I2C_SCL_High(void);
void OLED_I2C_SCL_Low(void);

#endif