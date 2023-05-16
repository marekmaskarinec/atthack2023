
#define DEV_IMPL
#include "dev.h"

#define MOVE_IMPL
#include "move.h"

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	dev_init();
}

void loop() {
	move_loop();

	digitalWrite(LED_BUILTIN, 1);
	delay(1000);
	digitalWrite(LED_BUILTIN, 0);
	delay(1000);
}
