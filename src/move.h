#include <stdint.h>

#ifndef MOVE_H
#define MOVE_H

#define MOVE_SQ_DIM 10

bool _move_swc = false;
uint64_t _move_swc_start = 0;
bool move_enabled = true;
char _move_path[256] = {0};
int _move_pathi = 0;

void move_loop();
String move_log();
void move_set_path(char *s);

#endif

#ifdef MOVE_IMPL

#include <string.h>

void move_loop() {
	if (!move_enabled) {
		dev_set_speed(0, 0);
		return;
	}

	const int l = digitalRead(DEV_LINE_L);
	const int m = digitalRead(DEV_LINE_M);
	const int r = digitalRead(DEV_LINE_R);
	const int c = l + m + r;

	if (c == 0) {
		dev_set_speed(0, 0);
		return;
	}

	if (c == 3) {
		const uint64_t mcs = micros();
		if (!_move_swc) {
			_move_swc = true;
			_move_swc_start = mcs;
		}

		if (mcs - _move_swc_start > 120000) {
			dev_set_speed(0, 0);
			delay(1000);
			char c = _move_path[_move_pathi++];

			switch (c) {
			case 'l':
				dev_set_speed(80, 255);
				delay(500);
				break;
			case 'm':
				dev_set_speed(255, 255);
				delay(500);
				break;
			case 'r':
				dev_set_speed(255, 80);
				delay(800);
				break;
			}
		}
	} else {
		_move_swc = false;
	}

	if (l && !r) dev_set_speed(0, 150);
	else if (r && !l) dev_set_speed(150, 0);
	else dev_set_speed(150, 150);
}

String move_log() {
	return String("");
}

void move_set_path(char *s) {
	strncpy(_move_path, s, sizeof(_move_path - 1));
	_move_pathi = 0;
}

#undef MOVE_IMPL
#endif
