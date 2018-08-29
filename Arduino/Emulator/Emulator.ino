#define OUTPIN0 7
#define OUTPIN1 8
#define OUTPIN2 9
#define LEDPIN 13

void setup() {
  pinMode(OUTPIN0, OUTPUT);
  pinMode(OUTPIN1, OUTPUT);
  pinMode(OUTPIN2, OUTPUT);
  pinMode(LEDPIN, OUTPUT);

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("GPS Unit Emulator started."));
  printHelp();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  readFromPC();
  //  delay(5);
}


