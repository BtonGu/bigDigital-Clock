#ifndef __displaytime_H__ 
#define __displaytime_H__ 
#include "nongli.h"
uchar sec,min,hour,day,date,month,year,week,day_moon;

/*��ʾ�ꡢ�¡��ա�����-------------------------------------------------------*/
void displaydate(void)
{
	write_com(0x30);
	write_com(0x06);

/*��Һ������д �� ����-------------------------------------------*/
	write_com(0x80);
	lcm_w_word("20");	
	year=read_clock(0x8d);//����1302ʱ�������е������ݣ��ӵ�ַ0x8d��
	write_data(year/16+0x30);	
	write_data(year%16+0x30);
//	lcm_w_word("��");
	
/*��Һ������д �� ����-------------------------------------------*/
	month=read_clock(0x89);//����1302ʱ�������е������ݣ��ӵ�ַ0x89��
	lcm_w_word("-");	
	
/*	if(month/16 != 0){	  //ʮλ����
		write_data((month/16)+0x30);
		write_data((month%16)+0x30);}	
	else{
		write_data((month%16)+0x30);
		//write_data(0x20);
	}
	 */
	lcm_w_test(1,(month/16+0x30));
	lcm_w_test(1,((month%16)+0x30));		

//	write_com(0x88);
//	lcm_w_word("��");	

/*��Һ������д �� ����-------------------------------------------*/
	date=read_clock(0x87);//��1302оƬ�ж�ȡ�����ݣ��ӵ�ַ0x87��
	lcm_w_word("-");
/*
	if(date/16 !=0){			  //ʮλ����
		write1632GDRAM(2,2,num1632[date/16]);
		write1632GDRAM(3,2,num1632[date%16]);}
	else
				write1632GDRAM(3,2,num1632[date%16]);
*/
	lcm_w_test(1,(date/16+0x30));
	lcm_w_test(1,(date%16+0x30)); 

//	lcm_w_word("��");
}

/*��Һ������д ���� ����-----------------------------------------*/
void displayxq(void){

	unsigned char sel,dd,mo,yy;

	dd = read_clock(0x87);//��
	mo = read_clock(0x89);//��
	yy = read_clock(0x8d);//��
	Conver_week(0,yy,mo,dd);//���ù������������Ӻ���
   sel=week;//week�ǹ���ת�������Ӻ��������н�������Ϊ0-6��0��������
	write_com(0x87);//��ʾλ��
	if(sel==0)  {lcm_w_word("��");}    //0=������
  	if(sel==6)  {lcm_w_word("��");}    //
  	if(sel==5)  {lcm_w_word("��");}    //
  	if(sel==4)  {lcm_w_word("��");}    //
//	if(sel==3)  {lcm_w_word("��");}//�����Է���Һ����������һ�䣬ֻ������һ����ʾ ��	����Ҫ�򲹶�������ȷ��ʾ��
	if(sel==3)  {write_data(0xc8);write_data(0xfd);} //��ָ�����lcm_w_word("��"); ��Ϊ������������ʧЧ��
  	if(sel==2)  {lcm_w_word("��");}    //
  	if(sel==1)  {lcm_w_word("һ");}    //����һ
	write_com(0x85);
	lcm_w_word("����");//�����ַ���ʾ�Ӻ�������ʾ ���� ������

}
/*��Ҫ��ͼ��ʾ��:ʱ���֡���--------------------------------------------------*/
void displaytime(void)
{
/*��Һ������д Сʱ ����-----------------------------------------*/
	hour = read_clock(0x85);					 //��ȡDS1302�� ʱ
	write1632GDRAM(1,3,num1632[hour/16]);
	write1632GDRAM(2,3,num1632[hour%16]);
	write1632GDRAM(3,3,num1632[10]);        //ʱ�ӷָ�����:��
	 //���¼�eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	//	 if(hour> 12)					   //��
	//	 	hour = hour-12;			   //��

/*��Һ������д ���� ����-----------------------------------------*/
	min = read_clock(0x83);                 //��ȡDS1302�� ��				
	write1632GDRAM(4,3,num1632[min/16]);
	write1632GDRAM(5,3,num1632[min%16]);
	write1632GDRAM(6,3,num1632[10]);        //ʱ�ӷָ�����:��

/*��Һ������д ���� ����-----------------------------------------*/
	sec= read_clock(0x81);                  //��ȡDS1302�� ��
	write1632GDRAM(7,3,num1632[sec/16]);
	write1632GDRAM(8,3,num1632[sec%16]);
/*
	write_com(0x30);
	write_com(0x06);
	write_com(0x9d);
	lcm_w_test(1,(sec/16+0x30));	
	lcm_w_test(1,(sec%16+0x30));
*/	
}

 
/*��ʾ��Ф-----------------------------------------------------*/
void lcm_w_nl(void){
	unsigned char LunarYearD,ReYear,tiangan,dizhi;        //ũ����ݵ�ʮ������  ��ȡģ������� 

	//���ú�����,ԭ�����ݲ���,��c_moonũ������,year_moonũ����,month_moon,day_moon�ó�����BCD����
	write_com(0x88);
	LunarYearD=(year_moon/16)*10+year_moon%16;        //ũ����ת����10������ 
	ReYear=LunarYearD%12;                             //ũ����ģ12,ȡ������
	tiangan=LunarYearD%10;	 //���  �ס���.....
	dizhi=LunarYearD%12;	 //��֧  �ӡ���.....

	switch(tiangan)
	{
		case 0: write_com(0x90);lcm_w_word("��");break;   //��0������ ���  ��
		case 1: write_com(0x90);lcm_w_word("��");break;   //
		case 2: write_com(0x90);lcm_w_word("��");break;
		case 3: write_com(0x90);lcm_w_word("��");break;
		case 4: write_com(0x90);lcm_w_word("��");break;
		case 5: write_com(0x90);lcm_w_word("��");break;
		case 6: write_com(0x90);lcm_w_word("��");break;
		case 7: write_com(0x90);lcm_w_word("��");break;
		case 8: write_com(0x90);lcm_w_word("��");break;
		case 9: write_com(0x90);lcm_w_word("��");break;
	}

	switch(dizhi)
	{
		case 0: write_com(0x91);lcm_w_word("��");break;   //��0������ ��֧ ��
		case 1: write_com(0x91);lcm_w_word("��");break;   //
		case 2: write_com(0x91);lcm_w_word("��");break;
		case 3: write_com(0x91);lcm_w_word("δ");break;
		case 4: write_com(0x91);lcm_w_word("��");break;
		case 5: write_com(0x91);lcm_w_word("��");break;
		case 6: write_com(0x91);lcm_w_word("��");break;
		case 7: write_com(0x91);lcm_w_word("��");break;
		case 8: write_com(0x91);lcm_w_word("��");break;
		case 9: write_com(0x91);lcm_w_word("��");break;
		case 10:write_com(0x91);lcm_w_word("��");break;
		case 11:write_com(0x91);lcm_w_word("î");break;
	}

	switch(ReYear)
	{
		case 0: write_com(0x92);lcm_w_word("����");break;   //��0������ ũ�� ����
		case 1: write_com(0x92);lcm_w_word("����");break;   //����
		case 2: write_com(0x92);lcm_w_word("����");break;
		case 3: write_com(0x92);lcm_w_word("����");break;
		case 4: write_com(0x92);lcm_w_word("����");break;
		case 5: write_com(0x92);lcm_w_word("����");break;
		case 6: write_com(0x92);lcm_w_word("����");break;
		case 7: write_com(0x92);lcm_w_word("����");break;
		case 8: write_com(0x92);lcm_w_word("����");break;
		case 9: write_com(0x92);lcm_w_word("ţ��");break;
		case 10:write_com(0x92);lcm_w_word("����");break;
		case 11:write_com(0x92);lcm_w_word("����");break;
	}
}

