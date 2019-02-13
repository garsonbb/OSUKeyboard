#include "osu.h"
#include "stm32f10x.h"
#include "hw_config.h"
#include "delay.h"

//按键都是低电平按下


u8 z,x,esc,restart = 1;//0=keydown
u8 flag = 0;//0= key up

void osu_send()
{

	uint8_t Mouse_Buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	u8 i = 3;
	if (z && x && esc && restart && flag) {while(!PrevXferComplete){};keyboard_Send(0);flag=0;}
	if (esc == 0){osu_send_esc();delay_ms(100);while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14));}
	if (restart == 0){osu_send_restart();delay_ms(100);while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15));}
	if (z == 0){Mouse_Buffer[i] = 0x1d;i++;}
	if (x == 0){Mouse_Buffer[i] = 0x1b;i++;}
	if ((!z) || (!x) == 1){flag = 1;PrevXferComplete = 0;USB_SIL_Write(EP1_IN, Mouse_Buffer, 8);SetEPTxValid(ENDP1);}
	
	//PrevXferComplete = 0;
  //USB_SIL_Write(EP1_IN, Mouse_Buffer, 8);
  
  //SetEPTxValid(ENDP1);

}




void osu_send_restart(void)
{
	while(!PrevXferComplete){};
	keyboard_Send(0x29);
	while(!PrevXferComplete){};
	keyboard_Send(0x51);
	while(!PrevXferComplete){};
	keyboard_Send(0);
	while(!PrevXferComplete){};
	keyboard_Send(0x51);
	while(!PrevXferComplete){};
	keyboard_Send(0);
	while(!PrevXferComplete){};
	keyboard_Send(0x58);
	while(!PrevXferComplete){};
	keyboard_Send(0x0);
}
	
void osu_send_esc(void)
{
	while(!PrevXferComplete){};
	keyboard_Send(0x29);
	while(!PrevXferComplete){};
	keyboard_Send(0x0);
}

void osu_key_scan_send()
{
x = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
z = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
esc = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
restart = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
osu_send();
}
