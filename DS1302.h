#ifndef __DS1302_H__ 
#define __DS1302_H__ 
/*****************************************************************************/
//定义DS1302时钟接口
sbit clock_clk = P2^6;//ds1302_clk（时钟线）
sbit clock_dat = P2^7;//ds1302_dat（数据线）
sbit clock_Rst = P2^5;//ds1302_Rst（复位线）    Rst /CE   相同      
/*****************************************************************************/
//定义累加器A中的各位
sbit a0   = ACC ^ 0;
sbit a1   = ACC ^ 1;
sbit a2   = ACC ^ 2;
sbit a3   = ACC ^ 3;
sbit a4   = ACC ^ 4;
sbit a5   = ACC ^ 5;
sbit a6   = ACC ^ 6;
sbit a7   = ACC ^ 7;

/*******************************************************************************/
//函数声明
void write_clock(unsigned char ord, unsigned char dd);
void clock_out(unsigned char dd);
unsigned char clock_in(void);//DS1302逐位写入字节（底层协议）
void clock_out(unsigned char dd);//1302驱动程序逐位读出字节（底层协议?
void Init_1302(void);//-设置1302的初始时间（2010年10月08日20时51分00秒星期五）
unsigned char read_clock(unsigned char ord);//DS1302读数据（底层协议）
void read_clockS(void);


//设置1302的初始时间（自动初始化）
void Init_1302(void){//-设置1302的初始时间（2019年11月29日12时00分00秒星期五）
//	unsigned char f;
    	if(read_clock(0xc1) != 0xaa){
		write_clock(0x8e,0x00);//允许写操作
//		write_clock(0x8e,0x80);//禁止写操作
		write_clock(0x8c,0x19);//年
		write_clock(0x8a,0x03);//星期
		write_clock(0x88,0x12);//月
		write_clock(0x86,0x18);//日
		write_clock(0x84,0x13);//小时
		write_clock(0x82,0x18);//分钟
		write_clock(0x80,0x00);//秒
//		write_clock(0x90,0xa5);//充电	
		write_clock(0xc0,0xaa);//写入初始化标志RAM（第00个RAM位置）
//		for(f=0;f<60;f=f+2){//清除闹钟RAM位为0
//			write_clock(0xc2+f,0x00);
//		}
		write_clock(0x8e,0x80);//禁止写操作
	}
}
/*****************************************************************************/
//DS1302写数据（底层协议）
void write_clock(unsigned char ord, unsigned char dd){
	clock_clk=0;
	clock_Rst=0;
	clock_Rst=1;
	clock_out(ord);
	clock_out(dd);
	clock_Rst=0;
	clock_clk=1;
}
/*****************************************************************************/
//1302驱动程序逐位读出字节（底层协议）
void clock_out(unsigned char dd){
	ACC=dd;
	clock_dat=a0; clock_clk=1; clock_clk=0;
	clock_dat=a1; clock_clk=1; clock_clk=0;
	clock_dat=a2; clock_clk=1; clock_clk=0;
	clock_dat=a3; clock_clk=1; clock_clk=0;
	clock_dat=a4; clock_clk=1; clock_clk=0;
	clock_dat=a5; clock_clk=1; clock_clk=0;
	clock_dat=a6; clock_clk=1; clock_clk=0;
	clock_dat=a7; clock_clk=1; clock_clk=0;
}
/*****************************************************************************/
//DS1302逐位写入字节（底层协议）
unsigned char clock_in(void){
	clock_dat=1;
	a0=clock_dat;
	clock_clk=1; clock_clk=0; a1=clock_dat;
	clock_clk=1; clock_clk=0; a2=clock_dat;
	clock_clk=1; clock_clk=0; a3=clock_dat;
	clock_clk=1; clock_clk=0; a4=clock_dat;
	clock_clk=1; clock_clk=0; a5=clock_dat;
	clock_clk=1; clock_clk=0; a6=clock_dat;
	clock_clk=1; clock_clk=0; a7=clock_dat;
	return(ACC);
}
/*****************************************************************************/
//DS1302读数据（底层协议）供调用时钟数据
unsigned char read_clock(unsigned char ord){
	unsigned char dd=0;
	clock_clk=0;
	clock_Rst=0;
	clock_Rst=1;
	clock_out(ord);
	dd=clock_in();
	clock_Rst=0;
	clock_clk=1;
	return(dd);
}



#endif 