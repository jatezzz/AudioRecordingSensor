#include <SPI.h>
#include <SD.h>
//leer y escribir en memoria
#include <EEPROM.h>
//Reloj
#include <Wire.h>                       // For some strange reasons, Wire.h must be included here
#include <DS1307new.h>

uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xaa55;            // Helper that time must not set again
//-------------------------------

File myFile;

int sensorValue=0;
int cont=0;
int cont2=0;
int v=1;
const int estado = 8;
const int error = 9;
//eeprom
int address=0;
int val,segundo=0,minu=0,hor=0,dia=0,mes=0,ano=0;

void setup() {
  //Reloj--------------------------------------------------
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 
  RTC.getTime();
  hor=RTC.hour;
  minu=RTC.minute;
  segundo=RTC.second;
  dia=RTC.day;
  mes=RTC.month;
  ano=RTC.year;
  //interrupcion
  attachInterrupt( 0, ServicioBoton, FALLING);
  //
  Serial.begin(9600);
  Serial.println("iniciando");
   //
  val=EEPROM.read(address);
  Serial.print(address);
  Serial.print("\t");
  Serial.print(val, DEC);
  Serial.println();
  //Leds de salida
  pinMode(estado,OUTPUT);
  pinMode(error,OUTPUT);
  digitalWrite(estado,HIGH);
  //Pulsador de entrada
  pinMode(7,INPUT);
  //comprueba si se puede iniciar la comunicacion
  if (!SD.begin(4)) {
    digitalWrite(error,HIGH);
    return;
  }
  digitalWrite(error,LOW);
  //Reloj--------------------------------------------------
  
//RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 
///*
//   Control Register for SQW pin which can be used as an interrupt.
//*/
//  RTC.ctrl = 0x00;                      // 0x00=disable SQW pin, 0x10=1Hz,
//                                        // 0x11=4096Hz, 0x12=8192Hz, 0x13=32768Hz
//  RTC.setCTRL();
//  uint8_t MESZ;
 
}


void loop() {
  Serial.println("esperando");
  //espera hasta que se presione el pulsador
  digitalWrite(estado,HIGH);
  while(digitalRead(7)==HIGH){
    delay(10);
  }
  digitalWrite(estado,LOW);
  delay(100);
    
Serial.println("grabando");
//
////Consigo tiempo-
//    RTC.getTime();
//    hor=RTC.hour;
//    minu=RTC.minute;
//    dia=RTC.day;
//    mes=RTC.month;
//    ano=RTC.year;
      //if (hor < 10)                    // correct hour if necessary
//      {
//        
//        Serial.print("0");
//        Serial.print(RTC.hour, DEC);
//      } 
//      else
//      {
//        Serial.print(RTC.hour, DEC);
//      }
//      Serial.print(":");
//      if (RTC.minute < 10)                  // correct minute if necessary
//      {
//        Serial.print("0");
//        Serial.print(RTC.minute, DEC);
//      }
//      else
//      {
//        Serial.print(RTC.minute, DEC);
//      }
//      Serial.print(":");
//      if (RTC.second < 10)                  // correct second if necessary
//      {
//        Serial.print("0");
//        Serial.print(RTC.second, DEC);
//      }
//      else
//      {
//        Serial.print(RTC.second, DEC);
//      }
//      Serial.print(" ");
//      if (RTC.day < 10)                    // correct date if necessary
//      {
//        Serial.print("0");
//        
//        Serial.print(RTC.day, DEC);
//        //nombre+=0;
//      }
//      else
//      {
//        Serial.print(RTC.day, DEC);
//      }
//      //nombre+=RTC.day;
//      //nombre.concat("-");
//      Serial.print("-");
//      
//      if (RTC.month < 10)                   // correct month if necessary
//      {
//        Serial.print("0");
//        Serial.print(RTC.month, DEC);
//        //nombre+=0;
//      }
//      else
//      {
//        Serial.print(RTC.month, DEC);
//      }
//      Serial.print("-");
//      //nombre+=RTC.month;
//      //nombre.concat("-");
//      Serial.print(RTC.year, DEC);          // Year need not to be changed
//      //nombre+=RTC.year;
//      Serial.print(" ");
//      switch (RTC.dow)                      // Friendly printout the weekday
//      {
//        case 1:
//          Serial.print("MON");
//          break;
//        case 2:
//          Serial.print("TUE");
//          break;
//        case 3:
//          Serial.print("WED");
//          break;
//        case 4:
//          Serial.print("THU");
//          break;
//        case 5:
//          Serial.print("FRI");
//          break;
//        case 6:
//          Serial.print("SAT");
//          break;
//        case 0:
//          Serial.print("SUN");
//          break;
//      }
//      Serial.print("\n");
//---------------
  
//leo eeprom
String nombre = "record";
  nombre+=val;
  val++;
  EEPROM.write(address, val);
  nombre.concat(".txt");
  myFile = SD.open(nombre, FILE_WRITE);
  Serial.println(nombre);
    // if the file opened okay, write to it:
    if (myFile) {
      digitalWrite(error,LOW);
      //Imprimo cabecera
      myFile.print("Fecha: ");
      myFile.print(dia);
      myFile.print(" ");
      myFile.print(mes);
      myFile.print(" ");
      myFile.println(ano);
      myFile.print("Hora: ");
      myFile.print(hor);
      myFile.print(":");
      myFile.print(minu);
      myFile.print(":");
      myFile.println(segundo);
      
      v=1;//digitalRead(7);
      while(v==1){
      //sensorValue = ;
      myFile.println(analogRead(0));
      //v=digitalRead(7);
      }
      myFile.close();
      v=0;
      delay(200);
    }else{
      digitalWrite(error,HIGH);
      }
}
//interrupcion
void ServicioBoton() 
   {    v++ ;
   }

