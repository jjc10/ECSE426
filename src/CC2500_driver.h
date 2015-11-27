#include "stm32f4xx.h"                  // Device header
//#include "stm32f4xx_conf.h"


#define CC2500_IOCFG2		0x00
#define CC2500_IOCFG1		0x01
#define CC2500_IOCFG0		0x02
#define CC2500_FIFOTHR	0x03
#define CC2500_SYNC1		0x04
#define CC2500_SYNC0		0x05
#define CC2500_PKTLEN		0x06
#define CC2500_PKTCTRL1	0x07
#define CC2500_PKTCTRL0	0x08
#define CC2500_ADDR 		0x09
#define CC2500_CHANNR		0x0A
#define CC2500_FSCTRL1	0x0B
#define CC2500_FSCTRL0	0x0C
#define CC2500_FREQ2		0x0D
#define CC2500_FREQ1 		0x0E
#define CC2500_FREQ0		0x0F
// CC2500_Write()

#define CC2500_MDMCFG4	0x10
#define CC2500_MDMCFG3	0x11
#define CC2500_MDMCFG2	0x12
#define CC2500_MDMCFG1	0x13
#define CC2500_MDMCFG0	0x14
#define CC2500_DEVIATN	0x15
#define CC2500_MCSM2		0x16
#define CC2500_MCSM1		0x17
#define CC2500_MCSM0		0x18
#define CC2500_FOCCFG		0x19
#define CC2500_BSCFG		0x1A 
#define CC2500_AGCTRL2 	0x1B
#define CC2500_AGCTRL1 	0x1C
#define CC2500_AGCTRL0 0x1D
#define CC2500_WOREVT1 0x1E
#define CC2500_WOREVT0 0x1F

#define	CC2500_WORCTRL	0x20
#define	CC2500_FREND1	0x21
#define	CC2500_FREND0	0x22
#define	CC2500_FSCAL3	0x23
#define	CC2500_FSCAL2	0x24
#define	CC2500_FSCAL1	0x25
#define	CC2500_FSCAL0	0x26
#define	CC2500_RCCTRL1	0x27
#define	CC2500_RCCTRL0	0x28
#define	CC2500_FSTEST	0x29
#define	CC2500_PTEST	0x2A
#define	CC2500_AGCTEST	0x2B
#define	CC2500_TEST2	0x2C
#define	CC2500_TEST1	0x2D
#define	CC2500_TEST0	0x2E

#define	CC2500_PARTNUM	0x30
#define	CC2500_VERSION	0x31
#define	CC2500_FREQEST	0x32
#define	CC2500_LQI	0x33
#define	CC2500_RSSI	0x34
#define	CC2500_MARCSTATE	0x35
#define	CC2500_WORTIME1	0x36
#define	CC2500_WORTIME0	0x37
#define	CC2500_PKTSTATUS	0x38
#define	CC2500_VCO_VC_DAC	0x39
#define	CC2500_TXBYTES	0x3A
#define	CC2500_RXBYTES	0x3B
#define	CC2500_RCCTRL1_STATUS	0x3C
#define	CC2500_RCCTRL0_STATUS	0x3D

#define	CC2500_SRES 0x30
#define	CC2500_SFSTXON 0x31
#define	CC2500_SXOFF 0x32
#define	CC2500_SCAL 0x33
#define	CC2500_SRX 0x34
#define	CC2500_STX 0x35
#define	CC2500_SIDL 0x36
#define	CC2500_SWOR 0x38
#define	CC2500_SPWD 0x39
#define	CC2500_SFRX 0x3A
#define	CC2500_SFTX 0x3B
#define	CC2500_SWORRST 0x3C
#define	CC2500_SNOP 0x3D
#define	CC2500_PATABLE 0x3E
#define	CC2500_FIFO 0x3F


// CONFIGURATION VALUES



/**
  * @brief  CC2500 Register settings
  */
#define VAL_CC2500_IOCFG2 	0x29 		
#define VAL_CC2500_IOCFG0 	0x06	

#define VAL_CC2500_FIFOTHR 	0x07

#define VAL_CC2500_PKTLEN 	0x01

#define VAL_CC2500_PKTCTRL1 0x08	
#define VAL_CC2500_PKTCTRL0 0x04	

#define VAL_CC2500_ADDR 		0x00	

#define VAL_CC2500_CHANNR 	0x00

//#define VAL_CC2500_FSCTRL1 	0x0C	// offset
#define VAL_CC2500_FSCTRL1 	0x0C
#define VAL_CC2500_FSCTRL0 	0x00	

// freq set to 2.433 GHz, note f_xosc = 26MHz. Divide by 100 to get in GHz
#define VAL_CC2500_FREQ2 		0x5D	//x5D --> 5D
#define VAL_CC2500_FREQ1 		0x93	// 94 --> 94
#define VAL_CC2500_FREQ0 		0xC5	// x02 --> DF

