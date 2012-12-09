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

const int wait = 0, evade = 10, cruise = 20, locate = 30, engage = 40, mad = 50;
int status_robot = locate;
int rot = 1; //cw vs ccw rotation
//int state[4], no_state = 0;


unsigned long start_time = 0, run_time = 3000, current_time;
float distance;
int left = 0 , right = 0;



void go_cruise()
{
    status_robot = cruise;
    start_time = current_time;
    run_time = random(2000,5000);
    left = 150;
    right= 150;
}

void go_locate()
{
    int semn = -1;
    status_robot = locate;
    start_time = current_time;
    run_time = random(3000,6000);
    if( random(0,20) >= 11) {
      semn = 1;}
    left = 50*semn;
    right = -left;
}
  
void go_engage()
{
    status_robot = engage;
    start_time = current_time;
    run_time = random(10000,15000);
    left = 255;
    right =255;
} 

void go_mad()
{
    status_robot = mad;
    start_time = current_time;
    run_time = random(3000,5000);
    left = 255;
    right =-255;
}

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
    
void detect_border(){
  if(culFS < 500){ //alb zona 1
       if(culSS < 650){ //alb zona 3
         go(255,0);
         delay(random(400,500));
       }else if(culFD < 500){ //alb zona 2
          go(-150,-150);
          delay(500);
          go(150,-150);
         delay(random(400,900));
       }else{
          go(-150,-150);
          delay(500);
          go(150,-150);
          delay(random(400,900));
       }
      go_cruise();
   }
   else if(culFD < 500){ //alb zona 2
     if(culSD < 800){ //alb zona 4
       go(0,255);
       delay(300);
       go(15,-150);
       delay(random(400,900));
     }else{  //alb doar acolo zona 1 a fost deja
        go(-150,-150);
        delay(500);
        go(-150,150);
        delay(random(400,900));
     }
      go_cruise();
 }
}  
    
//structura repetitiva, loop-ul se repeta la nesfarsit
void loop()
{

  culFS = analogRead(s_culFS); // fata stanga // culoare stanga
  culSS = analogRead(s_culSS); // fata dreapta // culoare dreapta
  culSD = analogRead(s_culSD); // spate dreapta // lat stg
  culFD = analogRead(s_culFD); // spate stanga // lat dr
  float volts = analogRead(s_distS)*0.0048828125;
  distance = 65*pow(volts, -1.1);
  current_time = millis();
/* 
  if(current_time% 400 == 0){
    Serial.println("\ndist \tFS \tFD \tSS \tSD");
    Serial.print(distance);
    Serial.print("\t"); 
    Serial.print(culFS);
    Serial.print("\t"); 
    Serial.print(culFD);
    Serial.print("\t"); 
    Serial.print(culSS);
    Serial.print("\t"); 
    Serial.println(culSD);
    if(status_robot == cruise)
      Serial.println("ncruise");
    else if(status_robot == locate)
      Serial.println("locate");
    else if(status_robot == engage)
      Serial.println("engage");
    Serial.println("ctime \tstime \trtime \tfeft \tright");
    Serial.print(current_time);
    Serial.print("\t"); 
    Serial.print(start_time);
    Serial.print("\t"); 
    Serial.print(run_time);
    Serial.print("\t"); 
    Serial.print(left);
    Serial.print("\t"); 
    Serial.println(right); 
  }
 */ 
 
   detect_border();
 

   if(status_robot == cruise && start_time + run_time < current_time)
     go_locate();
   else if(status_robot == locate && start_time + run_time < current_time) 
     go_cruise();
   else if(status_robot == locate && distance < 60)
     go_engage();
   else if(status_robot == engage && start_time + run_time < current_time)
     go_mad();
   else if(status_robot == mad && start_time + run_time < current_time)
     go_cruise();

 /*
 if(left == 0 ){
   left =1 ;
         go(-255,-255);
         delay(400);
 }else if(left == 1){
   left =2;
            go(255,-20);
         delay(400);
 }else
         go(0,0); 
  */
   go(left,right);

}



// in functie de distS specifica daca are un corp in fata


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

