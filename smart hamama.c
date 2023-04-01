#include "REG_89C51.h"	// REG_89C51.h כלילת ספריה בשם
#include "i2c.h"		// lcd.h כלילת ספריה בשם
#include "lcd.h"		// lcd.h כלילת ספריה בשם
#include "pinim.h"		// pinim.h כלילת ספריה בשם
#include "delays.h"		// delays.h כלילת ספריה בשם
#include "uart.h"		// uart.h כלילת ספריה בשם 

void read_metah(void);	// שלא מקבלת ערכים ולא מחזירה ערכים read_metah הכרזת פונקציה בשם
void read_temper(void);	// שלא מקבלת ערכים ולא מחזירה ערכים read_temper הכרזת פונקציה בשם
void init_pwm(void); // שלא מקבלת ערכים ולא מחזירה ערכים init_pwm הכרזת פונקציה בשם
void servo(void); // שלא מקבלת ערכים ולא מחזירה ערכים servo הכרזת פונקציה בשם

unsigned int  volt;		// הגדרת משתנה 16 ביט ללא סימן
unsigned char temp,fb;	// הגדרת משתנים בגודל 8 סיביות ללא סימן
unsigned char sekonds;	// הגדרת משתנים בגודל 8 סיביות ללא סימן
unsigned char minutes;	// הגדרת משתנים בגודל 8 סיביות ללא סימן
unsigned char hour;		// הגדרת משתנים בגודל 8 סיביות ללא סימן
unsigned char zmanH;	// הגדרת משתנים בגודל 8 סיביות ללא סימן
unsigned char zmanM;	// הגדרת משתנים בגודל 8 סיביות ללא סימן
char y; // הגדרת משתנה בגודל 8 סיביות
unsigned char volt1,volt2,volt3; // הגדרת משתנים בגודל 8 סיביות ללא סימן

void servo()// בנית פונק' עבור הכוונת רוטור של מנוע סרבו
{
	CCAP0L=y;//קביעת ערך התחלתי עבור מצב טעינה אוטומטית
	CCAP0H=0xff-y;//קביעת ערך עבור מצב טעינה אוטומטית

  CCON= 0x40;//01000000 CR=1   PCA הדלקת
	
	
}

void psikat_uart() interrupt 4// UART בניית פונקציה המשמשת כפסיקת 
{
			if(SBUF=='3') // במידה והתקבל קוד 1, הכנס לתנאי
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך 
		print_lcd (0x00, "Tris-OPEN");// קריאה לפונקציה להדפסת מחרוזת
		y=22;// קביעת ערך המשפיע על הכוונת רוטור של מנוע סרבו
		
		msec(10);// קריאה לפונקצית השהיה
	}
	
		if (SBUF=='4')//במידה והתקבל קוד 3, הכנס לתנאי 
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך
		print_lcd(0x00, "Tris-CLOSED");// קריאה לפונקציה להדפסת מחרוזת
		y=9;// קביעת ערך המשפיע על הכוונת רוטור של מנוע סרבו
		
		
		msec(10);// קריאה לפונקצית השהיה
	}
		if (SBUF=='1') // במידה והתקבל קוד 4, הכנס לתנאי
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך
		print_lcd(0x00, "Valve-Open");// קריאה לפונקציה להדפסת מחרוזת
		valve=1;// פתיחת שסתום השקיה
		
		msec(10);// קריאה לפונקצית השהיה
	}
	
		if (SBUF=='2') // במידה והתקבל קוד5, הכנס לתנאי
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך
		print_lcd(0x00, "Valve-CLOSED");// קריאה לפונקציה להדפסת מחרוזת
		valve=0;// סגירת שסתום השקיה
		
		
		msec(10);// קריאה לפונקצית השהיה
	}
	 if (SBUF=='6') // במידה והתקבל קוד 6, הכנס לתנאי
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך
		print_lcd(0x00, "lightbulb-ON");// קריאה לפונקציה להדפסת מחרוזת
		lightbulb=1;// הדלקת נורה
		
		
		msec(10);// קריאה לפונקצית השהיה
	}
	if (SBUF=='7') // במידה והתקבל קוד5, הכנס לתנאי
	{
		wr_com_to_lcd(clr_disp); //LCD קריאה לפונקציה ניקוי מסך
		print_lcd(0x00, "lightbulb-OFF");// קריאה לפונקציה להדפסת מחרוזת
		lightbulb=0;//כיבוי נורה
		
		
		msec(10);// קריאה לפונקצית השהיה
	}
	
	
	CCAP0L=y;//קביעת ערך התחלתי עבור מצב טעינה אוטומטית
	CCAP0H=0xff-y;//קביעת ערך עבור מצב טעינה אוטומטית

  CCON= 0x40;//01000000 CR=1   PCA הדלקת
		
	RI=0;// RI איפוס דגל 	
		

	}

