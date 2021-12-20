#include <Servo.h>

Servo serv_x;
Servo serv_y;

int incoming_byte = 0;
int led = 0;
int cam_x = 90;
int cam_y = 90;
int cam_inc = 30;

void setup() {
  Serial.begin(9600);   // Baudrate is 9600
  serv_x.attach(7);     // Servo data pins are 7 and 4
  serv_y.attach(4);
  serv_x.write(cam_x);  // Initialize servo position
  serv_y.write(cam_y);
}

// Prevent attempts to move servo beyond allowed limits
// 0 <= x <= 180
int bound(int x) {
  if (x < 0) {
    return 0;
  } else if (x > 180) {
    return 180;
  } else {
    return x;
  }
}

void loop() {
    if (Serial.available() > 0) {
        // Read the incoming byte
        incoming_byte = Serial.read();
    
        if (incoming_byte == 2) {
          // LEFT
          serv_x.write(bound(cam_x - cam_inc));
          cam_x = bound(cam_x - cam_inc);
        } else if (incoming_byte == 3) {
          // RIGHT
          serv_x.write(bound(cam_x + cam_inc));
          cam_x = bound(cam_x + cam_inc);
        } else if (incoming_byte == 4) {
          // UP
          serv_y.write(bound(cam_y + cam_inc));
          cam_y = bound(cam_y + cam_inc);
        } else if (incoming_byte == 5) {
          // DOWN
          serv_y.write(bound(cam_y - cam_inc));
          cam_y = bound(cam_y - cam_inc);
        } else if (incoming_byte == 6) {
          // CENTER
          serv_x.write(90);
          serv_y.write(90);
          cam_x = 90;
          cam_y = 90;
        }
    }
}
