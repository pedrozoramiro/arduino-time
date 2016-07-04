#include <Time.h>
#include <DS1302RTC.h>

const String CONFIGURE_DATE ="SD";
DS1302RTC RTC(8, 7, 6);
int i = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ;
  configureSyncDateOfSystem();
}

void configureSyncDateOfSystem(){
  setSyncProvider(RTC.get); 
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");  
}

void loop()
{
  String command = findCommand(i++);
  if(isCommandOf(CONFIGURE_DATE,command)) configureTime(getCommandValueInt(command));
  digitalClockDisplay();
}

void configureTime(int unixTime){
 if(RTC.set(unixTime* 1000) == 0){
   setTime(unixTime * 1000);
   Serial.println("Configurado");
   return;
  }
  Serial.println("ERRO AO CONFIGURAR");
}

String findCommand(int radom){
  Serial.println(radom);
   if(radom == 15)
    return "SD1444799410";
   return "";
}

int getCommandValueInt(String command){
   return getCommandValue(command).toInt();
}
String getCommandValue(String command){
   String value = command.substring(2,10);
   Serial.println(value);
   return value;
}

bool isCommandOf(String commandName, String command){
  if(command == "")   return false;
  String comm = command.substring(0,2);
  Serial.println(comm);
  return  comm == commandName;
}


void digitalClockDisplay(){
  Serial.print(hour());  printDigits(minute());  printDigits(second());  Serial.print(" ");
  Serial.print(day());  Serial.print(" ");  Serial.print(month());  Serial.print(" ");  Serial.print(year()); 
  Serial.println(); 
  delay(1000);
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

