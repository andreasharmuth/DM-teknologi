#include <LiquidCrystal.h>
boolean timer = false;
LiquidCrystal lcd(0,1,7,8,9,10);
int switchState = 0;
int prevSwitchState = 0;
int reply;
int i = 120;
boolean lock = false;
boolean lockavi = true;
boolean panik = false;
boolean dor = false;
unsigned long interval=1000;  // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
int las;
int vask;
int toilet;
int dor;
boolean sensorkali = false;
boolean sensortoilet = false;
boolean sensorlas = false;
boolean sensorvask = false;
boolean sensordor = false;
int t = 20; //kalibreringfaktor
int belysningsfaktor = 40;
int lastvask;
int lastlas;
int lastdor;
int lastToilet;
int lasNU;
int vaskNU;
int dorNU;
int toiletNU;
String d;

void setup(){
  for(int pinNumber = 2; pinNumber<9;pinNumber++){
    pinMode(pinNumber,OUTPUT);
  }
  lcd.begin(16,2);

    //seriel skal faktisk ikke bruges, fucker den med LCD?
    Serial.begin(9600);
  }
//4=rød,2=grøn,3=gul,5=lås,6=dør
void loop(){
  while (Serial.available() > 0) {
    d = Serial.readString();
    if (d == "p"){
      nt();
    }
    if (!panik){
      if (!sensorkali){
        if (!sensorlas){
          lastlas = las;
          las = analogRead(A1);
          if ((las < lastlas+t) && (las > lastlas-t)){
            sensorlas = true;
            digitalWrite(2,HIGH);
          }
        }
        if (!sensortoilet){
          lastToilet = toilet;
          toilet = analogRead(A4);
          if ((toilet < lastToilet+t) && (toilet > lastToilet-t)){
            sensortoilet = true;
          }
        }
        if (!sensorvask){
          lastvask = vask;
          vask = analogRead(A2);
          if ((vask < lastvask+t) && (vask > lastvask-t)){
            sensorvask = true;
            digitalWrite(3,HIGH);
          }
        }
        if (!sensordor){
          lastdor = dor;
          dor = analogRead(A3);
          if ((dor < lastdor+t) && (dor > lastdor-t)){
            sensordor = true;
            digitalWrite(4,HIGH);
          }
        }
                //Kali updater
                delay(500);
              }
              if (sensorlas && sensorvask && sensordor &&sensortoilet){

                digitalWrite(4,LOW);
                digitalWrite(2,LOW);
                digitalWrite(3,LOW);
                delay(500);
                digitalWrite(4,HIGH);
                digitalWrite(2,HIGH);
                digitalWrite(3,HIGH);
                delay(500);
                digitalWrite(4,LOW);
                digitalWrite(2,LOW);
                digitalWrite(3,LOW);
                sensorkali = true;
              }


              if (sensorkali){
                lasNU = analogRead(A1);
                vaskNU = analogRead(A2);
                dorNU = analogRead(A3);
                toiletNU = analogRead(A4);

                if (lock && !lockavi){
                  digitalWrite(4,HIGH);
                  digitalWrite(2,LOW);
                  digitalWrite(3,LOW);
                  digitalWrite(5,HIGH);
                }
                if (lock && lockavi){
                  digitalWrite(4,LOW);
                  digitalWrite(2,LOW);
                  digitalWrite(3,HIGH);
                }
                if (!lock){
                  digitalWrite(4,LOW);
                  digitalWrite(2,HIGH);
                  digitalWrite(3,LOW);
                  digitalWrite(5,LOW);
                  delay(1000);
                }
                if (lockavi && !lock){
                  Serial.println(vask);
                  if (dor<dor-belysningsfaktor){
                        //lukker døren selv?? boolean den efter shit
                        digitalWrite(6, HIGH);
                      }
                    }
                    if (lasNU<las-belysningsfaktor){
                      lock = true;
                      lockavi = false;

                    }
                    if (!lockavi){

                      if (vaskNU<vask-belysningsfaktor){
                        lockavi = true;
                        timer = false;

                      }
                    }
                    if (lockavi && lock){
                      if (lasNU<las-belysningsfaktor){
                        lock = false;
                      }
                    }
                    if (!timer){
                      lcd.setCursor(0,0);
                      lcd.print ("Husk at skylde  ");
                      lcd.setCursor(0,1);
                      lcd.print ("ud efter brug");
                      toilet = analogRead(A4);
                    }

                    if ((toilet < toilet-belysningsfaktor) && (!timer)){
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

                    }
                    //skal det evt. laves med milli??? - skal det være der?
                    delay(1000);
                  }
                }
              }
            }



            void nt(){
              panik = true;
              digitalWrite(5,LOW);
              digitalWrite(6,HIGH);
              lock=false;
              lockavi = true;
            }