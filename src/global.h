#include <pthread.h>
#include <MQTTClient.h>

// Configuration file
#define CONFIGFILE 		"/etc/anavilight.ini"

// Default configuratons
#define ADDRESS			"tcp://hassbian.local:1883"
#define CLIENTID		"ANAVI-Light-pHAT"

// MQTT topics

// For sensors
#define TOPICTEMPERATURE 	"sensors/temperature"
#define TOPICPRESSURE 		"sensors/pressure"
#define TOPICTEMPERATURE1 	"sensors/temperature1"
#define TOPICHUMIDITY 		"sensors/humidity"
#define TOPICLIGHT 		"sensors/light"

#define MSGNOSENSOR 		"Sensor not found"

// For actions
#define TOPICACTIONS 		"action/#"

#define TOPICACTION		"action"
#define TOPICRGBLED		"rgbled"

// GPIO

//Pin 19 on Raspberry Pi corresponds to BCM GPIO 10 and wiringPi pin 12 for blue
#define PINRGBLED1 		12
//Pin 21 on Raspberry Pi corresponds to BCM GPIO 9 and wiringPi pin 14 for green
#define PINRGBLED2 		14
//Pin 23 on Raspberry Pi corresponds to BCM GPIO 11 and wiringPi pin 13 for red
#define PINRGBLED3 		13

pthread_t tid[3];

struct sensors {
	double temperature;
	double humidity;
	double temperature1;
	double pressure;
	int light;
	int buzzer;
	int relay;
	int rgbLed;
} sensors, status;

volatile MQTTClient_deliveryToken deliveredtoken;

volatile int lcdHandle;

MQTTClient client;
MQTTClient_deliveryToken token;
