// number of analog pins to read
#define NUMPINS 6

// read at most 100 times a second
#define READPERIOD 5

// a header for outgoing serial messages
#define MSGHEADER 0xAB

byte serialMsg[3];
int whichPin;
unsigned long lastReadWrite;
int mappedValue;
int started = 0;
int serialvalue;

void setup() {
  Serial.begin(57600);
  serialMsg[0] = serialMsg[1] = serialMsg[2] = 0x00;
  whichPin = 0;
  lastReadWrite = millis();
}



void loop() {
  if(Serial.available()) // check to see if there's serial data in the buffer
{
  serialvalue = Serial.read(); // read a byte of serial data
started = 1; // set the started flag to on
}
if(started) {
  // don't read pins more frequent than 100 times per second
  // and only read one pin per loop to avoid noise
  if (millis() - lastReadWrite > READPERIOD) {
   // short readValue = analogRead(whichPin);
    int readValue=analogRead(whichPin);
    //scale readValue to 0 to 255
   // mappedValue= map (readValue, 0 ,1023, 0, 255); 
   String string;
    string = String( whichPin );
    string += " ";
    string += readValue;
   Serial.print(string);
   Serial.print(" ");
   
    

    
//    Serial.println("val " + readValue);



//    serialMsg[0] = (MSGHEADER & 0xFF);
//    serialMsg[1] = ((whichPin << 4) & 0xF0) | ((readValue >> 8) & 0x0F);
//    serialMsg[2] = (readValue & 0xFF);

    //    Serial.write(serialMsg[0]);
    //    Serial.write(serialMsg[1]);
    //    Serial.write(serialMsg[2]);

    //    Serial.print("[0] " + serialMsg[0]);
//    Serial.println(serialMsg[1], DEC);
    //    Serial.println(", [2] " + serialMsg[2]);

    whichPin = (whichPin + 1) % NUMPINS;
    if ( whichPin == NUMPINS - 1 ) {
      Serial.println();
    }

    Serial.flush();
    // use millis() because flush could take longer
    lastReadWrite = millis();
  }
}
}


