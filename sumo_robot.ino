#define INF_PIN B3
#define TCRT_PIN 2
#define START_BTN 7
struct Motor {
  int in1_pin;
  int in2_pin;
};


Motor leftMotor = {A0, A1};  // IN1, IN2
Motor rightMotor = {A2, A3};

unsigned long currentTime = 0, turn_start_time = 0;
bool is_radar_mode = false;

void setup() {
  pinMode(INF_PIN, INPUT);
  pinMode(TCRT_PIN, INPUT);
  pinMode(SRT_BTN, INPUT);
  pinMode(leftMotor.in1_pin, OUTPUT);
  pinMode(leftMotor.in2_pin, OUTPUT);
  pinMode(rightMotor.in1_pin, OUTPUT);
  pinMode(rightMotor.in2_pin, OUTPUT);
  currentTime = millis();
  turn_start_time = millis();
}

void loop() {
  while(1) {
    if(digitalRead(START_BTN) == 1)
      break;
  }
  delay(5000);
  while(1) { //fight started
  currentTime = millis();
    if(digitalRead(INF_PIN) == 1) {
      is_radar_mode = false;
      moveTank(100, 100);
    } else {
      if(!is_radar_mode) {
        turn_start_time = millis();
      }
      is_radar_mode = true;
      moveTank(100, -100);
      if(currentTime - turn_start_time > 3000)
        break;
    }

    if(igitalRead(TCRT_PIN) == 1) {
      moveTank(-100, -100);
      delay(100);
    }


  }

}



void moveTank(int power_left, int power_right) {
  
  if(power_left < 0) {
    //power_left = power_left*-1;
    digitalWrite(leftMotor.in1_pin, LOW);
    digitalWrite(leftMotor.in2_pin, HIGH);
  } else {
    digitalWrite(leftMotor.in2_pin, LOW);
    digitalWrite(leftMotor.in1_pin, HIGH);
  }
  //analogWrite(leftMotor.pwm_pin, round(power_left/2.55));


    if(power_right < 0) {
    //power_right = power_right*-1;
    digitalWrite(rightMotor.in1_pin, LOW);
    digitalWrite(rightMotor.in2_pin, HIGH);
  } else {
    digitalWrite(rightMotor.in2_pin, LOW);
    digitalWrite(rightMotor.in1_pin, HIGH);
  }
  //analogWrite(rightMotor.pwm_pin, round(power_right/2.55));
}