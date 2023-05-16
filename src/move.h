#ifndef MOVE_H
#define MOVE_H

#define MOVE_SQ_DIM 10

bool *_move_path;
bool *_move_path_end;

void move_loop();
String move_log();

#endif

#ifdef MOVE_IMPL

#include <string.h>

void move_loop() {
	const int l = digitalRead(DEV_LINE_L);
	const int m = digitalRead(DEV_LINE_M);
	const int r = digitalRead(DEV_LINE_R);
	const int c = l + m + r;

	const int speed = 255;
		/*if (l) dev_set_speed(60, 255);
		else if (r) dev_set_speed(255, 60);*/
		if (l) dev_set_speed(0, 0);
		else if (r) dev_set_speed(0, 0);
		else dev_set_speed(speed, speed);
	/*switch (c) {
	case 0:
		dev_set_speed(255, -255);
		break;
	case 1:
		if (l) dev_set_speed(128, 255);
		else if (r) dev_set_speed(255, 128);
		else dev_set_speed(255, 255);
		break;
	case 2: { // this is hacky at best
		if (_move_path == _move_path_end)
			break;
		const bool p = *_move_path;
		++_move_path;
		if (p) {
			dev_set_speed(255, 255);
			delay(50);
			break;
		}

		if (l) {
			dev_set_speed(0, 255);
			delay(50);
		} else if (r) {
			dev_set_speed(255, 0);
			delay(50);
		}

		dev_set_speed(255, 255);
		delay(50);
		break;
	} case 3:
		digitalWrite(LED_BUILTIN, 1);	
		delay(200);
		digitalWrite(LED_BUILTIN, 0);	
		delay(200);
		digitalWrite(LED_BUILTIN, 1);	
		delay(200);
		digitalWrite(LED_BUILTIN, 0);	
		break;
	}*/
}

String move_log() {
	return String("");
}

#undef MOVE_IMPL
#endif
