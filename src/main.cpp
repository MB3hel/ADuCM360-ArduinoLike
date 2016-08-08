#include "SpiLib.h"
#include "DioLib.h"
#include "ArduinoLike.h"
#include "ArduinoEthernet/Ethernet.h"
#include "ArduinoEthernet/EthernetUdp.h"

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 129);

int port = 8888;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char  ReplyBuffer[] = "acknowledged";

EthernetUDP udp;

int main(){

	serial.begin(9600, PIN67); //Can't use PIN12 with SPI

	if(Ethernet.begin(mac) == 0){

		serial.println("Failed to start!");
		serial.println("[STOP]");
		while(1);

	}

	udp.begin(port);

	serial.print("IP: ");
	serial.println(ipToString(Ethernet.localIP()));

	while(1){

		int packetsize = udp.parsePacket();
		if(packetsize){

			serial.print("Recieved packer of size ");
			serial.println(packetsize);
			serial.print("From ");
			serial.print(ipToString(udp.remoteIP()));
			serial.print(", port ");
			serial.println(udp.remotePort());

			udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
			serial.println("Contents:");
			serial.println(packetBuffer);

			udp.beginPacket(udp.remoteIP(), udp.remotePort());
			udp.write(ReplyBuffer);
			udp.endPacket();

		}

		delay(10);

	}

}
