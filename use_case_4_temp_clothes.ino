
/* Weather Monitoring with Clothing Prediction */

#include <Wire.h>
#include "rgb_lcd.h"
#include <SD.h>; 

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

File myFile;   

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 4;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB); 
  
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
   
}


 myFile = SD.open("/sensor-data/temp_clothes.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("File '/sensor-data/temp_clothes.txt' ready for writing...");
    myFile.println("The readings are:");
    //close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening file\n");
  }
  
}

void loop(){
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    delay(10);
    
    float temp = analogRead(0);// is pressed, temperature is displayed
    temp = (float)(1023 - temp)*10000/temp;
    temp = 1/(log(temp/10000)/3975+1/298.15)-273.15;
    Serial.println("The temperature in *C is: ");
    Serial.println(temp);
    
    if(temp<25)
    {lcd.setCursor(0,0);
    lcd.print("temp:");
    lcd.print(temp,2);
    lcd.setCursor(0,1);
    lcd.print("Wear WarmClothes");
    Serial.println("Wear Warm Clothes! ");
    }
    else
    {lcd.setCursor(0,0);
    lcd.print("temp:");
    lcd.print(temp,2);
    lcd.setCursor(0,1);
    lcd.print("It's hot outside");
    Serial.println("It's hot outside");
    }
    
    myFile = SD.open("/sensor-data/temp_clothes.txt", FILE_WRITE);
 
    // if the file opened okay, write to it:
    if (myFile) {
    Serial.println("Logging sensor readings to file '/sensor-data/temp_clothes.txt'...");
    Serial.println("");Serial.println("");Serial.println("");Serial.println("");
    myFile.print("Temperature in *C is: ");
    myFile.println(temp);
    
    if(temp<25)
    {myFile.println("Wear Warm Clothes");
    }
    else
    {myFile.println("It's hot outside");
    }
    
    
    myFile.println("");myFile.println("");myFile.println("");
    myFile.close();                                              //close the file:
 
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening /temp_clothes.txt\n");
  }  
      
      
    delay(1000);
    }  
  
  else {
    lcd.clear();
   }
}
