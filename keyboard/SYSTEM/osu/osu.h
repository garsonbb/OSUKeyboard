#ifndef __OSU_H
#define __OSU_H 			   
#include "stm32f10x.h"

extern __IO uint8_t PrevXferComplete;

void osu_key_scan_send(void);
void osu_send(void);
void osu_send_restart(void);
void osu_send_esc(void);
#endif





























