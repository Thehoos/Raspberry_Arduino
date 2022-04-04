#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ports
const int Moisture_Sensor = A0;

// const int Dry_Soil_Moisture_Percentage = 35 ;           // 70% is good soil  20% and below is bad

const int Good_Value = 437;

const int Dry_Value = 484;
const int Just_watered = 387;

const int Air_Value = 670;
const int Water_Value = 350;

int Moisture_Percentage;
int Moisture_Value, Prev_Moisture_Value;

String msg;


/**********************************************************/

int Calculate_Moisture(int Value)
{

  int Percentage;
  Percentage = map(Value, Dry_Value, Just_watered, 0, 100);

  // Moisture_Percentage -= 10; // cause of the power shortage from supplying lcd display
  return Percentage;
}

int Calculate_Moist_Value(int Check_times, int delay_time)
{

  int Value = 0;
  for (int i = 0; i <= Check_times; i++)
  {
    Value += analogRead(Moisture_Sensor);
    delay(delay_time);
  }
  Value /= 20;

  return Value;
}

void LcdPrint(int Percentage, int Value)
{
  lcd.clear();
  lcd.print("Moisture ");
  lcd.print(Percentage);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(Value);
}

void readSerialPort()
{
  msg = "";
  delay(10);
  if (Serial.available()) {

    while (Serial.available() > 1)
    {
      msg += (char)Serial.read();
      Serial.flush();
    }
    char x = (char)Serial.read();
//    Serial.print("'");
//    Serial.print(x, DEC);
//    Serial.print("'");
//    Serial.println();
  }
}
void sendData()
{
  if (msg == "all") {
    Serial.print(Moisture_Value);
    Serial.print(" ");
    Serial.println(Moisture_Percentage); //" -- all -- "
  }
  else if (msg == "value") {
    Serial.println(Moisture_Value); //" -- value --"
  }
  else if ( msg == "percentage") {
    Serial.println(Moisture_Percentage); //"-- percentage --"
  }

  else{
    Serial.print("recieved: ");
    Serial.println(msg);
  }
}
/**********************************************************/

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
    Moisture_Value = Calculate_Moist_Value(20, 50);
    Moisture_Percentage = Calculate_Moisture(Moisture_Value);

    if (Moisture_Value > Prev_Moisture_Value + 2 || Moisture_Value < Prev_Moisture_Value - 2)
    {
      LcdPrint(Moisture_Percentage, Moisture_Value);
      Prev_Moisture_Value = Moisture_Value;
    }

  readSerialPort();
  if (msg != "")
  {
//    Serial.print("recieved: ");
//    Serial.println(msg);
    sendData();
  }
}