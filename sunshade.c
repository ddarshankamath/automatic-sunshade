#include <Servo.h>

int easternLight = 0, westernLight = 0, rainSensed = 0, sunshadePosition = 0, sunshadePosition2 = 0, rainRhreshold = 512, sunshadeExpanded = 40, sunshadeContracted = -40 , ambientLighting = 0, turnOnLightsOn = 150, ledIntensity = 0, ledPower = 0;
Servo servo, servo2;
char pos;
void setup()
{ Serial.begin(9600);
  pinMode(A4, OUTPUT); // Interior lighting of the bus stop
  pinMode(8, OUTPUT); // Street light
  pinMode(A1, INPUT); // Western light
  pinMode(A2, INPUT); // Eastern light
  pinMode(A5, INPUT); // Rain sensor analog
  pinMode(2, INPUT); // Rain sensor digital
  servo.attach(13);
  servo2.attach(12);// Servo
 //todo:
 //servo.write(sunshadePosition);
 //servo2.write(sunshadePosition2);
}

void loop()
{
  
  Serial.println("*************************************************************************************************");
  Serial.println("***********************************      BUS STOP       *****************************************");
  Serial.println("*************************************************************************************************");
  
  easternLight = analogRead(A2);
  westernLight = analogRead(A1);
  rainSensed = analogRead(A5);
  sunshadePosition = servo.read();
  sunshadePosition2 = servo2.read();
  if(westernLight>easternLight){
    pos="WEST";
  }
  else
  {
    pos="EAST";
  }
  //Serial.println("<<<");
  //Serial.println(westernLight);
  //Serial.println(easternLight);

  //Serial.println(rainSensed);
  if (  rainSensed < 500) { //raining
        Serial.println("Rain sensed : YES");
       // Serial.println("Sun position:%c",pos);
        Serial.println("LED Status : OFF");
         if (sunshadePosition != sunshadeExpanded) {
          servo.write(sunshadeExpanded);
          digitalWrite(8, HIGH);
        //delay(5000);
    }
   if ( sunshadePosition2 != sunshadeContracted) {
      servo2.write(sunshadeContracted);
    }

  }
  else {
    Serial.println("Rain sensed : NO");
        //Serial.println("Sun position:%c",pos);
        Serial.println("LED Status : ON");
    //Serial.println(westernLight);
    //Serial.println(">");
    ambientLighting = easternLight + westernLight; // Average the brightness of the east and west

    // It is not raining
    if (ambientLighting < 100) {
      // It's getting dark, turn on the lights
      //ledPower = HIGH;
      //analogWrite(A5, 500);
      digitalWrite(8, HIGH);
      //analogWrite(A4, ledPower);
      Serial.println("LED ON");

    } else {
      // There is a lot of sun light
      //analogWrite(A5, 0);
      digitalWrite(8, LOW);
      //analogWrite(A4, 0);
      Serial.println("LED OFF");
    }
    if (easternLight <= westernLight) {
      // It's sunset
      if (sunshadePosition != sunshadeExpanded) {
        servo.write(sunshadeExpanded);

        //delay(5000);
       // Serial.print("dd1 ");
        //Serial.println(easternLight);
        //Serial.println(westernLight);
      }
      if (sunshadePosition != sunshadeExpanded) {
        servo2.write(sunshadeExpanded);
      }
    }
    if (easternLight > westernLight) {
      // It's down
      if (sunshadePosition != sunshadeContracted) {
        servo.write(sunshadeContracted);
        //delay(5000);
        
        //Serial.print("dd2 ");
        //Serial.println(easternLight);
       // Serial.println(westernLight);

      }
      if (sunshadePosition != sunshadeContracted) {
        //to add position 2
        servo2.write(sunshadeContracted);
      }
    }
  }
  delay(100);
}