#include <stdio.h>
#include <REG922.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code  dout[5]={0x01,0x42,0x00,0x00,0x00};
uchar data  din[5]={0x00,0x00,0x00,0x00,0x00};
uint  code  hos_tabup[16]={0xE31B,0xF800,0xF50D,0xFF07,0xDE26,0x0000,0x0000,0xDF27,		 //主手柄释放键表
                            0x877F,0xB941,0xBA42,0x8870,0xDC24,0xA159,0xD820,0xA058};			
uint  code  hos_tabdn[16]={0x639B,0x7880,0x758D,0x7F87,0x5EA6,0x0000,0x0000,0x5FA7,		 //主手柄按键表
                            0x07FF,0x39C1,0x3AC2,0x08F0,0x5CA4,0x21D9,0x58A0,0x20D8};	
/*uint  code  hos_tabup[16]={0x0000,0x8870,0x877F,0x0000,0xDE26,0x0000,0x0000,0xDF27,		 //主手柄释放键表
                            0xF50D,0xFF07,0xE31B,0xF800,0xDC24,0xA159,0xD820,0xA058};				
uint  code  hos_tabdn[16]={0x0000,0x08F0,0x07FF,0x0000,0x5EA6,0x0000,0x0000,0x5FA7,		 //主手柄按键表
                            0x758D,0x7F87,0x639B,0x7880,0x5CA4,0x21D9,0x58A0,0x20D8};				*/
uint  code  gue_tabup[16]={	0x9961,0x9A62,0x9B63,0x8B73,0x0000,0x0000,0x0000,0x0000,	  //副手柄释放键表
                            0xB149,0xA35B,0xFC04,0xF901,0x0000,0x0000,0x0000,0x0000};
uint  code  gue_tabdn[16]={	0x19E1,0x1AE2,0x1BE3,0x0BF3,0x0000,0x0000,0x0000,0x0000,  	  //副手柄按键表
                            0x31C9,0x23DB,0x7C84,0x7981,0x0000,0x0000,0x0000,0x0000};
//unsigned long endcode=0x0005AA8A;												 //结束码的红外发射码	 ，
uint   KEY_hos[2]={0xFFFF,0xFFFF};                                     	   //主游戏手柄扫描值，
uint   KEY_gue[2]={0xFFFF,0xFFFF};                                     	   //副游戏手柄扫描值，
uint   ir_key;														  		   //标准红外码缓冲,
uint   chan_key;                                 //手柄按键有变化的位，
uint   stat_key;                                 //当前手柄的状态值，

unsigned long ref;
unsigned long idata irbuf[32];                                                     //红外输出缓冲区，
unsigned long *p_t;                                            //指向红外缓冲区的两个指针，
unsigned long *p_b;
bit   bdata   Buf_emp=1;			                                               //红外输出缓冲区空标志，
bit   bdata   Bit_F=0;				    	               	                	  //红外输出的移位标志，
bit   bdata   Buf_ful=0;					                            		  //红外输出缓冲区满标志
bit   bdata   Saf_F=0;	          //安全间隔标志位
bit   bdata   Host_F=0;	 														 

sbit  ACK1  =P1^2;
sbit  ACK2  =P1^3;
sbit  DI1   =P0^3;
sbit  DI2   =P1^6;
sbit  DO1   =P0^0;
sbit  DO2   =P0^4;
sbit  CLK1  =P0^2;
sbit  CLK2  =P0^7;
sbit  SEN1  =P0^1;
sbit  SEN2  =P1^7;		
sbit  PWM   =P0^5;
sbit  IR_OUT=P0^6;
				  

void  delay(uchar n);
void  Isp_Init();			  //初始化串口，
//void  keysignout(void)	;
void  Getkey_hos(void);
void  Getkey_gue(void);
void  Trans(void);		 //手柄键码转化为红外输出码，