/*��ʾũ������---------------------------------------------------------------*/
void displaynl(void)
{
	Conversion(century,year,month,date);	//����תũ��
	write_com(0x30); write_com(0x06); write_com(0x90);

/*****	��ʾũ���·�  *****/

	if (month_moon==1) {lcm_w_word("��");}
	if (month_moon==2) {lcm_w_word("��");}
//	if (month_moon==2) {lcm_w_word("��");}
	if (month_moon==3) {write_data(0xc8);write_data(0xfd);}	//"��"�ֵĴ���
	if (month_moon==4) {lcm_w_word("��");}
	if (month_moon==5) {lcm_w_word("��");}
	if (month_moon==6) {lcm_w_word("��");}
	if (month_moon==7) {lcm_w_word("��");}
	if (month_moon==8) {lcm_w_word("��");}
	if (month_moon==9) {lcm_w_word("��");}
	if (month_moon==10){lcm_w_word("ʮ");}
	if (month_moon==11){lcm_w_word("��");}
	if (month_moon==12){lcm_w_word("��");}
                       lcm_w_word("��");

/*****	��ʾũ���յ�ʮλ  *****/

  	if(day_moon/10==0)  {lcm_w_word("��");}    //
  	if(day_moon/10==1)  
		if(day_moon/10==1	&	day_moon%10==0) {lcm_w_word("��");}
		else	{lcm_w_word("ʮ");}    //
  	if(day_moon/10==2)      
  		if(day_moon/10==2	&	day_moon%10==0)  {lcm_w_word("��");}
		else  {lcm_w_word("إ");}   //
  	if(day_moon/10==3)  {write_data(0xc8);write_data(0xfd);}	  //"��"�ֵĴ���

/*****	��ʾũ���յĸ�λ  *****/

  	if(day_moon%10==1)  {lcm_w_word("һ");}    //
  	if(day_moon%10==2)  {lcm_w_word("��");}    //
  	if(day_moon%10==3)  {write_data(0xc8);write_data(0xfd);}	  //"��"�ֵĴ���
  	if(day_moon%10==4)  {lcm_w_word("��");}    //
  	if(day_moon%10==5)  {lcm_w_word("��");}    //
  	if(day_moon%10==6)  {lcm_w_word("��");}    //
  	if(day_moon%10==7)  {lcm_w_word("��");}    //
  	if(day_moon%10==8)  {lcm_w_word("��");}    //
  	if(day_moon%10==9)  {lcm_w_word("��");}    //
  	if(day_moon%10==0)  {lcm_w_word("ʮ");}    //

}

void nongli(void)//ũ�����ա���Ф��5�����ֻ���ʾ
{
	unsigned char ss;
	ss = read_clock(0x81);
	if(ss%16==5){displaynl();}//ÿ��5�����ũ��������ʾ�Ӻ���
	if(ss%16==0){lcm_w_nl();} //ÿ��5�����ũ����Ф��ʾ�Ӻ���
}

/*��ʾ��ӭ��Ϣ---------------------------------------------------------------*/
void welcome(void)
{								  
	write_com(0x81); lcm_w_word("���������"); 
	write_com(0x90); lcm_w_word("���ŷ��鲩��"); 	
	write_com(0x88); lcm_w_word("����13486324621"); 	
	write_com(0x98); lcm_w_word("�޸ģ�2019-11-30");	
}
/*---------------------------------------------------------------------------*/
#endif