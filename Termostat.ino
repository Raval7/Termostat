// Termostat
// Version: 1.0
// By Rafał Mlicki


// Constants:
const int ON_TEMP = 35;
const int OFF_TEMP = 32;

// Variables:
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int mode;
int fanEnable;

// Main program setup
void setup()
{

  mode = 0;
  fanEnable = 0;

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}

// Main program loop
void loop()
{

  tempRead();

  switch (mode)
  {
    case 0:

      if (T > ON_TEMP)
      {
        mode = 1;
      }

      if (fanEnable == 1)
      {
        fanEnable = 0;
        fanOff();
      }
      break;

    case 1:

      if (T < OFF_TEMP)
      {
        mode = 0;
      }

      if (fanEnable == 0)
      {
        fanEnable = 1;
        fanOn();
      }
      break;
  }

  delay(500);
}

// Reading current temperature
void tempRead()
{
  Vo = analogRead(6);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
}

// Fan realy off
void fanOff()
{
  digitalWrite(3, HIGH);
}

// Fan realy on
void fanOn()
{
  digitalWrite(3, LOW);
}
