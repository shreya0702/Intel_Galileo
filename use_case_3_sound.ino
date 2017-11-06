/*Sound Based Burglary Detection System*/

#include <SD.h>; 

const int buzzerPin=2;                   //Connect the Buzzer Grove module to 2, Digital 2 
const int ledPin=8;                      //Connect the LED Grove module to 8, Digital 8
const int thresholdvalue=400;            // The threshold to turn the led on 400.00*5/1024 = 1.95v 

File myFile;  

void setup() {
    Serial.begin(9600);
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
    
      myFile = SD.open("/sensor-data/burglar_sound.txt", FILE_WRITE);
 
      // if the file opened okay, write to it:
      if (myFile) {
        Serial.print("File '/sensor-data/burglar_sound.txt' ready for writing...");
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
  int sensorValue = analogRead(0);            //use A0 to read the sound signal
  Serial.print("sensorValue ");
  Serial.println(sensorValue);

  if(sensorValue>thresholdvalue)
  {
    digitalWrite(ledPin,HIGH);               //if sound detected then LED glows
    digitalWrite(buzzerPin,HIGH);            //if sound detected then Buzzer goes ON
    Serial.println("Sound Detected. Somebody suspicious in the empty house!!! :O :O ");
    
  }

  else
  {
    digitalWrite(ledPin,LOW);               ///if no sound detected then LED does not glow
    digitalWrite(buzzerPin,LOW);            //if no sound detected then Buzzer goes LOW
    Serial.println("No Sound Detected. Your House Is Silent!! :) :) ");
  }

  myFile = SD.open("/sensor-data/burglar_sound.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Logging sensor readings to file '/sensor-data/burglar_sound.txt'...");
    Serial.println("");Serial.println("");Serial.println("");Serial.println("");
    myFile.print("The sensor value is: ");
    myFile.println(sensorValue);
    if(sensorValue>thresholdvalue)
    {
        digitalWrite(ledPin,HIGH);
        myFile.println("Sound Detected. Somebody suspicious in the empty house!!! :O :O ");    
    }

    else
    {
        digitalWrite(ledPin,LOW);
        
        myFile.println("No Sound Detected. Your House Is Silent!! :) :) ");
     }

    myFile.println("");myFile.println("");
    myFile.close();                            //close the file:
 
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening /burglar_sound.txt\n");
  }
    
delay(1000);
}
