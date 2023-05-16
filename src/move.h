#ifndef MOVE_H
#define MOVE_H

#define MOVE_SQ_DIM 10
int move_field_w = 10;
int move_field_h = 10;

int _move_x = 0;
int _move_y = 0;
int _move_dirx = 1;
int _move_diry = 0;
int _move_target_x = 0;
int _move_target_y = 0;

bool _move_last_scan[3] = {0};

enum move_state {
	MoveStateIdle,
	MoveStateDrive
};

enum move_state _move_state = MoveStateIdle;

void move_loop();

#endif

#ifdef MOVE_IMPL

#include <string.h>

bool _move_scan_cmp(bool scan[3], bool l, bool m, bool r) {
	return scan[0] == l && scan[1] == m && scan[2] == r;
}

void _move_advance() {
	++_move_x;
	++_move_y;

	if (_move_dirx && _move_x == _move_target_x) {
		const bool clockwise = _move_y < _move_target_y;
		const int l = clockwise ? 255 : -255;
		const int r = clockwise ? -255 : 255;

		while (digitalRead(DEV_LINE_M)) {
			dev_set_speed(l, r);
			delay(20);
		}

		while (!digitalRead(DEV_LINE_M)) {
			dev_set_speed(l, r);
			delay(20);
		}
	}

	if (_move_diry && _move_y == _move_target_y) {
		const bool clockwise = _move_x < _move_target_x;
		const int l = clockwise ? 255 : -255;
		const int r = clockwise ? -255 : 255;

		while (digitalRead(DEV_LINE_M)) {
			dev_set_speed(l, r);
			delay(20);
		}

		while (!digitalRead(DEV_LINE_M)) {
			dev_set_speed(l, r);
			delay(20);
		}
	}
}

void move_loop() {
	bool scan[3] = {
		digitalRead(DEV_LINE_L),
		digitalRead(DEV_LINE_M),
		digitalRead(DEV_LINE_R)
	};

	switch (_move_state) {
	case MoveStateIdle:
		break;
	case MoveStateDrive:
		if (scan[0] && !scan[2]) {
			dev_set_speed(255, 200);
		} else if (!scan[0] && scan[2]) {
			dev_set_speed(200, 255);
		} else {
			dev_set_speed(255, 255);
		}

		if (_move_scan_cmp(scan, 1, 1, 1) &&
			_move_scan_cmp(_move_last_scan, 0, 1, 0))
				_move_advance();
		break;
	}

	memcpy(_move_last_scan, scan, sizeof(scan));
}

#undef MOVE_IMPL
#endif
