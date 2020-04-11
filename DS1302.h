#ifndef __DS1302_H__ 
#define __DS1302_H__ 
/*****************************************************************************/
//����DS1302ʱ�ӽӿ�
sbit clock_clk = P2^6;//ds1302_clk��ʱ���ߣ�
sbit clock_dat = P2^7;//ds1302_dat�������ߣ�
sbit clock_Rst = P2^5;//ds1302_Rst����λ�ߣ�    Rst /CE   ��ͬ      
/*****************************************************************************/
//�����ۼ���A�еĸ�λ
sbit a0   = ACC ^ 0;
sbit a1   = ACC ^ 1;
sbit a2   = ACC ^ 2;
sbit a3   = ACC ^ 3;
sbit a4   = ACC ^ 4;
sbit a5   = ACC ^ 5;
sbit a6   = ACC ^ 6;
sbit a7   = ACC ^ 7;

/*******************************************************************************/
//��������
void write_clock(unsigned char ord, unsigned char dd);
void clock_out(unsigned char dd);
unsigned char clock_in(void);//DS1302��λд���ֽڣ��ײ�Э�飩
void clock_out(unsigned char dd);//1302����������λ�����ֽڣ��ײ�Э��?
void Init_1302(void);//-����1302�ĳ�ʼʱ�䣨2010��10��08��20ʱ51��00�������壩
unsigned char read_clock(unsigned char ord);//DS1302�����ݣ��ײ�Э�飩
void read_clockS(void);


//����1302�ĳ�ʼʱ�䣨�Զ���ʼ����
void Init_1302(void){//-����1302�ĳ�ʼʱ�䣨2019��11��29��12ʱ00��00�������壩
//	unsigned char f;
    	if(read_clock(0xc1) != 0xaa){
		write_clock(0x8e,0x00);//����д����
//		write_clock(0x8e,0x80);//��ֹд����
		write_clock(0x8c,0x19);//��
		write_clock(0x8a,0x03);//����
		write_clock(0x88,0x12);//��
		write_clock(0x86,0x18);//��
		write_clock(0x84,0x13);//Сʱ
		write_clock(0x82,0x18);//����
		write_clock(0x80,0x00);//��
//		write_clock(0x90,0xa5);//���	
		write_clock(0xc0,0xaa);//д���ʼ����־RAM����00��RAMλ�ã�
//		for(f=0;f<60;f=f+2){//�������RAMλΪ0
//			write_clock(0xc2+f,0x00);
//		}
		write_clock(0x8e,0x80);//��ֹд����
	}
}
/*****************************************************************************/
//DS1302д���ݣ��ײ�Э�飩
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
//1302����������λ�����ֽڣ��ײ�Э�飩
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
//DS1302��λд���ֽڣ��ײ�Э�飩
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
//DS1302�����ݣ��ײ�Э�飩������ʱ������
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