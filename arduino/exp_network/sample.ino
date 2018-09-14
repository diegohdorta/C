#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>

#define RED   	13
#define YELLOW 	12
#define GREEN 	11

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xB9, 0x80};

EthernetServer server(23);
EthernetClient client;

int button_state = 0;
int status_red = 0;
int status_yellow = 0;
int status_green = 0;

boolean gotAMessage = false;

void handler(char thisChar);
void printIPAddress();

void setup() 
{
	Serial.begin(9600);
	Serial.print("Trying to get an IP using DHCP...\n");

	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(GREEN, OUTPUT);

	digitalWrite(RED, HIGH);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(GREEN, HIGH);

	lcd.begin(16, 2);
	lcd.print("Getting IP...");

	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
		lcd.setCursor(0, 1);
		lcd.print("Error IP");
		exit(0);      
	}

	Serial.print("Calling function to print IP address!\n");
	printIPAddress();
	server.begin();
}

void loop() 
{
	delay(1000);
	digitalWrite(RED, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, LOW);

	Serial.print("Initializing program...\n");

	while(1) {

		client = server.available();

		if (client) {
			if (!gotAMessage) {
				Serial.println("We have a new client");
				gotAMessage = true;
		}

		char thisChar = client.read();

		Serial.print(thisChar);
		handler(thisChar);         

		Ethernet.maintain();
		}
	} 
	/*
		https://www.arduino.cc/en/Tutorial/DhcpChatServer
		https://www.arduino.cc/en/Tutorial/DhcpAddressPrinter
	*/
}

void handler(char thisChar)
{
	switch (thisChar) {

		case 'a':
			Serial.print("\nReceived A command!\n");
			digitalWrite(RED, HIGH);
			client.write("RED LED: ON\n");
			break;

		case 'b':
			Serial.print("\nReceived B command!\n");
			digitalWrite(YELLOW, HIGH);
			client.write("YELLOW LED: ON\n");
			break;

		case 'c':
			Serial.print("\nReceived C command!\n");
			digitalWrite(GREEN, HIGH);
			client.write("GREEN LED: ON\n");
			break;

		case 'd':
			Serial.print("\nReceived D command!\n");
			digitalWrite(RED, LOW);
			client.write("RED LED: OFF\n");
			break;

		case 'e':
			Serial.print("\nReceived E command!\n");
			digitalWrite(YELLOW, LOW);
			client.write("YELLOW LED: OFF\n");
			break;

		case 'f':
			Serial.print("\nReceived F command!\n");
			digitalWrite(GREEN, LOW);
			server.write("GREEN LED: OFF\n");
			break;

		case 'g':
			Serial.print("\nReceived G command!\n");
			status_red = digitalRead(RED);

			if(status_red == HIGH)
				client.write("STATUS RED LED: ON\n");
			else
				client.write("STATUS RED LED: OFF\n");
			break;

		case 'h':
			Serial.print("\nReceived H command!\n");
			status_yellow = digitalRead(YELLOW);

			if(status_yellow == HIGH)
				client.write("STATUS YELLOW LED: ON\n");
			else
				client.write("STATUS YELLOW LED: OFF\n");
			break;

		case 'i':
			Serial.print("\nReceived I command!\n");
			status_green = digitalRead(GREEN);

			if(status_green == HIGH)
				client.write("STATUS GREEN LED: ON\n");
			else
				client.write("STATUS GREEN LED: OFF\n");
			break;

		case '\n':
			break;

		case '\r':
			break;

		default:
			Serial.print("\nINVALID COMMAND!\n");
			client.write("\nINVALID COMMAND!\n");
			break;  
	} 
}

void printIPAddress()
{
	lcd.setCursor(0, 0);
	lcd.print("IP Adress:   ");
	lcd.setCursor(0, 1);
	lcd.print(Ethernet.localIP());

	Serial.print("My IP address: ");
	Serial.println(Ethernet.localIP());
}

