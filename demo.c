#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit out=P3^7;
sbit led1=P0^0;
sbit led2=P0^1;
sbit led3=P0^2;
sbit led4=P0^3;
sbit led5=P0^4;
sbit led6=P0^5;
sbit led7=P0^6;
sbit led8=P0^7;

sbit SCL=P1^2;      //SCL定义为P1口的第3位脚，连接ADC0832SCL脚
sbit DO=P1^3;       //DO定义为P1口的第4位脚，连接ADC0832DO脚
sbit CS=P1^0;       //CS定义为P1口的第4位脚，连接ADC0832CS脚



uchar h1,date;
unsigned char adval;
void delay(uint z)
{
   uchar y;
   for(;z>0;z--)
   for(y=5;y>0;y--);
}


/***********读数模转换数据********************************************************/    
//请先了解ADC0832模数转换的串行协议，再来读本函数，主要是对应时序图来理解，本函数是模拟0832的串行协议进行的
                        //  1  1  0 通道
                        //  1  1  1 通道 
unsigned char ad0832read(bit SGL,bit ODD)
{
    unsigned char i=0,value=0,value1=0;     
        SCL=0;
        DO=1;
        CS=0;       //开始
        SCL=1;      //第一个上升沿    
        SCL=0;
        DO=SGL;
        SCL=1;      //第二个上升沿
        SCL=0;
        DO=ODD;
        SCL=1;     //第三个上升沿
        SCL=0;     //第三个下降沿
        DO=1;
        for(i=0;i<8;i++)
        {
            SCL=1;
            SCL=0; //开始从第四个下降沿接收数据
            value<<=1;
            if(DO)
                value++;                        
        }
        for(i=0;i<8;i++)
        {           //接收校验数据
            value1<<=1;
            if(DO)
                value1+=0x80;
            SCL=1;
            SCL=0;
        }
        CS=1;
        SCL=1;  
        if(value==value1)               //与校验数据比较，正确就返回数据，否则返回0 
            return value;
    return 0;
}

void penquan()    //PWM调压
{
    date=ad0832read(1,0);
    
    h1=(255-date);
    out=0;
    delay(h1);
    if(h1>30) led1=1; else led1=0;
    if(h1>70) led2=1; else led2=0;
    if(h1>100) led3=1; else led3=0;
    if(h1>130) led4=1; else led4=0;
    if(h1>160) led5=1; else led5=0;
    if(h1>180) led6=1; else led6=0;
    if(h1>200) led7=1; else led7=0;
    if(h1>220) led8=1; else led8=0;

    out=1;
    delay(date);

}
void main()
{
   
   while(1)
   {    
       
        penquan();         //给定个延时次数
       