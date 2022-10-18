//地址：http://www.jdgcs.org/wiki/Downloads
#include <at89x51.h>
#include "KBCODE.H"
#define LCM_RS    P2_0
#define LCM_RW    P2_1 //定义LCD引脚
#define LCM_E     P2_2
#define LCM_Data  P0
#define Busy 0x80 //用于检测LCM状态字中的Busy标识
#define Key_Data  P3_2 //定义Keyboard引脚
#define Key_CLK   P3_3
void LCMInit(void);
void DisplayOneChar(unsigned char X,unsigned char Y,unsigned char DData);
void DisplayListChar(unsigned char X,unsigned char Y,unsigned char code *DData);
void Delay5Ms(void);
void Delay400Ms(void);
void Decode(unsigned char ScanCode);
void WriteDataLCM(unsigned char WDLCM);
void WriteCommandLCM(unsigned char WCLCM,BuysC);
unsigned char ReadStatusLCM(void);
unsigned char code cdle_net[] = {"RICHMCU PS2 TEST"};
unsigned char code email[] = {"WWW.RICHMCU.COM"};
unsigned char code Cls[] =   {"                "};
static unsigned char IntNum = 0; //中断次数计数
static unsigned char KeyV; //键值
static unsigned char DisNum = 0; //显示用指针
static unsigned char Key_UP=0, Shift = 0;//Key_UP是键松开标识，Shift是Shift键按下标识
static unsigned char BF = 0; //标识是否有字符被收到
 
void main(void)
{
    unsigned char TempCyc;
 
    Delay400Ms(); //启动等待，等LCM讲入工作状态
    LCMInit(); //LCM初始化
 
    DisplayListChar(0, 0, cdle_net);
    DisplayListChar(0, 1, email);
    for(TempCyc=0; TempCyc<10; TempCyc++) {
        Delay400Ms(); //延时
    }
    DisplayListChar(0, 1, Cls);
 
    IT1 = 0; //设外部中断1为低电平触发
    EX1 = 1; //开中断
    EA = 1;
 
    while(1) {
        if(BF)
            Decode(KeyV);
        else {
            EA = 1; //开中断
        }
    }
}
 
//写数据
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //检测忙
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; //若晶振速度太高可以在这后加小的延时
    LCM_E = 0; //延时
    LCM_E = 1;
}
 
//写指令
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
    if(BuysC) 
        ReadStatusLCM(); //根据需要检测忙
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
}
 
 
//读状态
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF;
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 1;
    while(LCM_Data & Busy); //检测忙信号
 
    return(LCM_Data);
}
 
void LCMInit(void) //LCM初始化
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
    Delay5Ms();
    Delay5Ms();
    WriteCommandLCM(0x38,0);
    Delay5Ms();
    Delay5Ms();
    WriteCommandLCM(0x38,0);
    Delay5Ms();
    Delay5Ms();
 
    WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
    WriteCommandLCM(0x08,1); //关闭显示
    WriteCommandLCM(0x01,1); //显示清屏
    WriteCommandLCM(0x06,1); // 显示光标移动设置
    WriteCommandLCM(0x0F,1); // 显示开及光标设置
}
 
//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF; //限制X不能大于15，Y不能大于1
    if(Y)
        X |= 0x40; //当要显示第二行时地址码+0x40;
    X |= 0x80; //算出指令码
    WriteCommandLCM(X, 1); //发命令字
    WriteDataLCM(DData); //发数据
}
 
//按指定位置显示一串字符
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
    unsigned char ListLength;
 
    ListLength = 0;
    Y &= 0x1;
    X &= 0xF; //限制X不能大于15，Y不能大于1
    while (DData[ListLength]>0x19) {//若到达字串尾则退出
        if(X <= 0xF) {//X坐标应小于0xF
            DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
            ListLength++;
            X++;
        }
    }
}
 
//5ms延时
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}
 
