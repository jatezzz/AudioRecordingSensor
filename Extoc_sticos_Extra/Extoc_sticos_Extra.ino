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
  Serial.println(segundo);
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
//  while(digitalRead(7)==HIGH){
//    delay(10);
//  }
v=1;
    while(v==1){
      delay(10);
      if(digitalRead(7)==HIGH){
        val=0;
        EEPROM.write(address, val);
        }
    }
v=0;
  digitalWrite(estado,LOW);
  delay(100);
    
Serial.println("grabando");
//leo eeprom
String nombre = "record";
  nombre+=val;
  val++;
  if(val==100){
    val=0;
    }
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
      myFile.print("H");
      myFile.print(minu);
      myFile.print("Min");
      myFile.print(segundo);
      myFile.println("Seg");
      
      v=1;//digitalRead(7);
      while(v==1){
        myFile.println(analogRead(0));
      }
      
      myFile.close();
      digitalWrite(estado,HIGH);
      digitalWrite(error,HIGH);
      delay(200);
      digitalWrite(estado,LOW);
      digitalWrite(error,LOW);
      delay(100);
       digitalWrite(estado,HIGH);
      delay(200);
      digitalWrite(estado,LOW);
      delay(100);
       digitalWrite(estado,HIGH);
      delay(200);
      digitalWrite(estado,LOW);
      delay(100);
      v=0;
    }else{
      digitalWrite(error,HIGH);
      }
}
//interrupcion
void ServicioBoton() 
   {    v++ ;
   }

