
#define DEV_IMPL
#include "dev.h"

#define MOVE_IMPL
#include "move.h"

#define NET_IMPL
#include "net.h"

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	dev_init();
	//net_init();
}

void loop() {
	move_loop();
	//net_loop();
}
