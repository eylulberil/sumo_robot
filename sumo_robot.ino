#define TCRT_PIN PB6
#define START_BTN PA1

struct Motor {
  int in1_pin;
  int in2_pin;
};

Motor leftMotor = {PA0, PA1};
Motor rightMotor = {PA2, PA3};

int radar_mode_turn_direction = 1;

struct INFSENSOR {
  int right_pin;
  int middle_pin;
  int left_pin;
};

INFSENSOR infra_pin = {PB3, PB4, PB5}; //right, middle, left


unsigned long currentTime = 0, turn_start_time = 0;
bool is_radar_mode = false;

void setup() {
  pinMode(infra_pin.right_pin, INPUT);
  pinMode(infra_pin.middle_pin, INPUT);
  pinMode(infra_pin.left_pin, INPUT);
  pinMode(TCRT_PIN, INPUT);
  pinMode(SRT_BTN, INPUT);
  pinMode(leftMotor.in1_pin, OUTPUT);
  pinMode(leftMotor.in2_pin, OUTPUT);
  digitalWrite(leftMotor.in1_pin, LOW);
  digitalWrite(leftMotor.in2_pin, LOW);
  pinMode(rightMotor.in1_pin, OUTPUT);
  pinMode(rightMotor.in2_pin, OUTPUT);
  digitalWrite(rightMotor.in1_pin, LOW);
  digitalWrite(rightMotor.in2_pin, LOW);
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
    if(digitalRead(infra_pin.middle_pin) == 1) {
      is_radar_mode = false;
      moveTank(100, 100);
    } else {
      if(!is_radar_mode) {
        turn_start_time = millis();
      }
      if(digitalRead(infra_pin.right_pin) == 1) {
        radar_mode_turn_direction = 1;
      }
      if(digitalRead(infra_pin.left_pin) == 1) {
        radar_mode_turn_direction = -1;
      }
      is_radar_mode = true;
      moveTank(100*radar_mode_turn_direction, -100*radar_mode_turn_direction);
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
    digitalWrite(leftMotor.in1_pin, LOW);
    digitalWrite(leftMotor.in2_pin, HIGH);
  } else {
    digitalWrite(leftMotor.in2_pin, LOW);
    digitalWrite(leftMotor.in1_pin, HIGH);
  }


    if(power_right < 0) {
    digitalWrite(rightMotor.in1_pin, LOW);
    digitalWrite(rightMotor.in2_pin, HIGH);
  } else {
    digitalWrite(rightMotor.in2_pin, LOW);
    digitalWrite(rightMotor.in1_pin, HIGH);
  }
}