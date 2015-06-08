#define trigPin 13
#define echoPin 12
#define trigPin3 2
#define echoPin3 3
#define trigPin2 5
#define echoPin2 6
#define ledRight 11
#define ledLeft 10
#define ledMiddle 8


//#define 30cmbutton 1
#define 40cmbutton 1

int defPOS = 0;
int array[10];
int x;
int SIZE = 10;
int butonState=0;

int STEPSIZE;
int putstep;






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


// pinMode(30cmbutton, INPUT);
 pinMode(40cmbutton, INPUT);
 
}

void loop() {
  // Calibrating part
  buttonState = digitalRead(40cmbutton);
  
  if(buttonState==HIGH){
    STEPSIZE =30;
  }else{
    STEPSIZE =40;
  }
  
   goStraight();
  
}

public  static void insertion_sort(int [] data) { 
           int i,j,tmp;
           
           for(i=1;i<data.length;i++){
               int value= data[i];
               j=i-1;
               while(j>=0&& data[j]>value){
                  
                   data[j+1]= data[j];
                   j--;
               }
               data[j+1]=value;
           
           } 
         
            
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



int ultraSonic(){

    

    long duration, distance, avgdistance;
    
    int arrayMiddle[10];

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

    

    }

  //  avgdistance = mediansort(arrayMiddle, 10);
   avgdistance = insertion_sort(arrayMiddle, 10);
   return avgdistance;
     

}


void goStraight(){
   int avgDistance = ultraSonic();
   distanceMid = avgDistance / STEPSIZE;
   
   if (distanceMid >= (400/STEPSIZE) || distanceMid <= 0){

     Serial.println("Out of range Middle sensor");
     system("aplay /media/realroot/AudioNew/GoStraight.wav");
     

   }

   else {
    
     Serial.print(distanceMid);

     Serial.println(" cm from Middle sensor");
     digitalWrite(ledMiddle, HIGH);
     
     if(distanceMid > 300/STEPSIZE){
      system("aplay /media/realroot/AudioNew/GTenSF.wav"); 
     }
     else if(distanceMid > 270/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GNineSF.wav");
     }
     else if(distanceMid > 240/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GEightSF.wav");
     }
     else if(distanceMid > 210/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GSevenSF.wav");
     }
     else if(distanceMid > 180/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GSixSF.wav");
     }
     else if(distanceMid > 150/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GFiveSF.wav");
     }
     else if(distanceMid > 120/STEPSIZE){
       system("aplay /media/realroot/AudioNew/GFourSF.wav");
     }
     else if(distanceMid > 90/STEPSIZE){
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



