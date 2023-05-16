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

#endif

#ifdef MOVE_IMPL

#include <string.h>

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
		
		break;
	}

	memcpy(_move_last_scan, scan, sizeof(scan));
}

#undef MOVE_IMPL
#endif
