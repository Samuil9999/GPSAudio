//--------  variables ---------------------------------------------------------------
int  inByte = -1;                        //incoming byte from serial RX

String command;
char commandBuffer[10];
int  commandStringPos = 0;

int  data = 0;                           //data - int number (index or value of array element)
char dataBuffer[10];
int  dataStringPos = 0;                  //index number of data in string buffer

int outputNumber = 0;
int pulseNumber = 0;
int pulseLength = 1000;

////*********************************************************************************
////  Read incoming data
////*********************************************************************************
void serialEvent() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
  }

  // we`ve get the data type part: save only ASCII characters (ASCII 'A' - 'I')
  if ((inByte >= 'A' && inByte <= 'Z') || (inByte >= 'a' && inByte <= 'z')) {
    commandBuffer[commandStringPos] = (char)inByte;
    commandStringPos++;
  }
  // we`ve got numbers
  if ((inByte >= '0') && (inByte <= '9')) {
    dataBuffer[dataStringPos] = (char)inByte;
    dataStringPos++;
  }
  // if end of packet
  if (inByte == '\n') {
    command = commandBuffer;
    command.toUpperCase();
    data = atoi(dataBuffer);

    flushCommandBuffer();
    flushDataBuffer();

    interpretPacket();
  }
}

//*********************************************************************************
//  Interpret
//*********************************************************************************
void interpretPacket() {
  //---------------------------------------------------------------
  if (command == "SON") {
    //setOutputNumber();
    if((data >=0 && data <= 2) || data == LEDPIN) {
      outputNumber = data;
      Serial.print(command);
      Serial.println(outputNumber);
    } else {
      Serial.println(F("Incorrect command."));
      Serial.println(F("The output number must be 0, 1 or 2."));
    }
  }
  //---------------------------------------------------------------
  if (command == "SPN") {
    //setPulseNumber();
    if(data >=1 && data <= 15) {
      pulseNumber = data;
      Serial.print(command);
      Serial.println(pulseNumber);
    } else {
      Serial.println(F("Incorrect command."));
      Serial.println(F("The pulse number must be between 1 and 15."));
    }
  }
  //---------------------------------------------------------------
  if (command == "SPL") {
    if(data >=200 && data <= 10000) {
      pulseLength = data;
      Serial.print(command);
      Serial.println(pulseLength);
    } else {
      Serial.println(F("Incorrect command."));
      Serial.println(F("The pulse number must be between 200 and 10000."));
    }
  }
  //---------------------------------------------------------------
  if (command == "EC") {
    Serial.print(F("Executing command for: "));
    Serial.print(F("outputNumber - "));
    Serial.print(outputNumber);
    Serial.print(F(", pulseNumber - "));
    Serial.print(pulseNumber);
    Serial.print(F(", pulseLength - "));
    Serial.println(pulseLength);
    executeCommand();
  }

  //---------------------------------------------------------------
  //
  //---------------------------------------------------------------
  flushCommandBuffer();
  flushDataBuffer();
  data = -1;
}


//*********************************************************************************
//
//*********************************************************************************
void printHelp(){
  Serial.println(F("Use below commands to set parameters and start pulse train"));
  Serial.println(F("SON[NNN] - set output number, NNN - output number"));
  Serial.println(F("SPN[NNN] - set pulse number, NNN - pulse number"));
  Serial.println(F("SPL[LLL] - set pulse length, LLL - pulse length (in milliseconds)"));
  Serial.println(F("EC - execute command (start pulse train) on selected output"));
}
//*********************************************************************************
//
//*********************************************************************************
void executeCommand() {
  if (outputNumber == 0) {
    pulse(OUTPIN0, pulseNumber, pulseLength);
  } else if (outputNumber == 1) {
    pulse(OUTPIN1, pulseNumber, pulseLength);
  } else if (outputNumber == 2) {
    pulse(OUTPIN2, pulseNumber, pulseLength);
  } else {
    Serial.println(F("Wrong command"));    
  }
}

void pulse(int outputPin, int npulses, int pause) {
  for (int i = 0; i < pulseNumber; i++) {
    digitalWrite(outputPin, HIGH);
    digitalWrite(LEDPIN, HIGH);
    Serial.print(outputPin);
    Serial.print(",");
    Serial.print(i);
    Serial.print(",");
    Serial.println("HIGH");
    delay(pause);
    digitalWrite(outputPin, LOW);
    digitalWrite(LEDPIN, LOW);
    Serial.print(outputPin);
    Serial.print(",");
    Serial.print(i);
    Serial.print(",");
    Serial.println("LOW");
    delay(pause);
  }
}

//*********************************************************************************
//
//*********************************************************************************
void flushCommandBuffer() {
  for (int i = 0; i < 11; i++) {
    commandBuffer[i] = 0;
  }
  commandStringPos = 0;
}

void flushDataBuffer() {
  for (int i = 0; i < 11; i++) {
    dataBuffer[i] = 0;
  }
  dataStringPos = 0;
}


