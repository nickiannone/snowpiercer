
#include <SPI.h>
#include <Ethernet.h>
#include <TimeLib.h>
#include "../model/dataFrame.h"

class TransmitService {
private:
    EthernetClient client;
    byte[] mac;
    int port;
    IPAddress serverAddr;

    // https://www.circuitbasics.com/using-an-arduino-ethernet-shield-for-timekeeping/
    EthernetUDP ntpUDP; // UDP instance to let us send and receive NTP packets over UDP
    IPAddress ntpServerAddr = IPAddress(129, 6, 15, 28); // time.nist.gov
    uint16_t localNtpPort = 8888;
    time_t prevNtpTime = 0;
    byte ntpPacketBuffer[48];

    void sendNTPRequest(IPAddress& address) {
        // set all bytes in the buffer to 0
        memset(this->ntpPacketBuffer, 0, sizeof(this->ntpPacketBuffer));

        // Initialize values needed to form NTP request packet
        this->ntpPacketBuffer[0] = 0b11100011;   // LI, Version, Mode
        this->ntpPacketBuffer[1] = 0;     // Stratum, or type of clock
        this->ntpPacketBuffer[2] = 6;     // Polling Interval
        this->ntpPacketBuffer[3] = 0xEC;  // Peer Clock Precision

        // 8 bytes of zero for Root Delay & Root Dispersion
        this->ntpPacketBuffer[12]  = 49;
        this->ntpPacketBuffer[13]  = 0x4E;
        this->ntpPacketBuffer[14]  = 49;
        this->ntpPacketBuffer[15]  = 52;

        // Send the packet
        this->ntpUDP.beginPacket(this->ntpServerAddr, 123);
        this->ntpUDP.write(this->ntpPacketBuffer, sizeof(this->ntpPacketBuffer));
        this->ntpUDP.endPacket();
    }

public:
    TransmitService(byte[] mac, IPAddress serverAddr, int port) {
        this->mac = mac;
        this->serverAddr = serverAddr;
        this->port = port;
    }

    void setup() {        
        Serial.println("Initializing Ethernet connection...");
        while (Ethernet.begin(mac) == 0) {
            Serial.println("Failed to configure Ethernet using DHCP");
            delay(1000);
        }
        Serial.println("Ethernet configured via DHCP");
        Serial.print("Ethernet Shield IP address: ");
        Serial.println(Ethernet.localIP());

        // Set up NTP
        this->ntpUDP.begin(this->localNtpPort);
        setSyncProvider(this->getNtpTime); // Set the sync provider to our function

        // TODO: Can we init the connection here and pool it? How do we handle reconnects?
        this->client = EthernetClient();
    }

    bool transmit(DataFrame* dataFrame) {
        if (!this->client.connected() && !this->client.connect(serverAddr, port)) {
            Serial.println("Failed to connect to server");
            return false;
        }
        this->client.write(dataFrame->getBytes());
        this->client.stop();
        return true;
    }

    time_t getNtpTime() {
        while (this->ntpUDP.parsePacket() > 0) ; // discard any previously received packets

        Serial.println("Transmitting NTP request");
        sendNTPRequest(this->ntpServerAddr);

        uint32_t beginWait = millis();
        while (millis() - beginWait < 1500) {
            int size = this->ntpUDP.parsePacket();
            if (size >= 48) {
                Serial.println("Received NTP response");
                this->ntpUDP.read(this->ntpPacketBuffer, 48); // read the packet into the buffer
                unsigned long secsSince1900;
                // convert four bytes starting at location 40 to a long integer
                secsSince1900 = (unsigned long) this->ntpPacketBuffer[40] << 24;
                secsSince1900 |= (unsigned long) this->ntpPacketBuffer[41] << 16;
                secsSince1900 |= (unsigned long) this->ntpPacketBuffer[42] << 8;
                secsSince1900 |= (unsigned long) this->ntpPacketBuffer[43];
                return secsSince1900 - 2208988800UL; // return seconds since 1970
            }
        }

        Serial.println("Error: no NTP response");
        return 0;
    }
}