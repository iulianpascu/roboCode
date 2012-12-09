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

const int wait = 0, evade = 10, cruise = 20, locate = 30, engage = 40;
int status_robot = locate;
int rot = 1; //cw vs ccw rotation
//int state[4], no_state = 0;


unsigned long start_time = 0, run_time = 3000, current_time;
float distance;
int left, right;



void succesor(){
  if(status_robot == evade){
    status_robot = cruise;
    start_time = current_time;
    run_time = random(1000,3000);
    left = 150;
    right= 150;
  }else if(status_robot == cruise) {
    status_robot == locate;
    start_time = current_time;
    run_time = random(1000,3000);
    left = -50;
    right = 50;
  }else if(status_robot == locate) {
    status_robot == engage;
    start_time = current_time;
    run_time = random(1000,3000);
    left = 255;
    right =255;
  }else{
    status_robot = cruise;
    start_time = current_time;
    run_time = random(1000,3000);
    left = 150;
    right= 150;
  }
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
         go(120,60);
         delay(300);
         go(150,-150);
         delay(random(400,900));
       }else if(culFD < 500){ //alb zona 2
          go(-150,-150);
          delay(1000);
          go(150,-150);
         delay(random(400,900));
       }else{
          go(-150,-150);
          delay(500);
          go(150,-150);
          delay(random(400,900));
       }
       succesor();
   }
   else if(culFD < 500){ //alb zona 1
     if(culSD < 800){ //alb zona 3
       go(60,120);
       delay(300);
       go(15,-150);
       delay(random(400,900));
     }else if(culFD < 500){ //alb zona 2
        go(-150,-150);
        delay(1000);
        go(-150,150);
       delay(random(400,900));
     }else{
        go(-150,-150);
        delay(500);
        go(-150,150);
        delay(random(400,900));
     }
     succesor();
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
 
  if(current_time% 400 == 0){
    Serial.println("dist \tFS \tFD \tSS \tSD");
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
    Serial.println("cruise");
   if(status_robot == locate)
    Serial.println("locate");
      if(status_robot == engage)
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
/*  Serial.print("current_time is ");
    Serial.println(current_time);
    Serial.print("and state is");
    Serial.println(state);
    */
  }
  
   detect_border();

   if(status_robot == cruise && start_time + run_time < current_time)
     succesor();
   else if(status_robot == locate && (start_time + run_time < current_time || distance < 60))
       succesor();
   
   else if(status_robot == engage && start_time + run_time < current_time)
       succesor();

    
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

