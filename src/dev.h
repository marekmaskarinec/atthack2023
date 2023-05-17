#include <ESP32Servo.h>

#ifndef DEV_H
#define DEV_H

#define DEV_LINE_L 17
#define DEV_LINE_M 25
#define DEV_LINE_R 26

#define DEV_SERVO_L_PIN 13
#define DEV_SERVO_R_PIN 5

#define DEV_ARM_SERVO_A_PIN 27
#define DEV_ARM_SERVO_B_PIN 14

#define DEV_MAGNET_PIN 4

Servo dev_servo_l;
Servo dev_servo_r;
Servo dev_arm_servo_a;
Servo dev_arm_servo_b;

void dev_init();
void dev_set_speed(int l, int r);
String dev_log();

#endif

#ifdef DEV_IMPL

void dev_init() {
	pinMode(DEV_LINE_L, INPUT);
	pinMode(DEV_LINE_M, INPUT);
	pinMode(DEV_LINE_R, INPUT);

	pinMode(DEV_MAGNET_PIN, OUTPUT);

	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	dev_servo_l.attach(DEV_SERVO_L_PIN);
	dev_servo_r.attach(DEV_SERVO_R_PIN);
}

void dev_set_speed(int l, int r) {	// 0 - still; -255 - full speed back; 255 - full speed forward 
	dev_servo_l.write(map(l, -255, 255, 0, 180));	// dirty speed hack
	dev_servo_r.write(map(-r, -255, 255, 0, 180));
}

String dev_log() {
	char buf[2048];
	sprintf(buf, "IR L: %d\nIR M: %d\nIR R: %d\n",
		digitalRead(DEV_LINE_L),
		digitalRead(DEV_LINE_M),
		digitalRead(DEV_LINE_R));
	return buf;
}

#undef DEV_IMPL
#endif
