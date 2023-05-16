#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <uri/UriBraces.h>

#ifndef NET_H
#define NET_H

WebServer _net_serv(80);

#define SSID "hackathon"
#define PWD "att4hack"

void net_init();
void net_loop();

#endif

#ifdef NET_IMPL


void _net_handle_not_found() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += _net_serv.uri();
	message += "\nMethod: ";
	message += (_net_serv.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += _net_serv.args();
	message += "\n";
	for (uint8_t i = 0; i < _net_serv.args(); i++) {
		message += " " + _net_serv.argName(i) + ": " + _net_serv.arg(i) + "\n";
	}
	_net_serv.send(404, "text/plain", message);
}


void net_init() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(SSID, PWD);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(SSID);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp32")) {
		Serial.println("MDNS responder started");
	}

	_net_serv.on("/", []() {
		String message = "Move:\n";
		//message += move_log();
		message += "\n-----\n\nDev:\n";
		message += dev_log();
		_net_serv.send(200, "text/plain", message);
	});

	_net_serv.on("api/enable", []() {
		move_enabled = true;
	});

	_net_serv.on("api/disable", []() {
		move_enabled = false;
	});

	_net_serv.on(UriBraces("api/path/{}"), []() {
		char *s = _net_serv.pathArg(0);
	});

	_net_serv.onNotFound(_net_handle_not_found);

	_net_serv.begin();
	Serial.println("HTTP _net_serv started");
}

void net_loop() {
	_net_serv.handleClient();
}

#endif
