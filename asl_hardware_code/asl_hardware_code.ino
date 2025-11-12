// Serial connection with computer, VSCode
#include <Servo.h>

Servo servo_thumb;
Servo servo_pointer;
Servo servo_middle;
Servo servo_ring;
Servo servo_pinky;

int full_down = 650;
int half_down = 600;
// int pos;

int servo_speed_set = 70;
int servo_speed_reset = 110;

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
    {full_down, full_down, full_down, half_down, 0}
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


  for(int i = 0; i<5; i++) {
    finger = letters[num_letter][0][i];
    time = letters[num_letter][1][i];

    if (time != 0) {

      
      if(finger == 4)
      {
        servo_thumb.write(servo_speed_set);
        delay(time);
        servo_thumb.write(90);
        // pos_thumb = pos;
      }
      else if(finger == 3)
      {
        servo_pointer.write(servo_speed_set);
        delay(time);
        servo_pointer.write(90);
        // pos_pointer = pos;
      }
      else if(finger == 2)
      {
        servo_middle.write(servo_speed_set);
        delay(time);
        servo_middle.write(90);
        // pos_middle = pos;
      }
      else if(finger == 1)
      {
        servo_ring.write(servo_speed_set);
        delay(time);
        servo_ring.write(90);
        // pos_ring = pos;
      }
      else {
        servo_pinky.write(servo_speed_set);
        delay(time);
        servo_pinky.write(90);
        //pos_pinky = pos;
      }
    }
  }
}

void reset (char input_letter) {
  char letter = input_letter;
  int num_letter = letter - 'A';
  int finger = 0;
  int time = 0;

  for(int i = 4; i>-1; i--) {
    finger = letters[num_letter][0][i];

    time = letters[num_letter][1][i];

    if (time != 0) {
      time -= 50;
    

      if(finger == 4)
      {
        servo_thumb.write(servo_speed_reset);
        delay(time);
        servo_thumb.write(90);
        // pos_thumb = pos;
      }
      else if(finger == 3)
      {
        servo_pointer.write(servo_speed_reset);
        delay(time);
        servo_pointer.write(90);
        // pos_pointer = pos;
      }
      else if(finger == 2)
      {
        servo_middle.write(servo_speed_reset);
        delay(time);
        servo_middle.write(90);
        // pos_middle = pos;
      }
      else if(finger == 1)
      {
        servo_ring.write(servo_speed_reset);
        delay(time);
        servo_ring.write(90);
        // pos_ring = pos;
      }
      else {
        servo_pinky.write(servo_speed_reset);
        delay(time);
        servo_pinky.write(90);
        //pos_pinky = pos;
      }
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
  while (!Serial) { } // wait for Serial to connect (good for Leonardo/Micro)
  Serial.println("Arduino ready");
  servo_thumb.write(90);
  servo_pointer.write(90);
  servo_middle.write(90);
  servo_ring.write(90);
  servo_pinky.write(90);
  delay(5000);
}

void loop() {
  set_letter('B');
  delay(5000);
  reset('B');
  delay(5000);

  // if (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n'); // read until newline
  //   input.trim(); // remove any extra whitespace
  //   Serial.print("You sent: ");
  //   Serial.println(input);
   
  //   set_letter(input);
  //   delay(5000);
  //   reset(input);
  // }
}

