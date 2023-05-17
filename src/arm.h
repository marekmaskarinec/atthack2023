#ifndef ARM_H
#define ARM_H

void arm_up();

#endif

#ifdef ARM_IMPL

void _arm_attach() {
	dev_arm_servo_a.attach(DEV_ARM_SERVO_A_PIN);
	dev_arm_servo_b.attach(DEV_ARM_SERVO_B_PIN);
}

void _arm_detach() {
	dev_arm_servo_a.detach();
	dev_arm_servo_b.detach();
}

void arm_up() {
	_arm_attach();
	dev_arm_servo_a.write(175);
	delay(100);
	dev_arm_servo_b.write(180);
	delay(400);
	_arm_detach();
}

void arm_down() {
	_arm_attach();
	dev_arm_servo_a.write(88);
	delay(100);
	dev_arm_servo_b.write(94);
	delay(400);
	_arm_detach();
}

#endif