main()
{

   P0M1=0XDF;		//外部引脚I/O配置,
   P0M2=0XF7;
   P1M1=0XFF;
   P1M2=0X83;
   DIVM=0;			//时钟分频设置，
//   AUXR1=AUXR1|0x80;
   TH0=238;
   TL0=212;
   TMOD=0X01;		//记数器0设置，
   PWM=0;
   IR_OUT=1;
   TCON=0x14;		//设置下降沿中断，
   IEN0=0x06;		//开外部中断一	  ,定时器零，
   EA=1;
   Isp_Init();				  //初始化串口，

   p_t=&irbuf[0];
   p_b=&irbuf[0];



  while(1)
  {
   Getkey_hos();
   chan_key=KEY_hos[0]^KEY_hos[1];
   if(chan_key)
   {
     Host_F=1;
     stat_key=KEY_hos[0];
     Trans();
	 KEY_hos[1]=KEY_hos[0];
	}
   Getkey_gue();
   chan_key=KEY_gue[0]^KEY_gue[1];
   if(chan_key)  
   { 
     Host_F=0;
     stat_key=KEY_gue[0];
     Trans();
	 KEY_gue[1]=KEY_gue[0];
    }
  } 	 

}

void irout() interrupt  2 using 2		   //使用外部中断1中断服务程序	 ,
{
  EA=0;
  IR_OUT=PWM;
  PWM=!PWM;
  EA=1;
} 

void delay(	uchar n)			 //n*12us延时程序；
{
    uchar i,	j;
	for(i=0;i<n;i++)
	{
	  for(j=0;j<10;j++)
	  {
	    _nop_();
   	   }	
	 }
}	
void  Getkey_hos()						//get gamekdy
{
 uchar p,i,ref;
  SEN2=0;
  delay(4);
  for(p=0;p<5;p++)
 {
	for(ref=0x01;ref>0x00;ref<<=1)
  {
	CLK2=0;
	if(ref&dout[p])		   //输出一位控制数据	  ？是否满足4us	   
 	  DO2=1;
	else
	  DO2=0;
	for(i=0;i<3;i++)		//大概2us的延迟，
	_nop_();				
	CLK2=1;
	if(DI2)
	  din[p]=ref|din[p];  //输入一位控制数据	  ？是否满足4us	  
	for(i=0;i<2;i++)		//大概2us的延迟，
   	_nop_();
   }
    DO2=1;
    if(p<4)
	{ 

//	  delay(1); 
//   	do
//	  {
//	  while(ACK2)			  //检测ACK信号是否响应。	  有响应则向下		执行。
//	  {
	  _nop_();
//	  ACK=1;
//	  timeout=10000;
//	  break;
//	  }
	  delay(2);
//	  }
//	  while(timeout--);
 	}
//	else
//	{}

   }
  SEN2=1;
//  delay(2);
//  keysignout();		      // 键码值通过串口输出。	
   KEY_hos[0]=din[3];
   KEY_hos[0]<<=8;
   KEY_hos[0]+=din[4];
  for(i=0;i<5;i++)
  din[i]=0x00;
//  for(i=0;i<255;i++)
//  delay(255);	

} 

void  Getkey_gue()						//get gamekdy
{
 uchar p,i,ref;

  SEN1=0;
  delay(4);
  for(p=0;p<5;p++)
 {
	for(ref=0x01;ref>0x00;ref<<=1)
  {
	CLK1=0;
	if(ref&dout[p])		   //输出一位控制数据	  ？是否满足4us	   
 	  DO1=1;
	else
	  DO1=0;
	for(i=0;i<3;i++)		//大概2us的延迟，
	_nop_();				
	CLK1=1;
	if(DI1)
	  din[p]=ref|din[p];  //输入一位控制数据	  ？是否满足4us	  
	for(i=0;i<2;i++)		//大概2us的延迟，
   	_nop_();
   }
    DO1=1;
    if(p<4)
	{ 

//	  delay(1); 
//   	do
//	  {
//	  while(ACK2)			  //检测ACK信号是否响应。	  有响应则向下		执行。
//	  {
	  _nop_();
//	  ACK=1;
//	  timeout=10000;
//	  break;
//	  }
	  delay(2);
//	  }
//	  while(timeout--);
 	}
//	else
//	{}

   }
  SEN1=1;
//  delay(2);
//  keysignout();		      // 键码值通过串口输出。	
   KEY_gue[0]=(din[3]|0x0F);
   KEY_gue[0]<<=8;
   KEY_gue[0]+=(din[4]|0x0F);
  for(i=0;i<5;i++)
  din[i]=0x00;
//  for(i=0;i<255;i++)
//  delay(255);	
			 	 
}
void Isp_Init()				  //初始化串口，
{
    SSTAT=0xFA;
	BRGCON=0x00;
	AUXR1=0x40;
	SCON=0x50;
	BRGR1=0x90;
	BRGR0=0x00;
	BRGCON=0x03;
}

