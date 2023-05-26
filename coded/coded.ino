#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo_1;
Servo servo_2;

int speed = 11;
int in1 = 10;


int metal_sayisi = 0;
int cam_sayisi = 0;
int plastik_sayisi = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial){}

  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  servo_1.attach(8);
  servo_2.attach(9);
  servo_1.write(0);
  servo_2.write(0);

  pinMode(speed, OUTPUT);
  pinMode(in1, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("M: " + String(metal_sayisi)+ "     " + " C: " + String(cam_sayisi));
  lcd.setCursor(0, 1);
  lcd.print("     P: " + String(plastik_sayisi));
}


void loop() {

  if(Serial.available()>0){

    String message = Serial.readStringUntil('\n');
    delay(15);

    if(message == "Plastic"){
      plastik_sayisi += 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("M: " + String(metal_sayisi)+ "     " + " C: " + String(cam_sayisi));
      lcd.setCursor(0, 1);
      lcd.print("     P: " + String(plastik_sayisi));

      servo_1.write(75);
      servo_2.write(0);

      digitalWrite(in1, HIGH);
      analogWrite(speed,255);
      delay(15000);     
      digitalWrite(in1, LOW);
      analogWrite(speed,0);
    }

    if(message == 'Glass'){

      cam_sayisi +=1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("M: " + String(metal_sayisi)+ "     " + " C: " + String(cam_sayisi));
      lcd.setCursor(0, 1);
      lcd.print("     P: " + String(plastik_sayisi));

      servo_1.write(0);
      servo_2.write(0);     

      digitalWrite(in1, HIGH);
      analogWrite(speed,255);
      delay(10000);     
      digitalWrite(in1, LOW);
      analogWrite(speed,0);
          
    }

    if(message == 'Metal'){

      metal_sayisi +=1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("M: " + String(metal_sayisi)+ "     " + " C: " + String(cam_sayisi));
      lcd.setCursor(0, 1);
      lcd.print("     P: " + String(plastik_sayisi));  

      servo_1.write(0);
      servo_2.write(50);

      digitalWrite(in1, HIGH);
      analogWrite(speed,255);
      delay(15000);     
      digitalWrite(in1, LOW);
      analogWrite(speed,0);
    }
  
  }

  lcd.setCursor(0, 0);
  lcd.print("M: " + String(metal_sayisi)+ "     " + " C: " + String(cam_sayisi));
  lcd.setCursor(0, 1);
  lcd.print("     P: " + String(plastik_sayisi));

}



