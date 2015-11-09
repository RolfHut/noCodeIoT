
//the pin used to measure
int analogPin = A0;

//the measurement
int measuredValue = 0;

void setup(){
  //tell the photon that analogPin is used as an INPUT
  pinMode(analogPin, INPUT);

  //begin Serial communication
  Serial.begin(9600);

  //make the measurement available in the Cloud
  Particle.variable("measurement",measuredValue);

}

void loop(){

  //do a measurement
  measuredValue = analogRead(analogPin);

  //send over Serial
  Serial.println(measuredValue);

  //wait for a second
  delay(1000);

}
