// Serial connection with computer, VSCode
#include <Servo.h>

// ultrasonic ports and veriables
const int trigPin = 2;
const int echoPin = 4;
const int ledPin = 11;

float duration, distance;
unsigned long ledStartTime = 0;
bool ledOn = false;

// servo connections and constants
Servo servo_thumb;
Servo servo_pointer;
Servo servo_middle;
Servo servo_ring;
Servo servo_pinky;

int full_down_values[5] = {600, 720, 750, 760, 700};
int half_down_values[5] = {600, 600, 600, 600, 600};

int full_up_values[5] = {600, 860, 770, 820, 710};
int half_up_values[5] = {600, 600, 600, 600, 600};
int full_down = 2;
int half_down = 1;

int servo_speed_set = 70;
int servo_speed_reset = 110;

Servo fingers[5] = {servo_pinky, servo_ring, servo_middle, servo_pointer, servo_thumb};

// int pos_thumb, pos_pointer, pos_middle, pos_ring, pos_pinky;

int letters[26][2][5] = {
  { // A
    {0, 1, 2, 3, 4}, // finger order 0 (pinky) -> 4 (thumb)
    {full_down, full_down, full_down, full_down, 0} // finger states
  },
  { // B
    {0, 1, 2, 3, 4},
    {0, 0, 0, 0, full_down}
  },
  { // C
    {0, 1, 2, 3, 4},
    {half_down, half_down, half_down, half_down, 0}
  },
  { // D
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, 0, full_down}
  },
  { // E
    {0, 1, 2, 3, 4},
    {half_down, half_down, half_down, half_down, full_down}
  },
  { // F
    {0, 1, 2, 3, 4},
    {0, 0, 0, full_down, full_down}
  },
  { // G
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, 0, half_down}
  },
  { // H
    {0, 1, 2, 3, 4},
    {full_down, full_down, 0, 0, full_down}
  },
  { // I
    {0, 1, 2, 3, 4},
    {0, full_down, full_down, full_down, full_down}
  },
  { // J
    {0, 1, 2, 3, 4},
    {0, full_down, full_down, full_down, full_down}
  },
  { // K
    {0, 1, 2, 3, 4},
    {full_down, full_down, 0, 0, full_down}
  },
  { // L
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, 0, 0}
  },
  { // M
    {4, 3, 2, 1, 0},
    {full_down, full_down, full_down, full_down, full_down}
  },
  { // N
    {0, 1, 4, 2, 3},
    {full_down, full_down, full_down, full_down, full_down}
  },
  { // O
    {0, 1, 2, 3, 4},
    {half_down, half_down, half_down, half_down, half_down}
  },
  { // P
    {0, 1, 2, 3, 4},
    {full_down, full_down, half_down, 0, full_down}
  },
  { // Q
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, 0, full_down}
  },
  { // R
    {0, 1, 2, 3, 4},
    {full_down, full_down, 0, 0, full_down}
  },
  { // S
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, full_down, full_down}
  },
  { // T
    {0, 1, 2, 4, 3},
    {full_down, full_down, full_down, full_down, full_down}
  },
  { // U
    {0, 1, 2, 3, 4},
    {full_down, full_down, 0, 0, full_down}
  },
  { // V
    {0, 1, 2, 3, 4},
    {full_down, full_down, 0, 0, full_down}
  },
  { // W
    {0, 1, 2, 3, 4},
    {full_down, 0, 0, 0, full_down}
  },
  { // X
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, half_down, full_down}
  },
  { // Y
    {0, 1, 2, 3, 4},
    {0, full_down, full_down, full_down, 0}
  },
  { // Z
    {0, 1, 2, 3, 4},
    {full_down, full_down, full_down, 0, full_down}
  }
};


void set_letter (char input_letter)
{
  char letter = input_letter;
  int num_letter = letter - 'A';

  int finger = 0;
  int time = 0;
  int state = 0;


  for(int i = 0; i<5; i++) {
    finger = letters[num_letter][0][i];
    state = letters[num_letter][1][i];

    if (state == 2) {
      time = full_down_values[i];
      fingers[finger].write(servo_speed_set);
      delay(time);
      fingers[finger].write(90);
    } else if (state == 1) {
      time = half_down_values[i];
      fingers[finger].write(servo_speed_set);
      delay(time);
      fingers[finger].write(90);
    }
  }
}

void reset (char input_letter) {
  char letter = input_letter;
  int num_letter = letter - 'A';

  int finger = 0;
  int state = 0;
  int time = 0;

  for(int i = 4; i>-1; i--) {
    finger = letters[num_letter][0][i];
    state = letters[num_letter][1][i];

    if (state == 2) {
      time = full_up_values[i];
      fingers[finger].write(servo_speed_reset);
      delay(time);
      fingers[finger].write(90);
    } else if (state == 1) {
      time = half_up_values[i];
      fingers[finger].write(servo_speed_reset);
      delay(time);
      fingers[finger].write(90);
    }
  }
}

void setup() {
  Serial.begin(9600);
  servo_thumb.attach(3, 500, 2500);
  servo_pointer.attach(5, 500, 2500);
  servo_middle.attach(6, 500, 2500);
  servo_ring.attach(9, 500, 2500);
  servo_pinky.attach(10, 500, 2500);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
 
  servo_thumb.write(90);
  servo_pointer.write(90);
  servo_middle.write(90);
  servo_ring.write(90);
  servo_pinky.write(90);

  while (!Serial) { } // wait for Serial to connect (good for Leonardo/Micro)
  Serial.println("Arduino ready");

  delay(2000);
  // for (int i = 0; i < 5; i++) {

  //   fingers[i].write(servo_speed_set);
  //   delay(full_down_values[i]);
  //   fingers[i].write(90);

  //   delay(1000);

  //   fingers[i].write(servo_speed_reset);
  //   delay(full_up_values[i]);
  //   fingers[i].write(90);

  // }

}

void loop() {

  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration*0.0342)/2;

  if (distance < 5 && !ledOn && distance != 0) {
    Serial.println("PLAY1");
    for (int i = 0; i < 200; i+=1) {
      analogWrite(ledPin, i);
      delay(25);
    }
    ledOn = true;
    //ledStartTime = millis();
  }
 
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // read until newline
    input.trim(); // remove any extra whitespace
   
    char letter = input.charAt(0);

    Serial.println("Received");
   
    set_letter(letter);
    delay(3000);
    reset(letter);
    Serial.println("Finished");
  }
}

// Good Letter!!!!!!! *************************
// a, b, , d, , f, i, k (u, v), l, s, w, y

// no thumb, a, c, l, y
// ********************************************