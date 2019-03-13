#include <Servo.h>


// When used with the Rev SPARK ontroller, he NEOS can be controller using the same PWM
// frequencies used to control a servo motor.  A servo typically uses pulses bwteeen
//  1.5ms and 2.5ms to set the angle of the servo between 0-180 (proportionally).
//
// Ther NEOS motor controller responds the same way with 1.5ms being full reverse,
// 2.0ms being stopped, and 2.5ms being full forward (with proportional forward and
// backward speeds


//  pwm output pin

#define   PIN_PWM_OUT     9


// control input pin

#define   PIN_POT_IN      A0


// indicator LED pins

#define   PIN_RED_LED     5
#define   PIN_YELLOW_LED  6
#define   PIN_GREEN_LED   7

#define   LED_FWD         PIN_GREEN_LED
#define   LED_STOP        PIN_YELLOW_LED
#define   LED_REV         PIN_RED_LED


// any A2D inputs +/- this value from zero put out the 90 degree value
// (1.5ms PWM) whic is stopped on the NEOS controller - this prevents us from having
// to hit an exact singukar position on the control pot to stop the motor at the
// expense of loosing the very low speed forward and backward speeds

#define   ZERO_ZONE       50    

#define   PWM_STOP_VALUE  90      // "degrees" on the servo that will stop the NEOS

#define   A2D_MAX         1023
#define   ANGLE_MAX       180     // servos go from 0-180 degrees


Servo pwmOut;   // we use the Servo library becauise that gives us the
                // oppropriate PWM drive capabilities (The NEOS controller
                // basically responds liek a servo motor)



void setup() {
  
  pwmOut.attach(PIN_PWM_OUT);         // initialize the "servo"

  pinMode(PIN_RED_LED, OUTPUT);       // setup LEDs
  pinMode(PIN_YELLOW_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  
}




void loop() {
  
  int value;

  while ( 1 ) {

    value = analogRead(PIN_POT_IN);     // returns an A2D value from 0 through A2D_MAX

    // are we in the "zero" zone where we want to stoip the motor?
  
    if (value > (A2D_MAX / 2 - ZERO_ZONE) || value < (A2D_MAX / 2 + ZERO_ZONE)) {

      pwmOut.write(PWM_STOP_VALUE);

      digitalWrite(LED_FWD, LOW);     // off
      digitalWrite(LED_STOP, HIGH);   // on
      digitalWrite(LED_REV, LOW);     // off

      continue;
    }

    // scale it - maps from A2D input to servo "degrees"
    
    value = map(value, 0, A2D_MAX, 0, ANGLE_MAX);
    
    pwmOut.write(value);          // set the PWM frequency to control the NEOS
  }
}
