#include <stdint.h>

#ifndef MOVE_H
#define MOVE_H

#define MOVE_SQ_DIM 10

bool _move_swc = false;
uint64_t _move_swc_start = 0;
bool move_enabled = false;
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
			digitalWrite(LED_BUILTIN, 1);
			dev_set_speed(0, 0);
			delay(1000);
			digitalWrite(LED_BUILTIN, 0);
			char c = _move_path[_move_pathi++];
			if (c == NULL) {
				_move_pathi = 0;
				c = 'f';
			}

			switch (c) {
			case 'l':
				dev_set_speed(255, 255);
				delay(400);
				dev_set_speed(-255, 255);
				delay(200);
				while (!digitalRead(DEV_LINE_M))
					dev_set_speed(-255, 255);
				break;
			case 'f':
				dev_set_speed(255, 255);
				delay(800);
				break;
			case 'r':
				dev_set_speed(255, 255);
				delay(400);
				dev_set_speed(255, -255);
				delay(400);
				while (!digitalRead(DEV_LINE_M))
					dev_set_speed(255, -255);
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
	char buf[2048];
	sprintf(buf, "swc: %d\nen: %d\npath: %s\npathi: %s\n",
		_move_swc, move_enabled, _move_path, _move_pathi);
	return String(buf);
}

void move_set_path(const char *s) {
	strncpy(_move_path, s, sizeof(_move_path - 1));
	_move_pathi = 0;
}

#undef MOVE_IMPL
#endif
