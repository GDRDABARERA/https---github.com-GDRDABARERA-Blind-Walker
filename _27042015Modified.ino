

#define trigPin 13

#define echoPin 12

#define trigPin3 2

#define echoPin3 3

#define trigPin2 5

#define echoPin2 6

#define ledRight 11

#define ledLeft 10

#define ledMiddle 8




int defPOS = 0;

int array[10];

int x;

int SIZE = 10;


//Servo myservo;

void setup() {

  Serial.begin (9600);
  
  system("modprobe snd-usb-AudioNew");

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(trigPin2, OUTPUT);

  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);

  pinMode(echoPin3, INPUT);

  pinMode(ledRight, OUTPUT);

  pinMode(ledLeft, OUTPUT);
  
  pinMode(ledMiddle, OUTPUT);

 

}



void loop() {

  checkMiddle();
  //checkLeft();
  //checkRight();
  

  delay(500);

}


int ultraSonic2(){

    

    //long duration, distance;

    long duration2, distance2 ;
    int arrayRight[10];

    for(x=0 ; x< SIZE ; x++){

      

      //digitalWrite(trigPin, LOW); // Added this line

      digitalWrite(trigPin2, LOW);

      delayMicroseconds(2); // Added this line

      //digitalWrite(trigPin, HIGH);

      digitalWrite(trigPin2, HIGH);

      // delayMicroseconds(1000); - Removed this line

      delayMicroseconds(10); // Added this line

      //digitalWrite(trigPin, LOW);

      digitalWrite(trigPin2, HIGH);

      //duration = pulseIn(echoPin, HIGH);

      //distance = (duration) / 58.2;

      duration2 = pulseIn(echoPin2, HIGH);

      distance2 = (duration2) / 58.2;

      //arrayRight[x] = distance2;

      //array[x+5] = distance2; don't use

    }

    //distance2 = median(arrayRight);
      distance2 = mediansort(arrayRight, 10);
   

    
     return distance2;

}

int ultraSonic3(){

    

    //long duration, distance;

    long duration3, distance3 ;
    int arrayLeft[10];

    for(x=0 ; x< SIZE ; x++){

      

      //digitalWrite(trigPin, LOW); // Added this line

      digitalWrite(trigPin3, LOW);

      delayMicroseconds(2); // Added this line

      //digitalWrite(trigPin, HIGH);

      digitalWrite(trigPin3, HIGH);

      // delayMicroseconds(1000); - Removed this line

      delayMicroseconds(10); // Added this line

      //digitalWrite(trigPin, LOW);

      digitalWrite(trigPin3, HIGH);

      //duration = pulseIn(echoPin, HIGH);

      //distance = (duration) / 58.2;

      duration3 = pulseIn(echoPin3, HIGH);

      distance3 = (duration3) / 58.2;

      //arrayLeft[x] = distance3;

      //array[x+5] = distance2; don't use

    }

    //distance3 = median(arrayLeft); 
    distance3 = mediansort(arrayLeft, 10);
    
     return distance3;

}



int ultraSonic(){

    

    long duration, distance;
    
    int arrayMiddle[10];

    //long duration2, distance2 ;

    for(x=0 ; x< SIZE ; x++){

      

      digitalWrite(trigPin, LOW); // Added this line

      //digitalWrite(trigPin2, LOW);

      delayMicroseconds(2); // Added this line

      digitalWrite(trigPin, HIGH);

      //digitalWrite(trigPin2, HIGH);

      // delayMicroseconds(1000); - Removed this line

      delayMicroseconds(2); // Added this line

      digitalWrite(trigPin, LOW);

      //digitalWrite(trigPin2, HIGH);

      duration = pulseIn(echoPin, HIGH);

      distance = (duration) / 58.2;

      //duration2 = pulseIn(echoPin2, HIGH);

      //distance2 = (duration2) / 58.2;

      arrayMiddle[x] = distance;

      //array[x+5] = distance2; don't use

    }

    distance = mediansort(arrayMiddle, 10);

     return distance;
     

}



int checkLeft(){
   int flagLeft = 0 ;
   int distanceLeft = ultraSonic3();   

   if (distanceLeft >= 200 || distanceLeft <= 0){

      Serial.println("Left Clear,Turn left");
      flagLeft = 1 ;
      digitalWrite(ledLeft , HIGH);

   }

   else {

      Serial.print(distanceLeft);

      Serial.println(" cm from sensor left");

   }

   

   delay(100);
    
   digitalWrite(ledLeft, LOW);
   
   return flagLeft;

}



int checkRight(){
    
   int distanceRight = ultraSonic();

   int flagRight = 0 ;

   if (distanceRight >= 200 || distanceRight <= 0){

      Serial.println("Right Clear,Turn Right");
      flagRight = 1;
      digitalWrite(ledRight , HIGH);

   }

   else {

      Serial.print(distanceRight);

      Serial.println(" cm from sensor Right");

   } 

   

   delay(100);

   digitalWrite(ledRight, LOW);
   
   return flagRight;

}



