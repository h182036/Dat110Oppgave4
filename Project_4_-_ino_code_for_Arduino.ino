int redPin = 13;
int yellowPin = 12;
int greenPin = 11;

int button1Pin = 7;
int button2Pin = 6;
int pirPin = 2;

int correctSequence[] = {1, 2};
int firstpressed = 0;
int secondpressed = 0;

int pirStatus = LOW;

void blink (int n, int pin) {
  
  for (int i = 0;i<n;i++) {
   
   digitalWrite(pin, LOW);
   delay(250); 
   digitalWrite(pin, HIGH);
   delay(250); 
  }
}

  const int LOCKED = 0;
  const int WAIT1P = 1;
  const int WAIT2P = 2;
  const int CHECKING = 3;
  const int UNLOCKED = 4;
  int state = LOCKED;

void setstate (int newstate) {
  state = newstate;
  printstate();
}

void printstate() {

  switch (state) {
    case LOCKED:
    Serial.println("LOCKED");
    break;

    case WAIT1P:
    Serial.println("WAIT1P");
    break;

    case WAIT2P:
    Serial.println("WAIT2P");
    break;

    case CHECKING:
    Serial.println("CHECKING");
    break;

    case UNLOCKED:
    Serial.println("UNLOCKED");
    break;

    default:
    Serial.println("ILLEGAL STATE");
    break;
  }
}

//parameters are either HIGH or LOW
void setleds(int red, int yellow, int green) {
  digitalWrite(redPin, red);
  digitalWrite(yellowPin, yellow);
  digitalWrite(greenPin, green);
}

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(pirPin, INPUT);

  
  printstate();
  
}

void loop()
{
  int pirsensor = digitalRead(pirPin);
  int button1 = digitalRead(button1Pin);
  int button2 = digitalRead(button2Pin);
  
  switch (state) {
    
    case LOCKED:
     setleds(HIGH, LOW, LOW);

    if(pirsensor == HIGH){
      setleds(LOW, HIGH, LOW);
      setstate(WAIT1P);
    }
    break;
    
    case WAIT1P:
    
    if( (button1 == HIGH) || (button2 == HIGH)) {
      blink(3, yellowPin);
      
      if(button1 == HIGH) {
        firstpressed = 1;
      }
      
      if(button2 == HIGH) {
        firstpressed = 2;
      }
      
      setstate(WAIT2P);
      
    }
    break;
    
    case WAIT2P:
    if( (button1 == HIGH) || (button2 == HIGH)) {
      blink(3, yellowPin);
      
      if(button1 == HIGH) {
        secondpressed = 1;
      }
      
      if(button2 == HIGH) {
        secondpressed = 2;
      }
      
      setstate(CHECKING);
    }
    break;
    
    case CHECKING:
    if( (firstpressed == correctSequence[0]) && (secondpressed == correctSequence[1])){
     setstate(UNLOCKED); 
    } else {
      blink(3, redPin);
      setleds(HIGH, LOW, LOW);
      setstate(LOCKED);
    }
    
    firstpressed = 0;
    secondpressed = 0;
    break;
    
    case UNLOCKED:
    blink(3, greenPin);
    setleds(LOW, LOW, HIGH);
    
    delay(5000);
    
    blink(3, redPin);
    setstate(LOCKED);
    break;
    
    default:
    break; 
  }
  
 
}