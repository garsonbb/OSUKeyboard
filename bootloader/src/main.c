/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Device Firmware Upgrade(DFU) demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/

#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "dfu_mal.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;

__IO uint8_t PrevXferComplete = 1;


void Stm32_Clock_Init(u8 PLL)

{
    unsigned char temp=0;
    RCC_DeInit();		
    RCC->CR|=0x00000001;  //�ڲ�����ʱ��ʹ��HSION
    while(!(RCC->CR>>1));//�ȴ��ڲ�ʱ�Ӿ���
    RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
    PLL-=2;//����2����λ
    RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
    RCC->CFGR|=0<<16;	  //PLLSRC ON  HSI��2��Ƶ����ΪPLL����ʱ��
    FLASH->ACR|=0x32;	  //FLASH 2����ʱ����
    RCC->CR|=0x01000000;  //PLLON
    while(!(RCC->CR>>25));//�ȴ�PLL����
    RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��
    while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
    {
    temp=RCC->CFGR>>2;
    temp&=0x03;
    }
}



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
	Stm32_Clock_Init(12);
 
	DFU_Button_Config();
  
  if (DFU_Button_Read() != 0)
  { /* Test if user code is programmed starting from address 0x8010000 */
		//(*(__IO uint32_t*)ApplicationAddress) ���û������׵�ַ��������ݣ������û�����Ķ�ջ��ַ��ָ��RAM��RAM����ʼ��ַ����0x20000000
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000) == 0x20000000)//check the address is avavilable
    { /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);//��λ��ַ
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) ApplicationAddress);
      Jump_To_Application();
    }
  } /* Otherwise enters DFU mode to allow user to program his application */

	//else
  /* Enter DFU mode */
  DeviceState = STATE_dfuERROR;
  DeviceStatus[0] = STATUS_ERRFIRMWARE;
  DeviceStatus[4] = DeviceState;

  Set_System();
  Set_USBClock();
  USB_Init();  
	
  
  /* Main loop */
  while (1)
  {}
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
