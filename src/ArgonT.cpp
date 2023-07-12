/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Capstone/ArgonT/src/ArgonT.ino"
void setup();
void loop();
#line 1 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Capstone/ArgonT/src/ArgonT.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

SerialLogHandler logHandler;

void connectedCallback(const BlePeerDevice& peer, void* context);
void disconnectedCallback(const BlePeerDevice& peer, void* context);

BleUuid serviceUuid("afe7acc5-33a9-478f-bbe1-8944aa08e884");

void setup() {
	BLE.on();

	BLE.onConnected(connectedCallback, NULL);
	BLE.onDisconnected(disconnectedCallback, NULL);

    BleAdvertisingData advData;
    advData.appendServiceUUID(serviceUuid);
    BLE.advertise(&advData);
	BLE.setAdvertisingInterval(20);
}

void loop() {

}


void connectedCallback(const BlePeerDevice& peer, void* context) {
	Log.info("connected");

}

void disconnectedCallback(const BlePeerDevice& peer, void* context) {
	Log.info("disconnected");

}