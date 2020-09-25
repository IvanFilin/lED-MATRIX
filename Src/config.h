#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

void paint (int massiv[8][8], int  v)
 {
	 int i,j;
			for (int c; c<v;c++)// sickle delay infomation
			{
				for (int i=0;i<8;i++)
					for(int j=0;j<8;j++)
					{
						if(massiv[i][j]==1)// i == 1 amd j == 1
						{
							//on stolbec 
							GPIOA -> ODR = 0xC0;
							GPIOB -> ODR = 0xF000;
							GPIOC -> ODR = 0x300;							
							for ( int a=0;a<400;a++);// delay						
							//on stroka
							GPIOA -> ODR |= 0x30;
							GPIOB -> ODR |= 0x3;
							GPIOC -> ODR |= 0xF0;
						}
						else
						{
														//on stolbec 
							GPIOA -> ODR = 0xC0;
							GPIOB -> ODR = 0xF000;
							GPIOC -> ODR = 0x300;							
							for ( int a=0;a<400;a++);// delay						
							//on stroka
							GPIOA -> ODR |= 0x30;
							GPIOB -> ODR |= 0x3;
							GPIOC -> ODR |= 0xF0;
						}
			}
	}
}

int main(void){
	
	RCC->APB2ENR = 0x7C;// turn on shina APB2
	
	uint32_t row[8]={0x20000,0x200000, 0x2,0x20, 0x20000,0x200000,0x2000000,0x20000000};// string for CRL on HEX
	uint32_t col[8]={0x2000000,0x20000000, 0x20000,0x200000,0x2000000,0x2000000, 0x2,0x20};// collown for CRL and CRH on HEX
	
	//row = 4, 5,  0, 1,  4, 5, 6, 7
	//col = 6, 7,  12, 13, 14, 15,  8, 9
	
	int i=0,j=0,a,c, v=3;
	
	// symbol's array
	int massiv[8][8]= {
		
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,1,1,0,0,1,
		1,0,0,1,1,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1
	};
		for(int i=0; i<8;i++)//string pins turn on rejim pull-up-down
		{
				if(i==0 || i ==1){
				GPIOA -> CRL = row[i];
				}
				if(i==2 || i==3){
				GPIOB -> CRL = row[i];
				}
				if(i==4 || i==5 || i==6 || i==7 || i==8){
				GPIOC -> CRL = row[i];	
				}
		}
		
	for(int i=0; i<8;i++)//row pins turn on rejim pull-up-down
		{
				if(i==0 || i ==1){
				GPIOA -> CRL |= col[i];
				}
				if(i==2 || i==3 || i==4 || i==5 || i==6){
				GPIOB -> CRH |= col[i];
				}
				if(i==7 || i==8){
				GPIOC -> CRH |= col[i];
				}
		}
				for(int i=0; i<8;i++)//string pins turn on rejim pull-up-down
		{
				if(i==0 || i ==1){
				GPIOA -> ODR = row[i];
				}
				if(i==2 || i==3){
				GPIOB -> ODR = row[i];
				}
				if(i==4 || i==5 || i==6 || i==7 || i==8){
				GPIOC -> ODR = row[i];	
				}
		}
	while(1)
	{
		paint(massiv,v);
	}		
 }

  /*   Y8 -	40 PC9			   	 Y6 - 27 PB1
	in	 X5 -	39 PC8				   Y3 -1 26 PB0
	in	 X3 -	38 PC7				in X4 - 25 PC5
		   Y5 -	37 PC6				   Y1 - 24 PC4
	in	 X8 -	36 PB15				in X6 - 23 PA7
		   Y7 -	35 PB14				in X7 - 22 PA6
	in	 X2 - 34 PB13				   Y2 - 21 PA5
	in	 X1 - 33 PB12				   Y4 - 20 PA4
		 
		 port A  4 5         6 7
		 port B  0 1         12 13 14 15
		 port C  4 5 6 7     8 9
			 
 */
 			// 	1 	 2	 3	 4	 5	 6	 7	 8 		
			//	|		 |	 |	 |	 |	 |	 |	 | 		
			//	| 	 |	 |	 |	 |	 |	 |	 | 		
			//	13	 3   4   10  6   11  15  16 	
	//1--9 	*	  *	  *	  *	  *	  *	  *	  *
	
	//2--14 *	  *	  *	  *	  *	  *	  *	  *
	
	//3--8  *	  *	  *	  *	  *	  *	  *	  *
	
	//4--12 *	  *	  *	  *	  *	  *	  *	  *
	
	//5--1  *	  *	  *	  *	  *	  *	  *	  *
	
	//6--7  *	  *	  *	  *	  *	  *	  *	  *
	
	//7--2  *	  *	  *	  *	  *	  *	  *	  *
	
	//8--5  *	  *	  *	  *	  *	  *	  *	  *
	
	//---------------------------------------
	
 /*    Y8 -	40 PC9		--9			       Y6 - 27 PB1		--8
	in	 X5 -	39 PC8		--10				   Y3 -1 26 PB0		--7
	in	 X3 -	38 PC7		--11				in X4 - 25 PC5		--6
		   Y5 -	37 PC6		--12				   Y1 - 24 PC4		--5
	in	 X8 -	36 PB15		--13				in X6 - 23 PA7		--4
		   Y7 -	35 PB14		--14				in X7 - 22 PA6		--3
	in	 X2 - 34 PB13		--15				   Y2 - 21 PA5		--2
	in	 X1 - 33 PB12		--16				   Y4 - 20 PA4		--1
		 
		 port A  4 5         6 7
		 port B  0 1         12 13 14 15
		 port C  4 5 6 7     8 9
			 
 */
	