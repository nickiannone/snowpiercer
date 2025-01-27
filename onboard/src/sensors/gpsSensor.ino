// See: https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/BasicExample/BasicExample.ino
#include <TinyGPSPlus.h>
#include "../model/gpsData.h"

class GPSSensor {
private:
    TinyGPSPlus gps;
    SoftwareSerial ss;
    int rxPin;
    int txPin;
    uint32_t baudRate;

    void parseGPSData(TinyGPSPlus gps, GPSData* data) {
        if (gps.location.isValid() && gps.location.isUpdated()) {
            data->latitude = gps.location.lat();
            data->longitude = gps.location.lng();
            data->locationFixAge = gps.location.age();
        }
        if (gps.date.isValid() && gps.date.isUpdated()) {
            data->date = String(gps.date.value());
            data->dateFixAge = gps.date.age();
        }
        if (gps.time.isValid() && gps.time.isUpdated()) {
            data->time = String(gps.time.value());
            data->timeFixAge = gps.time.age();
        }
        if (gps.speed.isValid() && gps.speed.isUpdated()) {
            data->speedRaw = gps.speed.raw();
            data->speedMph = gps.speed.mph();
            data->speedFixAge = gps.speed.age();
        }
        if (gps.course.isValid() && gps.course.isUpdated()) {
            data->courseRaw = gps.course.raw();
            data->courseDeg = gps.course.deg();
            data->courseFixAge = gps.course.age();
        }
        if (gps.altitude.isValid() && gps.altitude.isUpdated()) {
            data->altitudeRaw = gps.altitude.raw();
            data->altitudeFeet = gps.altitude.feet();
            data->altitudeFixAge = gps.altitude.age();
        }
        if (gps.satellites.isValid() && gps.satellites.isUpdated()) {
            data->satellites = gps.satellites.value();
            data->satelliteFixAge = gps.satellites.age();
        }
        if (gps.hdop.isValid() && gps.hdop.isUpdated()) {
            data->hdopRaw = gps.hdop.raw();
            data->hdop = gps.hdop.hdop();
            data->hdopFixAge = gps.hdop.age();
        }
    }

public:
    GPSSensor(int rxPin, int txPin, uint32_t baudRate) {
        this->rxPin = rxPin;
        this->txPin = txPin;
        this->baudRate = baudRate;
        this->ss = SoftwareSerial(rxPin, txPin);
        this->ss.begin(baudRate);
        this->gps = TinyGPSPlus();
    }

    GPSData* read() {
        // TODO: Add sampling delay like the DHT sensor implementation!
        GPSData* data = new GPSData();
        int startMillis = millis();
        while (this->ss.available() > 0) {
            if (millis() - startMillis > 1000 && this->gps.charsProcessed() < 10) {
                Serial.println("GPS read timed out");
                break;
            }
            if (this->gps.encode(this->ss.read())) {
                // We've read the whole payload successfully!
                GPSData* data = new GPSData();
                parseGPSData(this->gps, data);
                return data;
            }
        }
        // Reset the GPS object if we didn't read anything
        this->gps = TinyGPSPlus();
        return NULL;
    }
}
