//#define irsensor 4

/*void readIR(int * outy)
{
  outy=analogread(irsensor)
}
*/
void readLineSensor(int * outputArray)
{
  for (int i =0; i <6; i++)
  {
    outputArray[i] = analogRead(i);
  }
}

void setup(){
  Serial.begin(9600);
  
}

void loop()
{

  int sensors[6];

  readLineSensor(sensors);

  Serial.print("Sensor Values : " );

  for (int i =0; i <6; i++)
  {
    Serial.print( sensors[i]);
    Serial.print(" " );
  }
  Serial.println(" ");
#if 0
  Serial.println(" ");
  int irval[1];
  
  Serial.print("IR Value : " );
  

#endif
  delay(240);
  
}
