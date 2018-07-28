/**************************************************************************//**
 *
 * Copyright (C) 2016 CMSMCU Electronic Co., Ltd. All rights reserved.
 *
 ******************************************************************************/

/*---------------------------------------------------------------------------------------------------------*/
/* Include related headers                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#include "config_CMS32F030x.h"
#include "stdio.h"

#if   defined ( __CC_ARM )
#pragma import(__use_no_semihosting_swi)


struct __FILE { int handle; /* Add whatever you need here */ };
#endif

FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {
  while(!(UART0->LSR&THRE));
  UART0->THR = ch;
  if(ch == '\n')
  {
    while(!(UART0->LSR&THRE));
    UART0->THR = '\r';
  }
  return ch;
}

int fgetc(FILE *f) {
  int u32data;
  while(!(UART0->LSR&RDR));
  u32data = UART0->RBR;
  while(!(UART0->LSR&THRE));
  UART0->THR = u32data;
  return u32data;
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch) {
  while(!(UART0->LSR&THRE));
  UART0->THR = ch;
}

void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}