void t0() interrupt 1 using 2		   //使用定时器0中断服务程序	 ,
{
/* if(Buf_emp==0)
  TxD=0;
 else
  TxD=1;	 */
 if(Saf_F)							   //安全间隔时间定时，
 {									   
     Saf_F=0;
	 IR_OUT=1;
	 TH0=39;
	 TL0=200;
	 TR0=1;
 }
 else
 {
  if(Buf_emp==0)
   {
     TH0=255;						   //定时45us
     TL0=6;
     if(Bit_F==0)
	   {
	    Bit_F=1;
	    ref=0x00000001; 
        }
	 if(*p_b&ref)					  //输出一位红外数据，
	    IR_OUT=0;					  
	 else
	    IR_OUT=1;
	 TR0=1;
	 ref<<=1;
	 if(ref>0x00080000)				  //判断一个红外码字是否发完，
		{
	  	Bit_F=0;
	    Buf_ful=0;
		if(p_b==&irbuf[31])
		  p_b=&irbuf[0];
		else
		  p_b++;
	    if(p_b==p_t)
		  Buf_emp=1;
		Saf_F=1;					  //置保护时间标志，
 
		}
   }
  else
   {
      TH0=255;						  //这个时间能否再减小？
      TL0=6; 
      TR0=1;
	  IR_OUT=!PWM;										
   }
 }
}

 void Trans()		                                //手柄键码值转换为红外输出码值，
{
  uchar  i;
  uint   ref;										 //一次扫描手柄后出现变化的键，
 // if(KEY[0]==KEY[1])
 // return;
 // else
  if(Buf_ful==0)
  {

  for(i=0,ref=0x8000;i<16;i++,ref>>=1)
  {
    if(chan_key&ref)
	{
	  if(stat_key&ref)								   //为真检测到释放键
	   {
	    if(Host_F)									   //释放键为主手柄的释放键
	    ir_key=hos_tabup[i];
		else											//释放键为副手柄的释放键
		ir_key=gue_tabup[i];		                    //释放键进入红外寄存器 
	    *p_t=ir_key&0x00FF;
        *p_t<<=12;
        *p_t+=(((ir_key&0xFF00)>>6)|0x0802);

/*	   if(p_t==&irbuf[31])
	     p_t=&irbuf[0];
	   else
	     p_t++;
	   Buf_emp=0;                                    //红外输出缓冲区有数据，
	   if(p_t==p_b)
	    {
	     Buf_ful=1;				                     //红外输出缓冲区满，
		 while(1)				  //测试缓冲区是否会满，
		 {
		  DO1=1;
		  delay(5);
		  DO1=0;
		  delay(5);
		  }
	     return;			    
	    }

		*p_t=0x0005AA8A;							//结束键进缓冲区，			*/
	   }
	  else											  //检测到按下键，
	   {											  
	    if(Host_F)									  //按下键为主手柄的按下键，
	    ir_key=hos_tabdn[i];
		else										  //按下键为副手柄的按下键，
		ir_key=gue_tabdn[i];
        *p_t=ir_key&0x00FF;
        *p_t<<=12;
        *p_t+=(((ir_key&0xFF00)>>6)|0x0802);		  //标准红外码转换为添加过引导码的发送红外码，
	   }
  	  if(p_t==&irbuf[31])
	    p_t=&irbuf[0];
	  else
	    p_t++;
	  Buf_emp=0;                   //红外输出缓冲区有数据，
	  if(p_t==p_b)
	   {
	    Buf_ful=1;				  //红外输出缓冲区满，
//	while(1)				  //测试缓冲区是否会满，
//		 {
          TxD=0;
//		  }		
		return;
	   }
	 
	}

   }
   }

} 