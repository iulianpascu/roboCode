//acestia sunt senzorii de culoare: x va fi inlocuit cu nr slot-ului corespunzator de pe placa;
// exemplu:
const int s_culFD = 1;//x; culoare
const int s_culFS = 2;//x; culoare
const int s_culSD = 3;//x; culoare
const int s_culSS = 4;//x; culoare
const int s_distS = 0;//x; distanta
const int MOTOR1_PIN1 = 3;
const int MOTOR1_PIN2 = 5;
const int MOTOR2_PIN1 = 6;
const int MOTOR2_PIN2 = 9;

int culFD, culFS, culSD, culSS, distS;//x; distanta

const int forward_mvmt = 10, backward_mvmt = 20, hammering = 30;


boolean danger_ahead, danger_behind;

boolean enemy_det = false;
int first_seen, last_seen;
unsigned long current_time = 0, seen_time;

void setup()
{
  //setam slot-urile motoarelor pe OUTPUT
  pinMode(MOTOR1_PIN1, OUTPUT); //
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  // setam toate slot-urile cu senzori pe INPUT pt a primi informatie
  Serial.begin(9600);
}

void random_turn(){ //face
  go(-255,-255);
  delay(500);
  go(-255,255); 
  delay( random(500,1300));
}

//structura repetitiva, loop-ul se repeta la nesfarsit
void loop()
{
//  delay(200);

  culFS = analogRead(s_culFS); // fata stanga // culoare stanga
  culSS = analogRead(s_culSS); // fata dreapta // culoare dreapta
  culSD = analogRead(s_culSD); // spate dreapta // lat stg
  culFD = analogRead(s_culFD); // spate stanga // lat dr
  distS = analogRead(s_distS);
  current_time = millis();
 
   
  danger_ahead = culFS < 500 || culFD < 500;
  danger_behind = culSS < 500 || culSD < 500;
    
  if(danger_ahead){
      random_turn();
   } 
   else if( saw_robot() ){
     go(0,0);
     det_incoming();
   }
   else {
     enemy_det = false; //daca doar a trecut prin fata ignora-l
     go(255,255);
   }
  // pentru codul final, nu e nevoie sa lasati functiile de printare – ele sunt numai pentru testele voastre in determinarea valorilor intoarse de senzori.
  
  
}


// in functie de distS specifica daca are un corp in fata
boolean saw_robot(){ 
  return false;
}

void hammer_it(){}
void avoid_it(){
}


void foo(){
  Serial.println("this went wrong");
  //spune daca robotul vine spre, sta si e in drum
  //si actioneaza adecvat
  if(first_seen - last_seen >= -100) //celalalt robot sta pe loc
    hammer_it();
  else
    avoid_it();
}

void det_incoming(){
  if(!enemy_det){ //daca vedem undeva in fata alt robot si e prima data 
      enemy_det = true;
      first_seen = distS;
      seen_time = current_time;
  }
  else{
    if(current_time < seen_time + 500) //il observam
      last_seen = distS;
    else{
      enemy_det = false;
      //apeleaza o functie care spune daca robotul vine spre, sta si e in drum, sau doar a trecut prin fata
      foo();
    }
  }
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