void checkMiddle(){

   int distanceMid = ultraSonic();

   
   if (distanceMid >= 400 || distanceMid <= 0){

     Serial.println("Out of range Middle sensor");
     system("aplay /media/realroot/AudioNew/GoStraight.wav");
     

   }

   else {

     Serial.print(distanceMid);

     Serial.println(" cm from Middle sensor");
     digitalWrite(ledMiddle, HIGH);
     
     if(distanceMid > 300){
      system("aplay /media/realroot/AudioNew/GTenSF.wav"); 
     }
     else if(distanceMid > 270){
       system("aplay /media/realroot/AudioNew/GNineSF.wav");
     }
     else if(distanceMid > 240){
       system("aplay /media/realroot/AudioNew/GEightSF.wav");
     }
     else if(distanceMid > 210){
       system("aplay /media/realroot/AudioNew/GSevenSF.wav");
     }
     else if(distanceMid > 180){
       system("aplay /media/realroot/AudioNew/GSixSF.wav");
     }
     else if(distanceMid > 150){
       system("aplay /media/realroot/AudioNew/GFiveSF.wav");
     }
     else if(distanceMid > 120){
       system("aplay /media/realroot/AudioNew/GFourSF.wav");
     }
     else if(distanceMid > 90){
       system("aplay /media/realroot/AudioNew/GThreeSF.wav");
     }
    
     else{
       system("aplay /media/realroot/AudioNew/ThereIsSomeThingIFY.wav");
       
       
       int flagRight = checkRight();
       //Serial.println("End of checkLeft");
       Serial.print("flagRight :");
       Serial.println(flagRight);
  
       int flagLeft = checkLeft();
       //Serial.println("End of checkRight");
       Serial.print("flagLeft :");
       Serial.println(flagLeft);
       
       
       if( flagLeft == 1 && flagRight == 1 ){
         //system("aplay /media/realroot/AudioNewNew/TurnLeftOrRight");
       }
       else if( flagLeft == 0 && flagRight == 1){
         //system("aplay /media/realroot/AudioNew/TurnRight");
       }
       else if( flagLeft == 1 && flagRight == 0){
         system("aplay /media/realroot/AudioNew/TurnLeft.wav");
       }
  
       else{
          system("aplay /media/realroot/AudioNew/YouCan'tGo.wav");
       } 
     }     

   }  
    
    delay(500);
    digitalWrite(ledMiddle, LOW);
 

}



int mediansort(int m[], int n)
{
    int         i, less, greater, equal;
    float  min, max, guess, maxltguess, mingtguess;

    min = max = m[0] ;
    for (i=1 ; i<n ; i++) {
        if (m[i]<min) min=m[i];
        if (m[i]>max) max=m[i];
    }

    while (1) {
        guess = (min+max)/2;
        less = 0; greater = 0; equal = 0;
        maxltguess = min ;
        mingtguess = max ;
        for (i=0; i<n; i++) {
            if (m[i]<guess) {
                less++;
                if (m[i]>maxltguess) maxltguess = m[i] ;
            } else if (m[i]>guess) {
                greater++;
                if (m[i]<mingtguess) mingtguess = m[i] ;
            } else equal++;
        }
        if (less <= (n+1)/2 && greater <= (n+1)/2) break ; 
        else if (less>greater) max = maxltguess ;
        else min = mingtguess;
    }
    if (less >= (n+1)/2) return (int)maxltguess;
    else if (less+equal >= (n+1)/2) return (int)guess;
    else return (int) mingtguess;
}











/*

void bubbleSort(int array[]){

        boolean status;

        int i,k;

        for( k = 0 ; k < 10 ; k++ ){

            status = false;

            for( i = 9 ; i > k ; i-- ){

                if(array[i] < array[i-1]){

                    int temp = array[i-1];

                    array[i-1] = array[i];

                    array[i] = temp ;

                    status = true;

                }

            }

            

            if(status == false){

                break;

            }

        }
        //Serial.println("End of Bubble sort");
        
        //return array;

}
*/

/*
int median(int array[]){

  

  bubbleSort(array);

  

  int i;
  int v; 
  int sum = 0;

  int len = 0;  

  for(i=0;i<10-1;i++){

    //len = i;

    if((array[i+1]-array[i])> 50){

      break;

    }else{

      sum = sum + array[i];

      len++;

    }

  }
  
  for( v = 0 ; v < 10 ; v++ ){
   array[v] =0 ;
  } 
  
  //Serial.println("End of the Median calculation");
  return (int)(sum/len);

}

*/
