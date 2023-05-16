#include <ESP32Servo.h>

#ifndef DEV_H
#define DEV_H

#define DEV_LINE_L 0
#define DEV_LINE_M 0
#define DEV_LINE_R 0

#define DEV_SERVO_L_PIN 0
#define DEV_SERVO_R_PIN 0

Servo dev_servo_l;
Servo dev_servo_r;

void dev_init();
void dev_set_speed(int l, int r);

#endif

#ifdef DEV_IMPL

void dev_init() {
	pinMode(DEV_LINE_L, INPUT);
	pinMode(DEV_LINE_M, INPUT);
	pinMode(DEV_LINE_R, INPUT);

	dev_servo_l.attach(DEV_SERVO_L_PIN);
	dev_servo_r.attach(DEV_SERVO_R_PIN);
}

void dev_set_speed(int l, int r) {

}

#undef DEV_IMPL
#endif
