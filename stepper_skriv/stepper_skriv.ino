int smDirectionPin = 3; //Direction pin
int smStepPin = 4; //Stepper pin
int smEnablePin = 5; //Motor enable pin
String a;
int k;
void setup(){
  /*Sets all pin to output; the microcontroller will send them(the pins) bits, it will not expect to receive any bits from thiese pins.*/
  pinMode(smDirectionPin, OUTPUT);
  pinMode(smStepPin, OUTPUT);
  pinMode(smEnablePin, OUTPUT);
 
  digitalWrite(smEnablePin, HIGH); //Disbales the motor, so it can rest untill it is called uppond
 
  Serial.begin(9600);
}
 
void loop(){
  /*Here we are calling the rotate function to turn the stepper motor*/
while(Serial.available()) {
a= Serial.readString();// read the incoming data as string
k = a.toInt();
Serial.println(k);
}
 if (k != 0) {
  rotate(k, 0.5); //The motor rotates 800 steps clockwise with a speed of 0.1 (slow)
  delay(1000);
  k = 0;
  a = "0";
 }
//  rotate(1600, 0.5); //The motor rotates 1600 steps clockwise with a speed of 0.5 (medium)
//  delay(5000);
//  rotate(-1600, 1); //The motor rotates 1600 steps counter clockwise with a speed of 1 (fast)
//  delay(5000);
}
 
/*The rotate function turns the stepper motor. Tt accepts two arguments: 'steps' and 'speed'*/
void rotate(int steps, float speed){
  digitalWrite(smEnablePin, LOW); //Enabling the motor, so it will move when asked to
 
  /*This section looks at the 'steps' argument and stores 'HIGH' in the 'direction' variable if */
  /*'steps' contains a positive number and 'LOW' if it contains a negative.*/
  int direction;
 
  if (steps > 0){
    direction = HIGH;
  }else{
    direction = LOW;
  }
 
  speed = 1/speed * 70; //Calculating speed
  steps = abs(steps); //Stores the absolute value of the content in 'steps' back into the 'steps' variable
 
  digitalWrite(smDirectionPin, direction); //Writes the direction (from our if statement above), to the EasyDriver DIR pin
 
  /*Steppin'*/
  for (int i = 0; i < steps; i++){
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(smStepPin, LOW);
    delayMicroseconds(speed);
  }
 
  digitalWrite(smEnablePin, HIGH); //Disbales the motor, so it can rest untill the next time it is called uppond
}