/*
#define VAL_CC2500_FREQ2 		0x5D	//x5D --> 5D
#define VAL_CC2500_FREQ1 		0x94	// 94 --> 94
#define VAL_CC2500_FREQ0 		0x02	// x02 --> DF
*/
#define VAL_CC2500_MDMCFG4 	0x0E
#define VAL_CC2500_MDMCFG3 	0x3B
#define VAL_CC2500_MDMCFG2 	0x73	
#define VAL_CC2500_MDMCFG1 	0x42	
#define VAL_CC2500_MDMCFG0 	0xF8	

#define VAL_CC2500_DEVIATN 	0x00	


#define VAL_CC2500_MCSM1 		0x02	
#define VAL_CC2500_MCSM0 		0x18	

#define VAL_CC2500_FOCCFG 	0x1D	
#define VAL_CC2500_BSCFG 		0x1C	

#define VAL_CC2500_AGCTRL2 	0xC7	 
#define VAL_CC2500_AGCTRL1 	0x40	
#define VAL_CC2500_AGCTRL0 	0xB0

#define VAL_CC2500_FREND1 	0xB6	 
#define VAL_CC2500_FREND0 	0x10	

#define VAL_CC2500_FSCAL3 	0xEA	 
#define VAL_CC2500_FSCAL2 	0x0A	
#define VAL_CC2500_FSCAL1 	0x00	 
#define VAL_CC2500_FSCAL0 	0x19	

#define VAL_CC2500_FSTEST 	0x59

#define VAL_CC2500_TEST2 		0x88	
#define VAL_CC2500_TEST1 		0x31	
#define VAL_CC2500_TEST0 		0x0B	
	
	



/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define CC2500_FLAG_TIMEOUT         ((uint32_t)0x1000)

/**
  * @brief  CC2500 SPI Interface pins
  */
#define CC2500_SPI                       SPI4
#define CC2500_SPI_CLK                   RCC_APB2Periph_SPI4

#define CC2500_SPI_SCK_PIN               GPIO_Pin_2                  /* PA.05 */
#define CC2500_SPI_SCK_GPIO_PORT         GPIOE                       /* GPIOA */
#define CC2500_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOE
#define CC2500_SPI_SCK_SOURCE            GPIO_PinSource2
#define CC2500_SPI_SCK_AF                GPIO_AF_SPI4

#define CC2500_SPI_MISO_PIN              GPIO_Pin_5                  /* PA.6 */
#define CC2500_SPI_MISO_GPIO_PORT        GPIOE                       /* GPIOA */
#define CC2500_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define CC2500_SPI_MISO_SOURCE           GPIO_PinSource5
#define CC2500_SPI_MISO_AF               GPIO_AF_SPI4

#define CC2500_SPI_MOSI_PIN              GPIO_Pin_6                  /* PA.7 */
#define CC2500_SPI_MOSI_GPIO_PORT        GPIOE                       /* GPIOA */
#define CC2500_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define CC2500_SPI_MOSI_SOURCE           GPIO_PinSource6
#define CC2500_SPI_MOSI_AF               GPIO_AF_SPI4

#define CC2500_SPI_CS_PIN                GPIO_Pin_3                  /* PE.03 */
#define CC2500_SPI_CS_GPIO_PORT          GPIOE                       /* GPIOE */
#define CC2500_SPI_CS_GPIO_CLK           RCC_AHB1Periph_GPIOE

#define CC2500_SPI_INT1_PIN              GPIO_Pin_4                  /* PE.00 */
#define CC2500_SPI_INT1_GPIO_PORT        GPIOE                       /* GPIOE */
#define CC2500_SPI_INT1_GPIO_CLK         RCC_AHB1Periph_GPIOE
#define CC2500_SPI_INT1_EXTI_LINE        EXTI_Line4
#define CC2500_SPI_INT1_EXTI_PORT_SOURCE EXTI_PortSourceGPIOE
#define CC2500_SPI_INT1_EXTI_PIN_SOURCE  EXTI_PinSource4
#define CC2500_SPI_INT1_EXTI_IRQn        EXTI4_IRQn 


#define CC2500_CS_LOW()       GPIO_ResetBits(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_PIN)
#define CC2500_CS_HIGH()      GPIO_SetBits(CC2500_SPI_CS_GPIO_PORT, CC2500_SPI_CS_PIN)


/* Read/Write command */
#define READWRITE_CMD              ((uint8_t)0x80) 
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                 ((uint8_t)0x00)
 
static uint8_t CC2500_SendByte(uint8_t byte);
void CC2500_LowLevel_Init(void);
void CC2500_Read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
uint32_t CC2500_TIMEOUT_UserCallback(void);
void CC2500_Write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);

void config_wireless();
// int val = VAL_CC2500_IOCFG2;
//CC2500_Write(&val, )

