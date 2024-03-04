/*
 * main.c
 *
 *  Created on: 1 Mar 2024
 *      Author: magdy
 */


#include "TYPES.h"
#include "BIT_MATH.h"

#include "Interface.h"



#include "LCD_Interface.h"
#include "KPD_Interface.h"
#include "Stepper_Interface.h"

#define F_CPU 8000000UL
#include <util/delay.h>



int main(void)
{
	uint8 Local_u8keychar, Local_u8First[4], Local_u8Sec[4], Local_Oper, iter, check_var_1, check_var_2, Local_res;
	uint8 Local_counter_1=0;
	uint8 Local_counter_2=0;
	uint8 Local_Flag=0;
	uint8 Local_oper_1=0;
	uint8 Local_oper_2=0;
	uint8 tens_1 = 1;
	uint8 tens_2 = 1;
	DIO_voidInit();

	LCD_voidInit();

	while(1)
	{
		KPD_u8GetKey(&Local_u8keychar);
		if(Local_u8keychar != KPD_u8_NOTPRESSED)
		{
			LCD_u8SendChar(Local_u8keychar);
			if((Local_u8keychar >= '1') && (Local_u8keychar <= '9'))
			{

				if(Local_Flag == 1)
				{
					Local_u8Sec[Local_counter_2] = Local_u8keychar;
					Local_counter_2++;
				}
				else
				{
					Local_u8First[Local_counter_1] = Local_u8keychar;
					Local_counter_1++;
				}
			}
			if((Local_u8keychar == '+') || (Local_u8keychar == '-') || (Local_u8keychar == '*') || (Local_u8keychar == '/'))
			{

				Local_Flag = 1;
				Local_Oper = Local_u8keychar;
				for(iter=0; iter < Local_counter_1; iter++)
				{
					check_var_1 = tens_1;
					tens_1 *=10;
				}
				for(iter=0; iter < Local_counter_1; iter++)
				{
					Local_oper_1 = Local_oper_1 * 10 +(Local_u8First[iter] - 48);
				}
			}
			if(Local_u8keychar == '=')
			{
				for(iter=0; iter < Local_counter_2; iter++)
				{
					check_var_2 = tens_2;
					tens_2 *=10;
				}
				for(iter=0; iter < Local_counter_2; iter++)
				{
					Local_oper_2 = Local_oper_2 = Local_oper_2 * 10 +(Local_u8Sec[iter] - 48);
				}
				if(Local_Oper == '+')
				{
					Local_res = Local_oper_1 + Local_oper_2;
					LCD_u8SendNUM(Local_res);
				}
				if(Local_Oper == '*')
				{
					Local_res = Local_oper_1 * Local_oper_2;
					LCD_u8SendNUM(Local_res);
				}
				if(Local_Oper == '-')
				{
					Local_res = Local_oper_1 - Local_oper_2;
					LCD_u8SendNUM(Local_res);
				}
				if(Local_Oper == '/')
				{
					if(Local_oper_2 == 0)
					{
						LCD_u8SendString("N/A");
					}
					else
					{
						Local_res = Local_oper_1 / Local_oper_2;
						LCD_u8SendNUM(Local_res);
					}

				}
			}
			if(Local_u8keychar == 'C')
			{
				LCD_CLR();
				Local_counter_1=0;
				Local_counter_2=0;
				Local_Flag=0;
				Local_oper_1=0;
				Local_oper_2=0;
				tens_1 = 1;
				tens_2 = 1;
			}
		}
	}


	return 0;

}