void init_pwm()//pmw-לטובת שימוש ב pca איתחול חומרה בשם
{
	TMOD|=0x02;// טיימר אפס טעינה אוטומטית
	TH0= 184;// timer // 20ms זמן מחזור
	TCON|=0x10;//הפעלת טיימר אפס
	
	
 	CCAPM0= 0x42;//01000010 ECOM0=1,PWM0=1	 //  enable comparator , PWM הדלקת 
  CMOD  = 0x84;//10000000 CIDL=1 	// PCA שימוש במתנד פנימי עבור 
}

//void update_time(void)	// פונקצייה לעידכון זמן 	 
//{
//    i2c_start();		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
//   i2c_write(0xD0);	// פנייה לשעון RTC
//    msec(1);			// קריאה לפונקציה לטובת השהייה
//    i2c_write(0x00);	// פנייה לאוגר שניות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_write(0x00);    // כתיבת שניות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_stop();			// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
//	
//	i2c_start();		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
//   i2c_write(0xD0);	// פנייה לשעון RTC
//    msec(1);			// קריאה לפונקציה לטובת השהייה
//    i2c_write(0x01);	// פנייה לאוגר דקות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_write(0x53);    // כתיבת דקות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_stop();			// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
//	
//	
//	i2c_start();		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
//   i2c_write(0xD0);	// פנייה לשעון RTC
//    msec(1);			// קריאה לפונקציה לטובת השהייה
//    i2c_write(0x02);	// פנייה לאוגר שעות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_write(0x11);    // כתיבת שעות
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_stop();			// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
//  	
//    //////סיום הגדרת זמן
//		////// איתחול RTC
//	
//	i2c_start();		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
//    i2c_write(0xD0);	// פנייה לשעון RTC
//    msec(1);			// קריאה לפונקציה לטובת השהייה
//   i2c_write(0x0E);	// פניה לאוגר בקרה (CONTROL)
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_write(0x98);    // כתיבת מילת בקרה להפעלת ספירה .... dynamic Clock enable 
//	msec(1);			// קריאה לפונקציה לטובת השהייה
//	i2c_stop();			// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
//}

