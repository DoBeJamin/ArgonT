#include "MQTT.h"
#include "LIS3DH.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);


//MQTT
void callback(char *topic, byte *payload, unsigned int length) {};
MQTT client("lab.thewcl.com", 1883, callback);

//accelerometer
LIS3DHSPI accel(SPI, D3, WKP);

//Bluetoth Beacon
SerialLogHandler logHandler;

void connectedCallback(const BlePeerDevice& peer, void* context);
void disconnectedCallback(const BlePeerDevice& peer, void* context);

BleUuid serviceUuid("afe7acc5-33a9-478f-bbe1-8944aa08e884");

void setup() {

	//configure accelerometer
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);
	accel.setup(config);

	//bluetooth
	BLE.on();
	BLE.onConnected(connectedCallback, NULL);
	BLE.onDisconnected(disconnectedCallback, NULL);

    BleAdvertisingData advData;
    advData.appendServiceUUID(serviceUuid);
    BLE.advertise(&advData);
	BLE.setAdvertisingInterval(20);
}

void loop() {

	LIS3DHSample sample;
  	if (accel.getSample(sample)) {

		//some tomfoolery bc publish didn't like taking in an int and sample didn't like being put into a String
		int x = sample.x;
		int y = sample.y;
		int z = sample.z;

		String xs = String(x);
		String ys = String(y);
		String zs = String(z);


		client.publish("BAR/argonT/accel/x", xs);
		client.publish("BAR/argonT/accel/y", ys);
		client.publish("BAR/argonT/accel/z", zs);

	}
}


void connectedCallback(const BlePeerDevice& peer, void* context) {
	Log.info("connected");

}

void disconnectedCallback(const BlePeerDevice& peer, void* context) {
	Log.info("disconnected");

}