#ifndef MOVE_H
#define MOVE_H

#define MOVE_SQ_DIM 10

bool *_move_path;
bool *_move_path_end;
int _move_swc;

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

	if (c == 0) {
		dev_set_speed(0, 0);
		return;
	}

	if (l && m || r && m) {
		// horrible cycle delta dependant stuff TODO XXX FIXME
		if (++_move_swc > 10) {
			dev_set_speed(0, 0);
			delay(500);
		}
	} else {
		_move_swc = 0;
	}

	if (l) dev_set_speed(0, 150);
	else if (r) dev_set_speed(150, 0);
	else dev_set_speed(150, 150);
}

String move_log() {
	return String("");
}

#undef MOVE_IMPL
#endif
