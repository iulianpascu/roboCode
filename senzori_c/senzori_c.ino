//acestia sunt senzorii de culoare: x va fi inlocuit cu nr slot-ului corespunzator de pe placa;
// exemplu:
int culFD = 1;//x; culoare
int culFS = 2;//x; culoare
int culSD = 3;//x; culoare
int culSS = 4;//x; culoare
int distS = 0;//x; distanta
int s_culFD = 1;//x; culoare
int s_culFS = 2;//x; culoare
int s_culSD = 3;//x; culoare
int s_culSS = 4;//x; culoare
int s_distS = 0;//x; distanta
int MOTOR1_PIN1 = 3;

int MOTOR1_PIN2 = 5;

int MOTOR2_PIN1 = 6;

int MOTOR2_PIN2 = 9;

void setup()
{
  //setam slot-urile motoarelor pe OUTPUT
  pinMode(MOTOR1_PIN1, OUTPUT); //
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  // setam toate slot-urile cu senzori pe INPUT pt a primi informatie
  pinMode(culFS, INPUT);
  pinMode(culFD, INPUT);
  pinMode(culSS, INPUT);
  pinMode(culSD, INPUT);
  pinMode(distS, INPUT);
  Serial.begin(9600);
}

//structura repetitiva, loop-ul se repeta la nesfarsit
void loop()
{
  int culFS = analogRead(s_culFS); // fata stanga // culoare stanga
  delay(200);
  int culSS = analogRead(s_culSS); // fata dreapta // culoare dreapta
  int culSD = analogRead(s_culSD); // spate dreapta // lat stg
  int culFD = analogRead(s_culFD); // spate stanga // lat dr
//  Serial.print("cul Fata stanga: ");
  Serial.println(culFS); // printati in Serial Monitor (dreapta sus in programul arduino) valorile detectate de senzori
  //Serial.print("cul Spate stanga: ");
  //Serial.println(culSS);
  //Serial.print("cul Fata dreapta: ");
  //Serial.println(culFD); // printati in Serial Monitor (dreapta sus in programul arduino) valorile detectate de senzori
  //Serial.print("cul Spate dreapta: ");
  //Serial.println(culSD);

  //go(255,255); // mai jos aveti declarata functia go. Aceasta are doua argumente(fiecare dintre motoare). Valorile posibile sunt cuprinse intre -255 si 255;
  // pentru codul final, nu e nevoie sa lasati functiile de printare – ele sunt numai pentru testele voastre in determinarea valorilor intoarse de senzori.
  
  
}

void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  } else 
  {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  }
  else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}

