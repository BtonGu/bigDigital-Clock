#ifndef __displaytime_H__ 
#define __displaytime_H__ 
#include "nongli.h"
uchar sec,min,hour,day,date,month,year,week,day_moon;

/*显示年、月、日、星期-------------------------------------------------------*/
void displaydate(void)
{
	write_com(0x30);
	write_com(0x06);

/*往液晶屏填写 年 数据-------------------------------------------*/
	write_com(0x80);
	lcm_w_word("20");	
	year=read_clock(0x8d);//调用1302时钟数据中的年数据，从地址0x8d中
	write_data(year/16+0x30);	
	write_data(year%16+0x30);
//	lcm_w_word("年");
	
/*往液晶屏填写 月 数据-------------------------------------------*/
	month=read_clock(0x89);//调用1302时钟数据中的月数据，从地址0x89中
	lcm_w_word("-");	
	
/*	if(month/16 != 0){	  //十位消隐
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
//	lcm_w_word("月");	

/*往液晶屏填写 日 数据-------------------------------------------*/
	date=read_clock(0x87);//从1302芯片中读取日数据，从地址0x87中
	lcm_w_word("-");
/*
	if(date/16 !=0){			  //十位消隐
		write1632GDRAM(2,2,num1632[date/16]);
		write1632GDRAM(3,2,num1632[date%16]);}
	else
				write1632GDRAM(3,2,num1632[date%16]);
*/
	lcm_w_test(1,(date/16+0x30));
	lcm_w_test(1,(date%16+0x30)); 

//	lcm_w_word("日");
}

