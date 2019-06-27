/* This code is used in hardware testing of the KY-038
 * Most tests were done in the real world and this code
 * just functions as a means to test different setups
 */

int microphone = A0; // microphone input
int led = 13;       // LED output

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open serial connection at 9600 baud

  pinMode(microphone, INPUT); // microphone should be input
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(microphone);

   delay(150);
   Serial.print("[Mic value]: ");
   Serial.print(value);
   Serial.print('\n');

   if (value >= 512){
    digitalWrite(led, HIGH);
   }
   else{
    digitalWrite(led, LOW);
   }
}
