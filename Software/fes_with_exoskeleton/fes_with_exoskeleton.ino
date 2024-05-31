/*
What does the program need to do:
When the wrist is in the down position, send PWM signal to cathode pin.

When the wrist reaches maximum extension, turn off the PWM signal.

Always keep the servos running at a fixed angle. 

Optional Features
  Have the fingers extend/flex in time with teh wrist
  Automatically setup the wrist angle measurements. 
    Take measurement initially, activate PWM, wait until fully extended, take extended measurement
  


*/


const int in_size = 32;
char valin[in_size] = {0};

int parameters[3] = {50, 20, 0};    //pulse width, frequency, amplitude

unsigned long time_curr = 0;
unsigned long time_diff = 0;

//unsigned long period = 1000000/parameters[1];
unsigned long us_per_sec = 1000000;

#define pulse_width parameters[0]
#define freq parameters[1]
#define amp parameters[2]
#define period us_per_sec/freq

bool on = false;
bool exit = false;

const int cath_pin = 13;
const int wrist_pin = -1;
const int servo_pin = -1;
const int wrist_pin = -1;

int wrist_flexed = 0;
int wrist_extend = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  Serial.println("Arduino Ready!");
  pinMode(cath_pin, OUTPUT);
  digitalWrite(cath_pin, LOW);
  /*
  pinMode(wrist_pin, INPUT);
  wrist_flexed = digitalRead(wrist_pin);
  */
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(exit){ //exit code
    return;
  }

  if(Serial.available()){ //check to see if new parameters have been input
    Serial.readBytes(valin, in_size);
    Serial.print("You entered: ");
    tokenize(valin, ' ');
    Serial.println(parameters[0]);
    Serial.println(parameters[1]);
    Serial.println(parameters[2]);
    Serial.println(pulse_width);
  }



  time_diff = micros() - time_curr;
  if(freq > 0){
    if(time_diff > period){
      time_curr = micros();
      send_pulse();
    }
  }
}

void tokenize(char* str, char delimiter){
  if(*str == 'c'){
    exit = true;
  }
  char* token = strtok(str, " ");
  for(int i = 0; i < 3; i++){
    parameters[i] = atoi(token);
    token = strtok(NULL, " ");
  }
}

void send_pulse(){
  digitalWrite(cath_pin, HIGH);
  delayMicroseconds(pulse_width);
  digitalWrite(cath_pin, LOW);
}