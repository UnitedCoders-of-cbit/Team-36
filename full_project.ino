#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

class Smart_Segregator

{
  public:
     int servo_pin;
     int moisture_sensor_pin;
     int touch_sensor_pin;
     int detect_moisture;
     int detect_touch;
 
     Servo servo;

     Smart_Segregator(int pin_1, int pin_2, int pin_3)
     {
       servo_pin = pin_1;
       moisture_sensor_pin = pin_2;
       touch_sensor_pin = pin_3;

       detect_moisture = 0;
       detect_touch = false;
     }

    void init()
    {
      Serial.begin(9600);
      servo.attach(servo_pin);
      servo.write(90);
      
      pinMode(moisture_sensor_pin, INPUT);
      pinMode(touch_sensor_pin, INPUT);

      Serial.println("Your Smart Segregator is ready to Segregate!");
    }

    void dry_waste()
    {
      servo.write(50);
      delay(3000);
    }

    void wet_waste()
    {
      servo.write(130);
      delay(3000);
    }

    void neutral_state()
    {
      servo.write(90);
      delay(3000);
    }
    
    void execute()
    {
      detect_moisture = analogRead(moisture_sensor_pin);
      detect_touch = digitalRead(touch_sensor_pin);
      Serial.println(detect_moisture);
      if (detect_moisture <325 && detect_touch == true)
      {
        
        Serial.println(detect_moisture);
        LCD.clear();
        LCD.print("WET WASTE");
        wet_waste();
        
      }
      else if (detect_moisture >=3245&& detect_touch == true)
      {
        Serial.println(detect_moisture);
        LCD.clear();
        LCD.print("DRY WASTE");
        dry_waste();
        
      }

      else 
      {
        neutral_state();
      }
    }
}

segregator = Smart_Segregator(8,A0,10);

void setup() 
{
  segregator.init();
}

void loop() 
{
 segregator.execute();
}
