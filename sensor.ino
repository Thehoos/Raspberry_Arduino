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

String nom = "Arduino";
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

/**********************************************************/

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
  Moisture_Value = Calculate_Moist_Value(20, 100);

  if (Moisture_Value != Prev_Moisture_Value)
  {
    Moisture_Percentage = Calculate_Moisture(Moisture_Value);
    //LcdPrint(Moisture_Percentage, Moisture_Value);

    Prev_Moisture_Value = Moisture_Value;
  }

  readSerialPort();
  if (msg != "")
  {
    Serial.print("recieved: ");
    Serial.print(msg);
    sendData();
  }
  //delay(500);
}

void readSerialPort()
{
  msg = "";
  delay(10);
  while (Serial.available() > 0)
  {
    msg += (char)Serial.read();
    Serial.flush();
  }
  
  Serial.print(msg);
  if ( msg == nom ) {
    Serial.println("OOOOOOOOOOOKKKKKK");
    Serial.println(nom);
  }

}
void sendData()
{
  if (msg == "all") {
    Serial.print(Moisture_Value);
    Serial.println(Moisture_Percentage);
  }
  else if (msg == "value") {
    Serial.print(Moisture_Value);
  }
  else if ( msg == "percentage") {
    Serial.print(Moisture_Percentage);
  }
}