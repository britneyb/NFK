
void setup() {
 // open the serial port at 9600 bps:
 Serial.begin(9600);
}

void loop() {

 //Must be println to work:
 Serial.println("HelloWorld ");       
 
 // delay 1000 milliseconds before the next print:
 delay(1000);
}

