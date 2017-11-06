/*Touch Based Burglary Detection System*/

#include <SD.h>; 

const int buzzerPin=2;                   //Connect the Buzzer Grove module to 2, Digital 2 
const int TouchPin=4;
const int ledPin=8;

File myFile;  

void setup() {
  Serial.begin(9600);
  pinMode(TouchPin, INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
    
  Serial.print("\nInitializing SD card...");
 
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
 
  Serial.println("initialization done.");
 
  // if the directory does not exist, create it:
  if (!SD.exists("/sensor-data")) {
    Serial.print("Creating directory '/sensor-data'\n");
    SD.mkdir("/sensor-data");
    
  myFile = SD.open("/sensor-data/burglar_touch.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("File '/sensor-data/burglar_touch.txt' ready for writing...");
    myFile.println("The readings are:");
    //close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening file\n");
  }
 
}
}
 


void loop() {
int sensorValue = digitalRead(TouchPin);            //use TouchPin to read touch signal

if(sensorValue==1)
{
digitalWrite(ledPin,HIGH);               //if touch detected LED glows
digitalWrite(buzzerPin,HIGH);            //if touch detected then Buzzer goes ON
Serial.println("Touch Detected. BURGULAR ALERT!!! :O :O ");
}

else
{
digitalWrite(ledPin,LOW);                //if no touch detected LED does not glow
digitalWrite(buzzerPin,LOW);            //if no touch detected then Buzzer goes OFF
Serial.println("No Touch Detected. Your Property Is Safe!! :) :) ");
}

myFile = SD.open("/sensor-data/burglar_touch.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Logging sensor readings to file '/sensor-data/burglar_touch.txt'...");
    Serial.println("");Serial.println("");Serial.println("");Serial.println("");
    myFile.print("The sensor value is: ");
    myFile.println(sensorValue);
    if(sensorValue==1)
    {
        digitalWrite(ledPin,HIGH);
        myFile.println("Touch Detected. BURGULAR ALERT!!! :O :O ");
     }

    else
    {
        digitalWrite(ledPin,LOW);
        
        myFile.println("No Touch Detected. Your Property Is Safe!! :) :)  ");
        
    }

     myFile.println("");myFile.println("");
     myFile.close();              //close the file:
 
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening /burglar_touch.txt\n");
    
  }
    
delay(1000);
}
