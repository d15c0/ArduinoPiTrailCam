//Global Variables
// Motion Pin expecting a High

const byte MOTION = 2; // motion pin active high
const byte DETECT = 3; // Motion Detect
const byte PWR = 10; // PWR 
const byte TRIG = 9; // camera trigger to pi GPIO 21
const byte SHTDWN = 8; // shutdown pulse to pi GPIO 26
const byte DETECTOUT = 7;


unsigned long motionActivatedMillis; // when button was pushed
unsigned long trigOffMillis;
unsigned long pwrTurnedOnAt; // when pwr was turned on
unsigned long trigTurnedOnAt; // blah trig not pwr

unsigned long pwrOnDelay = 250; // wait to turn on PWR
unsigned long pwrOffDelay = 180000; // turn off PWR after this time
unsigned long trigOnDelay = 250; // after motion wait to activate trigger
unsigned long trigOffDelay = 20000; // keep the trigger low for ...
unsigned long shtdwnOnDelay = 30000;
unsigned long shtdwnOffDelay = 8000;

bool pwrReady = false; // flag for when button is let go
bool pwrState = false; // for PWR is on or not.
bool trigReady = false;
bool trigState = false;
bool shtdwnReady = false;
bool shtdwnState = false;




void setup() {
 pinMode(MOTION, INPUT);
 pinMode(DETECT, INPUT);
 pinMode(PWR, OUTPUT);
 digitalWrite(PWR, LOW);

 pinMode(TRIG, OUTPUT);
 digitalWrite(TRIG, HIGH);

 pinMode(SHTDWN, OUTPUT);
 digitalWrite(SHTDWN, HIGH); 

 pinMode(DETECTOUT, OUTPUT);
 digitalWrite(DETECTOUT, HIGH);
}


void loop() {

 // get the time at the start of this loop()
 unsigned long currentMillis = millis(); 

 // check the button
 if (digitalRead(MOTION) == HIGH) {

  // update the time when button was pushed
  motionActivatedMillis = currentMillis;
  pwrReady = true;
  trigReady = true;

 }
//check motion 
 if (digitalRead(DETECT) == HIGH) {
    digitalWrite(DETECTOUT, LOW);
 }
 else{
  digitalWrite(DETECTOUT, HIGH);
 }

  

 // make sure this code isn't checked until after button has been let go

 if (pwrReady) {
  
   //this is typical millis code here:
   if ((currentMillis - motionActivatedMillis) <= pwrOnDelay) { 

     delay(1500);
  
     // okay, enough time has passed since the button was let go.
     digitalWrite(PWR, HIGH);

     // setup our next "state"
     pwrState = true;

     // save when the PWR turned on
     pwrTurnedOnAt = currentMillis;

     // wait for next button press
     pwrReady = false;

   }
 }

 if (trigReady) {

   //this is typical millis code here:
   if (currentMillis - motionActivatedMillis <= trigOnDelay) {  

     delay(3000);
   
     // okay, enough time has passed since the button was let go.
     digitalWrite(TRIG, LOW);
    
     // setup our next "state"
     trigState = true;

     // save when the PWR turned on
     trigTurnedOnAt = currentMillis;

     // wait for next button press
     trigReady = false;

   }
 }

 
// see if we are watching for the time to turn off TRIG
 if (trigState) {

   // okay, pwr on, check for now long
   if ((currentMillis - trigTurnedOnAt) >= trigOffDelay) {

     trigState = false;
     digitalWrite(TRIG, HIGH);
                    
    
   }

}

if (pwrState) {

  if ((currentMillis - trigTurnedOnAt) >= (trigOffDelay + shtdwnOnDelay)) {
    pwrState = false;
    trigState = false;
    digitalWrite(SHTDWN, LOW);
    delay(2000);
    digitalWrite(SHTDWN, HIGH);
    delay(6000);
    digitalWrite(PWR, LOW);
   
   }
 } 
}
