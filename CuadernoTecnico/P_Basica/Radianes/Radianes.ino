/*  ----------------------------------------------------------------
Fco. Javier Rodriguez Navarro   www.pinguytaz.net

  
Trigonometria senos y cosenos, con conversion de radianes.
----------------------------------------------------------------*/

void setup() 
{
  Serial.begin(9600);
  float r;
  for (int i = 0; i<=360 ; i= i+45)
  {
    r = radianes(i);
    Serial.println("Para "+ String(i) + "º que son: " +String(r) + " radianes");
    Serial.println("\ttSeno: " + String(sin(r)));
    Serial.println("\tCoseno: " + String(cos(r)));
  }
}

void loop() 
{
}

float radianes(int a)
{
  return (a * PI /180);
}