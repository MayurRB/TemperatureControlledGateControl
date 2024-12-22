
////Servo : 
//Libraries 
#include <Servo.h>
//Variables
int Door = 10;
Servo right;


//// PIR 
//Variables
int pir = 2;
int motion;


////MLX TEMP : 
//Libraries : 
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


////LCD : 
//Libraries : 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//Variables : 
String val;
String oldVal;
String newVal;

////LED : 
//Variables :
int ledPin = 13;



void setup() {
  Serial.begin(9600);

  //Servo : 
  pinMode(Door,OUTPUT);
  right.attach(Door);

  //PIR : 
  pinMode(pir,INPUT);

  //MLX TEMP : 
  mlx.begin();
  
  //LCD: 
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);


  //LED : 
  pinMode(ledPin,OUTPUT);

  //Setup Code : 
  lcdp("Smart Covid ","  Door ");
  
}

void loop() {

  //PIR 
  motion = digitalRead(pir);

  //MLX TEMP : 
  float temperature = mlx.readObjectTempC();
  Serial.println(motion);
  Serial.println(temperature);
  
  //LOGIC :

  if(motion)
  {
    lcdp("Person Detected ","");
    lcdp("Temperature : ","");
    lcdn(temperature);


    
    //Code to run if the Person is Detected (i.e Person Near MLX)  : 
    if(temperature > 38 ){

      
      //Code for Person Detected With Covid : 
      lcdp("Person Detected ", " with Covid .");
      light(5);
      
      }
      else 
      {

        //Code for Safe Person  : 
        lcdp("Person Safe : ","Gate Opening : ");
        
        gate();
        
        }

    
    }
    
    else
    {
      //Code to run if No person Detected : 
      lcdp("No Person"," Detected : ");
      }

  

}

//ServoFunctions : 

void gate(){
  right.write(0);
  delay(5000);
  right.write(90);

  }

//LCDFunctions : 

void lcdp(String x,String y){
lcd.clear();
lcd.setCursor(1,0);
lcd.print(x);
lcd.setCursor(1,1);
lcd.print(y);

delay(2500);

}

void lcdn(float x){

lcd.setCursor(1,1);
lcd.print(x);

delay(2500);
  
  }

void light(int y){
  for(int i = 0; i < y;i++)
  {
    //Blinks LED 5 Times : 
  digitalWrite(ledPin,HIGH);
  delay(1000);
  digitalWrite(ledPin,LOW);
  delay(1000);
  }
  //Sets LED OFF as Default State
  digitalWrite(ledPin,LOW);
  }
