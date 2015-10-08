
boolean lockavi = true;


#include <LiquidCrystal.h>
int toilet;
boolean timer = false;
LiquidCrystal lcd(0,1,7,8,9,10);
int switchState = 0;
int prevSwitchState = 0;
int reply;
int i = 120;

void setup()
{
	lcd.begin(16,2);

}
void loop(){
	if (!timer){
		lcd.setCursor(0,0);
		lcd.print ("Husk at skylde  ");
		lcd.setCursor(0,1);
		lcd.print ("ud efter brug");
		toilet = analogRead(A4);
	}

	if (toilet < 400 && !timer){
		timer = true;
		lcd.setCursor(0,0);
		lcd.print ("                 ");
		lcd.setCursor(0,1);
		lcd.print ("                 ");
		lcd.setCursor(0,0);     
		lcd.print ("Ventetid:");
		lcd.setCursor(4,1);
		lcd.print ("sekunder");
	}
	if (timer){
		if (i>0){
			lcd.setCursor(0,1);
			lcd.print(i);
			i--;
		}
		if (i==99){
			lcd.setCursor(2,1);
			lcd.print(" ");
			lcd.setCursor(3,1);
			lcd.print ("sekunder  ");
			i--;
		}
		if (i==9){
			lcd.setCursor(1,1);
			lcd.print(" ");
			lcd.setCursor(2,1);
			lcd.print ("sekunder  ");
			i--;
		}
		if (i==0){
			lcd.setCursor(0,0);  
			lcd.print ("Ventetiden er nu");    
			lcd.setCursor(0,1);  
			lcd.print ("forbi             ");  
			boolean lockavi = true;
			
		}
		if (i==0 && timer){
			delay(2000);
			timer = false;
			i = 120;
		}
		delay(50);
	}
}