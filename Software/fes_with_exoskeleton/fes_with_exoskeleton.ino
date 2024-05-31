/*

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



int cath_pin = 13;
int wrist_pin = -1;
int servo_pin = -1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  Serial.println("Arduino Ready!");
  pinMode(cath_pin, OUTPUT);
  digitalWrite(cath_pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(cath_pin, HIGH);


  if(Serial.available()){
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

  //delay(10);
}


void tokenize(char* str, char delimiter){
  char* token = strtok(str, " ");
  for(int i = 0; i < 3; i++){
    parameters[i] = atoi(token);
    token = strtok(NULL, " ");
  }
  // char *token = strtok(str, " ");

  // // Keep printing tokens while one of the
  // // delimiters present in str[].
  // while (token != NULL)
  // {
  //     Serial.println(atoi(token));
  //     token = strtok(NULL, " ");
  // }
}

void send_pulse(){
  digitalWrite(cath_pin, HIGH);
  delayMicroseconds(pulse_width);
  digitalWrite(cath_pin, LOW);
}