void	read_time() 	// פונקציה לקריאת זמן עדכני מהשעון
{
	
    print_lcd(0x00,"Time:"); // הדפסת מחרוזת על המסך
	i2c_start();		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
    i2c_write(0xD0);	// פנייה לשעון RTC
    msec(1);			// קריאה לפונקציה לטובת השהייה
    i2c_write(0x02);	// פנייה לאוגר מכיל שעות
    msec(1);			// קריאה לפונקציה לטובת השהייה
	 
	i2c_start();       	// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
	i2c_write(0xD1);	// פנייה לשעון RTC 
	msec(1);			// קריאה לפונקציה לטובת השהייה
	
	hour=i2c_read(NACK);	// קריאת שעה מהשעון
    msec(1);				// קריאה לפונקציה לטובת השהייה
	 	 
    i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
	zmanH=hour;					
	wr_data_to_lcd((hour>>4)+0x30); 	//הצגת שעה על המסך: עשרות
    wr_data_to_lcd((hour&0x0F)+0x30);	//הצגת שעה על המסך: אחדות
	
	wr_data_to_lcd(':');//נקודתיים לטובת הפרדה בין יחידות זמן
		
    i2c_start();			// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת	  
    i2c_write(0xD0);		// פנייה לשעון RTC
    msec(1);				// קריאה לפונקציה לטובת השהייה
    i2c_write(0x01);		// פנייה לאוגר מכיל דקות
    msec(1);				// קריאה לפונקציה לטובת השהייה
	 
	i2c_start();      		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
	i2c_write(0xD1);		// פנייה לאוגר מכיל דקות 
	msec(1);				// קריאה לפונקציה לטובת השהייה
	
	 
	minutes=i2c_read(NACK);	// קריאת דקות מהשעון RTC
    msec(1);				// קריאה לפונקציה לטובת השהייה
	 	 
    i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
	zmanM=minutes;//העברת דקות למשתנה אחר
	 
	wr_data_to_lcd((minutes>>4)+0x30);		//הצגת דקות על המסך: עשרות
    wr_data_to_lcd((minutes&0x0F)+0x30);	//הצגת דקות על המסך: אחדות
	 
	 
	wr_data_to_lcd(':');		//הצגת סימן על המסך
	 
	 
	i2c_start();		 	// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
    i2c_write(0xD0);		// פנייה לשעון RTC
    msec(1);				// קריאה לפונקציה לטובת השהייה
    i2c_write(0x00);		// פנייה לאוגר מכיל שניות
	msec(1);				// קריאה לפונקציה לטובת השהייה
	 
	i2c_start();       		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
	i2c_write(0xD1);		// פנייה לאוגר מכיל שניות
	msec(1);				// קריאה לפונקציה לטובת השהייה

	 
	sekonds=i2c_read(NACK);	// קריאת שניות מהשעון RTC
    msec(1);				// קריאה לפונקציה לטובת השהייה
	 	 
    i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
	 
	 
	 
 
	wr_data_to_lcd((sekonds>>4)+0x30);		//הצגת שניות על המסך: עשרות
    wr_data_to_lcd((sekonds&0x0F)+0x30);	//הצגת שניות על המסך: אחדות
	 
	 


    msec(100);		// קריאה לפונקציה לטובת השהייה
	 
	if (((zmanH>0x18)&&(zmanM>0x05))||(zmanH<0x08)||(zmanH>0x19)) // בדיקת תנאי: האם היגיע זמן מסויים?
	{			 
		wr_com_to_lcd(clr_disp); 	// קריאה לפונקציית ניקוי מסך
		msec(2);					// קריאה לפונקציה לטובת השהייה
		print_lcd(0x00,"ZMAN");		// קריאה לפונקציית הדפסת מחרוזת על המסך
		valve=0;					// סגירת שסתום השקיה
		msec(100);	 				// קריאה לפונקציה לטובת השהייה
	}
	 
 }
	

void read_metah()			// פונקצייה לקריאת מתח מהממיר
	
{
		
    i2c_start();		   	// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
    i2c_write(0x90);		// PCF8591 פנייה לממיר

    usec(3);				// קריאה לפונקציה לטובת השהייה
    i2c_write(0x00);		// עבודה עם ערוץ של הממיר
    i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת

	msec(4);				// קריאה לפונקציה לטובת השהייה
	i2c_start();			// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
	i2c_write(0x91);   		// קריאת מספר המתאר מתח מהממיר
    msec(4);				// קריאה לפונקציה לטובת השהייה
	fb = i2c_read(ACK); //A/D מקבל ערך תוצאת המרה מהממיר fb משתנה
	fb = i2c_read(ACK); //A/D מקבל ערך תוצאת המרה מהממיר fb משתנה
	fb = i2c_read(NACK); //A/D מקבל ערך תוצאת המרה מהממיר fb משתנה
	i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת
    msec(100);				// קריאה לפונקציה לטובת השהייה

	volt=((fb*5)/(2.55));   // המרת מספר לטובת הצגה על המסך
	
	if (fb<103) valve=0;

    wr_com_to_lcd(clr_disp);		// קריאת פונקצייה לניקוי מסך
	wr_data_to_lcd(volt/100+'0');	// הצגת מתח נימדד על המסך
	temp=volt%100;					// הכנת משתנה מכיל שארית של המספר



    print_lcd(0x01, ".");			// הדפסת סימן על המסך

	wr_data_to_lcd(temp/10+'0');	// הצגת מתח נמדד על המסך: עשרות
	wr_data_to_lcd(temp%10+'0');	// הצגת מתח נמדד על המסך: אחדות

    print_lcd(0x05, "Volt");		// הצגת מחרוזת על המסך
	msec(100);						// קריאה לפונקציה לטובת השהייה
}



void read_temper(void)	   // פונקצייה למדידת טמפרטורה
 	 