//400ms延时
void Delay400Ms(void)
{
    unsigned char TempCycA = 5;
    unsigned int TempCycB;
    while(TempCycA--) {
        TempCycB=7269;
        while(TempCycB--);
    }
}
 
void Keyboard_out(void) interrupt 2
{
    if[[IntNum > 0) && (IntNum < 9]] {
        KeyV >>= 1;			//因键盘数据是低>>高，结合上一句所以右移一位
        if(Key_Data) {
            KeyV |= 0x80;	//当键盘数据线为1时为1到最高位
        }
    }
    IntNum++;
    while(!Key_CLK);		//等待PS/2CLK拉高
    if(IntNum > 10) {
        IntNum = 0;			//当中断10次后表示一帧数据收完，清变量准备下一次接收
        BF = 1;				//标识有字符输入完了
        EA = 0;				//关中断等显示完后再开中断
    }
}
void Decode(unsigned char ScanCode) 
//注意:如SHIFT+G为12H 34H F0H 34H F0H 12H，也就是说shift的通码+G的通码+shift的断码+G的断码
{
    unsigned char TempCyc;
 
    if(!Key_UP) {			//当键盘松开时
        switch(ScanCode) {
            case 0xF0 :		//当收到0xF0，Key_UP置1表示断码开始
                Key_UP = 1;
                break;
            case 0x12:		// 左 SHIFT
                Shift = 1;
                break;
            case 0x59:		// 右 SHIFT
                Shift = 1;
                break;
            default:
                if(DisNum > 15) {
                    DisplayListChar(0,1,Cls);	//清LCD第二行
                    DisNum = 0;
                }
            if(Shift == 1) {				//如果按下SHIFT
                for(TempCyc = 0;(Shifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
                if(Shifted[TempCyc][0] == ScanCode) 
                {
                    DisplayOneChar(DisNum,1,Shifted[TempCyc][1]);
                }
                DisNum++;
            }
            else {							//没有按下SHIFT
                for(TempCyc = 0; (UnShifted[TempCyc][0]!=ScanCode)&&(TempCyc<59);TempCyc++); //查表显示
                if(UnShifted[TempCyc][0] == ScanCode) {
                    DisplayOneChar(DisNum,1,UnShifted[TempCyc][1]);
                }
                DisNum++;
            }
            break;
        }
    }
    else {
        Key_UP = 0;
        switch(ScanCode) {	//当键松开时不处理判码，如G 34H F0H 34H 那么第二个34H不会被处理
            case 0x12:		// 左 SHIFT
                Shift = 0;
                break;
            case 0x59:		// 右 SHIFT
                Shift = 0;
                break;
            default:
                break;
        }
    }
    BF = 0;	//标识字符处理完了
}
unsigned char code UnShifted[61][2] = {
    0x1C, 'a',
    0x32, 'b',
    0x21, 'c',
    0x23, 'd',
    0x24, 'e',
    0x2B, 'f',
    0x34, 'g',
    0x33, 'h',
    0x43, 'i',
    0x3B, 'j',
    0x42, 'k',
    0x4B, 'l',
    0x3A, 'm',
    0x31, 'n',
    0x44, 'o',
    0x4D, 'p',
    0x15, 'q',
    0x2D, 'r',
    0x1B, 's',
    0x2C, 't',
    0x3C, 'u',
    0x2A, 'v',
    0x1D, 'w',
    0x22, 'x',
    0x35, 'y',
    0x1A, 'z',
    0x45, '0',
    0x16, '1',
    0x1E, '2',
    0x26, '3',
    0x25, '4',
    0x2E, '5',
    0x36, '6',
    0x3D, '7',
    0x3E, '8',
    0x46, '9',
    0x0E, '`',
    0x4E, '-',
    0x55, '=',
    0x5D, '\\',
    0x29, ' ',
    0x54, '[',
    0x5B, ']',
    0x4C, ';',
    0x52, '\'
};