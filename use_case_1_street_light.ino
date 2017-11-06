
/*Intelligent Street Lighting with Temperature Monitoring*/

#include <SD.h>;                    
#include <math.h>
const int ledPin=4;                 //Connect the LED Grove module to 4, Digital 4
const int thresholdvalue=10;        //The threshold for which the LED should turn on. 
float Rsensor;                      //Declaring a variable; Resistance of sensor in K


File myFile;                       

int a;
float temperature;
int B=3975;                        //B: value of the thermistor
float resistance;


void setup() {
  Serial.begin(9600);              //Start the Serial connection at 9600 bits per second
  pinMode(ledPin,OUTPUT);          //Set the LED on Digital 4 as an OUTPUT
  
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


 myFile = SD.open("/sensor-data/street_light.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("File '/sensor-data/street_light.txt' ready for writing...");
    myFile.println("The readings are:");
    //close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening file\n");
  }
 
}


void loop() {
  //TEMPERATURE SENSOR CODE
  a=analogRead(0);                                            //Temperature Sensor connected on Analog Pin (A0)
  resistance=(float)(1023-a)*10000/a;                         //Get the resistance of the temperature sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;    //convert to temperature via datasheet&nbsp;;
  Serial.print("Current temperature in Celsius is: ");
  Serial.println(temperature);                                //Displaying temperature in Celsius
  
  
  //LDR + LED CODE
  int sensorValue = analogRead(3);                           //Light Sensor Connected on Analog Pin (A3)
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;          //Get the resistance of the light sensor;
    
  if(Rsensor>thresholdvalue)                                 //Comparing resistance of light sensor with threshold
  {
    digitalWrite(ledPin,HIGH);
    Serial.println("LED turned ON: Resistance of Light Sensor > Threshold");
  }
  else
  {
  digitalWrite(ledPin,LOW);
  Serial.println("LED turned OFF: Resistance of Light Sensor < Threshold");
  }
  
  Serial.print("Data read from Analog Pin 3 (Light Sensor) is:  ");
  Serial.println(sensorValue);                                    //show the raw sensor reading on the serial monitor
  Serial.print("The data of A3 (Light Sensor) converted into resistance is: ");
  Serial.println(Rsensor,DEC);                                    //show the light intensity on the serial monitor; 
  Serial.println("");
  
  
  myFile = SD.open("/sensor-data/street_light.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Logging sensor readings to file '/sensor-data/street_light.txt'...");
    Serial.println("");Serial.println("");Serial.println("");Serial.println("");
    myFile.print("Temperature in *C is: ");
    myFile.println(temperature);
    myFile.print("Data read from Analog Pin 3 (Light Sensor) is:  ");
    myFile.println(sensorValue);
    myFile.print("The data of A3 (Light Sensor) converted into resistance is: ");
    myFile.println(Rsensor);
    
    
    if(Rsensor>thresholdvalue)                                 //Comparing resistance of light sensor with threshold
    {
        myFile.println("LED turned ON: Resistance of Light Sensor > Threshold");
        
    }
    else
    {    
        myFile.println("LED turned OFF: Resistance of Light Sensor < Threshold");
    }
 
    myFile.println("");myFile.println("");myFile.println("");
    myFile.close();                                              //close the file:
 
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening /street_light.txt\n");
  }
    
  delay(1000);                                                    //Delay between two readings = 1second
   
  
}