{

unsigned char MBYTE,LBYTE;	 // הגדרת משתנים מקומיים בגודל 8ביט ללא סימן

	///////// מדידת חום


   wr_com_to_lcd(clr_disp);	// קריאת פונקצייה לניקוי מסך
  
   i2c_start();		   		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
   i2c_write(0x9E);		    // DS1621 פנייה לטרמומטר
   msec(2);					// קריאה לפונקציה לטובת השהייה
   i2c_write(0xEE);		 	// פקודה לתחילת המרה
   i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת

   msec(2);					// קריאה לפונקציה לטובת השהייה

   i2c_start();		  		// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
   i2c_write(0x9E);			// DS1621 פנייה לטרמומטר
   msec(2);					// קריאה לפונקציה לטובת השהייה
   i2c_write(0x22);		  	// פקודה לסיום המרה
   i2c_stop();				// i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת


   msec(8);					// קריאה לפונקציה לטובת השהייה

 	
   i2c_start();				// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
   i2c_write(0x9E);	  		// DS1621 פנייה לטרמומטר
   msec(2);					// קריאה לפונקציה לטובת השהייה

   i2c_write(0xAA);		 	// קריאת טמפרטורה
   msec(2);

    i2c_start();			// i2c קריאה לפונקציה לטובת תחילת מקטע בתקן תקשורת
    i2c_write(0x9F);		// DS1621 פנייה לטרמומטר
    msec(5);				// קריאה לפונקציה לטובת השהייה
    MBYTE=i2c_read(ACK);	// קריאת מספר מייצג טמפרטורה נמדדת 	
	msec(5);				// קריאה לפונקציה לטובת השהייה
	LBYTE=i2c_read(NACK);	// קריאת מספר מייצג טמפרטורה נמדדת 
	msec(5);				// קריאה לפונקציה לטובת השהייה

	i2c_stop();				//i2c קריאה לפונקציה לטובת סיום מקטע בתקן תקשורת

	msec(1); 				// קריאה לפונקציה לטובת השהייה


 wr_com_to_lcd(clr_disp);	// קריאת פונקצייה לניקוי מסך

 print_lcd(0x00, "TEMP:"); 	// הצגת מחרוזת על המסך

if(MBYTE>27) // המשך לתנאי במידה והטמפרטורה הנמדדת גבוהה מ27
{
	y=22;// קביעת ערך המשפיע על הכוונת רוטור של מנוע סרבו
	servo(); // servo קריאה לפונקציה 
}
	
wr_data_to_lcd(MBYTE/10+'0');		// הצגת טמפרטורה: עשרות
wr_data_to_lcd(MBYTE%10+'0');		// הצגת טמפרטורה: אחדות
 
if(LBYTE>0x00)   	print_lcd(0x07, ".5");	// הצגת שארית של המםפר מייצג טמפרטורה
if(LBYTE==0x00)  	print_lcd(0x07, ".0");	// הצגת שארית של המםפר מייצג טמפרטורה
 msec(100);				// קריאה לפונקציה לטובת השהייה


 }

 
void main()	 // הגדרת פונקציה הראשית 
{
 	valve=0;
	init_lcd();						// קריאה לפונקציה לאתחול מסך
 	msec(5);	  					// קריאה לפונקציה לטובת השהייה	
	wr_com_to_lcd(clr_disp); 		// קריאת פונקצייה לניקוי מסך
	msec(5);						// קריאה לפונקציה לטובת השהייה
	print_lcd(0x00, "23_05_2021d ");	// הצגת מחרוזת על המסך
	print_lcd(0xc0, "AMIR&ALEX");	// הצגת מחרוזת על המסך
	msec(200);						// קריאה לפונקציה לטובת השהייה
	
	
	init_pwm();//  PWM לטובת אות  PCA קריאה לפונק' לטובת איתחול חומרה 
	init_uart();//  UART קריאה לפונק' לטובת איתחול 
  wr_com_to_lcd(clr_disp); 		// קריאת פונקצייה לניקוי מסך

	EA=1;// ביטול מיסוך פסיקות מתן גישה לאיפשור פסיקות 
	ES=1;// UART איפשור פסיקת 
	
	while(1)						//לולה אין סופית
	{
    read_time();	// קריאה לפונקציה לצורך קבלת זמן עדכני 
	  read_temper();	// קריאה לפונקצית מדידת טמפרטורה
		read_metah();	// קריאה לפונקציה לצורך מדידת לחות של אדמה
		
	
		
	}

}