/*往液晶屏填写 星期 数据-----------------------------------------*/
void displayxq(void){

	unsigned char sel,dd,mo,yy;

	dd = read_clock(0x87);//日
	mo = read_clock(0x89);//月
	yy = read_clock(0x8d);//年
	Conver_week(0,yy,mo,dd);//调用公历换算星期子函数
   sel=week;//week是公历转换星期子函数的运行结果，结果为0-6，0是星期日
	write_com(0x87);//显示位置
	if(sel==0)  {lcm_w_word("日");}    //0=星期日
  	if(sel==6)  {lcm_w_word("六");}    //
  	if(sel==5)  {lcm_w_word("五");}    //
  	if(sel==4)  {lcm_w_word("四");}    //
//	if(sel==3)  {lcm_w_word("三");}//经调试发现液晶屏不认这一句，只好用下一句显示 三	。需要打补丁才能正确显示。
	if(sel==3)  {write_data(0xc8);write_data(0xfd);} //此指令等于lcm_w_word("三"); 因为“三”的内码失效。
  	if(sel==2)  {lcm_w_word("二");}    //
  	if(sel==1)  {lcm_w_word("一");}    //星期一
	write_com(0x85);
	lcm_w_word("星期");//调用字符显示子函数，显示 星期 两个字

}
/*需要绘图显示的:时、分、秒--------------------------------------------------*/
void displaytime(void)
{
/*往液晶屏填写 小时 数据-----------------------------------------*/
	hour = read_clock(0x85);					 //读取DS1302的 时
	write1632GDRAM(1,3,num1632[hour/16]);
	write1632GDRAM(2,3,num1632[hour%16]);
	write1632GDRAM(3,3,num1632[10]);        //时钟分隔符“:”
	 //以下加eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	//	 if(hour> 12)					   //加
	//	 	hour = hour-12;			   //加

/*往液晶屏填写 分钟 数据-----------------------------------------*/
	min = read_clock(0x83);                 //读取DS1302的 分				
	write1632GDRAM(4,3,num1632[min/16]);
	write1632GDRAM(5,3,num1632[min%16]);
	write1632GDRAM(6,3,num1632[10]);        //时钟分隔符“:”

/*往液晶屏填写 秒钟 数据-----------------------------------------*/
	sec= read_clock(0x81);                  //读取DS1302的 秒
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

 
/*显示生肖-----------------------------------------------------*/
void lcm_w_nl(void){
	unsigned char LunarYearD,ReYear,tiangan,dizhi;        //农历年份的十进制数  和取模后的余数 

	//调用函数后,原有数据不变,读c_moon农历世纪,year_moon农历年,month_moon,day_moon得出阴历BCD数据
	write_com(0x88);
	LunarYearD=(year_moon/16)*10+year_moon%16;        //农历年转换成10进制数 
	ReYear=LunarYearD%12;                             //农历年模12,取余运算
	tiangan=LunarYearD%10;	 //天干  甲、乙.....
	dizhi=LunarYearD%12;	 //地支  子、丑.....

	switch(tiangan)
	{
		case 0: write_com(0x90);lcm_w_word("庚");break;   //余0即整除 天干  庚
		case 1: write_com(0x90);lcm_w_word("辛");break;   //
		case 2: write_com(0x90);lcm_w_word("壬");break;
		case 3: write_com(0x90);lcm_w_word("癸");break;
		case 4: write_com(0x90);lcm_w_word("甲");break;
		case 5: write_com(0x90);lcm_w_word("乙");break;
		case 6: write_com(0x90);lcm_w_word("丙");break;
		case 7: write_com(0x90);lcm_w_word("丁");break;
		case 8: write_com(0x90);lcm_w_word("戊");break;
		case 9: write_com(0x90);lcm_w_word("已");break;
	}

	switch(dizhi)
	{
		case 0: write_com(0x91);lcm_w_word("辰");break;   //余0即整除 地支 辰
		case 1: write_com(0x91);lcm_w_word("巳");break;   //
		case 2: write_com(0x91);lcm_w_word("午");break;
		case 3: write_com(0x91);lcm_w_word("未");break;
		case 4: write_com(0x91);lcm_w_word("申");break;
		case 5: write_com(0x91);lcm_w_word("酉");break;
		case 6: write_com(0x91);lcm_w_word("戌");break;
		case 7: write_com(0x91);lcm_w_word("亥");break;
		case 8: write_com(0x91);lcm_w_word("子");break;
		case 9: write_com(0x91);lcm_w_word("丑");break;
		case 10:write_com(0x91);lcm_w_word("寅");break;
		case 11:write_com(0x91);lcm_w_word("卯");break;
	}

	switch(ReYear)
	{
		case 0: write_com(0x92);lcm_w_word("龙年");break;   //余0即整除 农历 龙年
		case 1: write_com(0x92);lcm_w_word("蛇年");break;   //蛇年
		case 2: write_com(0x92);lcm_w_word("马年");break;
		case 3: write_com(0x92);lcm_w_word("羊年");break;
		case 4: write_com(0x92);lcm_w_word("猴年");break;
		case 5: write_com(0x92);lcm_w_word("鸡年");break;
		case 6: write_com(0x92);lcm_w_word("狗年");break;
		case 7: write_com(0x92);lcm_w_word("猪年");break;
		case 8: write_com(0x92);lcm_w_word("鼠年");break;
		case 9: write_com(0x92);lcm_w_word("牛年");break;
		case 10:write_com(0x92);lcm_w_word("虎年");break;
		case 11:write_com(0x92);lcm_w_word("兔年");break;
	}
}

/*显示农历日期---------------------------------------------------------------*/
void displaynl(void)
{
	Conversion(century,year,month,date);	//公历转农历
	write_com(0x30); write_com(0x06); write_com(0x90);

/*****	显示农历月份  *****/

	if (month_moon==1) {lcm_w_word("正");}
	if (month_moon==2) {lcm_w_word("二");}
//	if (month_moon==2) {lcm_w_word("三");}
	if (month_moon==3) {write_data(0xc8);write_data(0xfd);}	//"三"字的代码
	if (month_moon==4) {lcm_w_word("四");}
	if (month_moon==5) {lcm_w_word("五");}
	if (month_moon==6) {lcm_w_word("六");}
	if (month_moon==7) {lcm_w_word("七");}
	if (month_moon==8) {lcm_w_word("八");}
	if (month_moon==9) {lcm_w_word("九");}
	if (month_moon==10){lcm_w_word("十");}
	if (month_moon==11){lcm_w_word("冬");}
	if (month_moon==12){lcm_w_word("腊");}
                       lcm_w_word("月");

/*****	显示农历日的十位  *****/

  	if(day_moon/10==0)  {lcm_w_word("初");}    //
  	if(day_moon/10==1)  
		if(day_moon/10==1	&	day_moon%10==0) {lcm_w_word("初");}
		else	{lcm_w_word("十");}    //
  	if(day_moon/10==2)      
  		if(day_moon/10==2	&	day_moon%10==0)  {lcm_w_word("二");}
		else  {lcm_w_word("廿");}   //
  	if(day_moon/10==3)  {write_data(0xc8);write_data(0xfd);}	  //"三"字的代码

/*****	显示农历日的个位  *****/

  	if(day_moon%10==1)  {lcm_w_word("一");}    //
  	if(day_moon%10==2)  {lcm_w_word("二");}    //
  	if(day_moon%10==3)  {write_data(0xc8);write_data(0xfd);}	  //"三"字的代码
  	if(day_moon%10==4)  {lcm_w_word("四");}    //
  	if(day_moon%10==5)  {lcm_w_word("五");}    //
  	if(day_moon%10==6)  {lcm_w_word("六");}    //
  	if(day_moon%10==7)  {lcm_w_word("七");}    //
  	if(day_moon%10==8)  {lcm_w_word("八");}    //
  	if(day_moon%10==9)  {lcm_w_word("九");}    //
  	if(day_moon%10==0)  {lcm_w_word("十");}    //

}

void nongli(void)//农历月日、生肖按5秒间隔轮换显示
{
	unsigned char ss;
	ss = read_clock(0x81);
	if(ss%16==5){displaynl();}//每隔5秒调用农历月日显示子函数
	if(ss%16==0){lcm_w_nl();} //每隔5秒调用农历生肖显示子函数
}

/*显示欢迎信息---------------------------------------------------------------*/
void welcome(void)
{								  
	write_com(0x81); lcm_w_word("爱尚你婚庆"); 
	write_com(0x90); lcm_w_word("东门坊婚博会"); 	
	write_com(0x88); lcm_w_word("热线13486324621"); 	
	write_com(0x98); lcm_w_word("修改：2019-11-30");	
}
/*---------------------------------------------------------------------------*/
#endif