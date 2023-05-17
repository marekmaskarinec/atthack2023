
#define DEV_IMPL
#include "dev.h"

#define MOVE_IMPL
#include "move.h"

#define NET_IMPL
#include "net.h"

#define ARM_IMPL
#include "arm.h"

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	dev_init();
	net_init();

	arm_up();
	delay(2000);
	arm_down();
	digitalWrite(DEV_MAGNET_PIN, 1);
	delay(500);
	arm_up();
}

void loop() {
	move_loop();
	net_loop();
}
