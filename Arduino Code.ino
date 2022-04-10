#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
Servo myservo;

#define echo1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trig1 3 //attach pin D3 Arduino to pin Trig of HC-SR0

#define echo2 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trig2 5 //attach pin D3 Arduino to pin Trig of HC-SR0
long duration1,duration2; // variable for the duration of sound wave travel
int distance1,distance2; // variable for the distance measurement
int sw=6;
int mois=A0;
int mois_val=0;
int prox=8;
/*long duration;
int distanceCm;
*/
LiquidCrystal_I2C lcd(0x27,16,2);
void dis1();
void dis2();
void setup()
{ lcd.init();
  lcd.init();
  lcd.backlight();
  pinMode(trig1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trig2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo2, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrlcd.begin(16,2);
  Serial.begin(9600);
  myservo.attach(10);
  pinMode(prox,INPUT);
  myservo.write(90);
  delay(2000);
  lcd.clear();
}

void loop()
{   mois_val=analogRead(mois);
    // Serial.println(mois_val);
     
  if(digitalRead(prox)==HIGH)
  {
    delay(1000);
     if(mois_val<=700)
     { Serial.println("Wet");
      lcd.setCursor(0,0);
      lcd.print("Wet Waste");
      delay(2000);
      lcd.clear();
      myservo.write(180);
      delay(500);
      myservo.write(90);
      delay(500);
       }
     else
     { Serial.println("Dry");
      lcd.setCursor(0,0);
      lcd.print("Dry Waste");
      delay(2000);
      lcd.clear();
      myservo.write(0);
      delay(500);
      myservo.write(90);
      delay(500);
      }
  }
  if(digitalRead(sw)==HIGH)
  {
    dis1();
    dis2();
    delay(2000);
  }

 }
void dis1()
{  
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echo1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.setCursor(10,0);
  //int dis1=20-(distance1-25);
  //lcd.print((dis1/20)*100);
  lcd.print(distance1);
  Serial.println(distance1);
  /*lcd.setCursor(15,2);
  lcd.print("%");
 // Serial.println(" cm");
 */ delay(10);
}
void dis2()
{
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echo2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.setCursor(10,1);
 // int dis2=20-(distance2-25);
  
  lcd.print(distance2);
//  Serial.println("%");
  /*lcd.setCursor(15,3);
  lcd.print("%");
  */delay(10);
}
