
#include <DHT.h>
#include "../model/temperatureHumidityData.h"

class TemperatureHumiditySensor {
private:
    DHT dhtSensor;
    int pin;

    // DHT11 sensor readings may be up to 2 seconds old, so we need to account for that
    int sensorFixAgeMillis;

    // We also control sampling and track how long a read was supposed to last!
    float sampleRateMillis;

    // Hidden stuff
    float lastSampleMillis = 0;
    float lastDurationMillis = 0;
    float averageSampleDurationMillis = 0;

    void parseTemperatureHumidityData(TemperatureHumidityData* data) {
        if (data) {
            data->temperature = this->dhtSensor->temperature;
            data->temperatureFixAge = this->dhtSensor->temperatureFixAge;
            data->humidity = this->dhtSensor->humidity;
            data->humidityFixAge = this->dhtSensor->humidityFixAge;
        }
    }

public:
    TemperatureHumiditySensor(int pin, int sensorFixAgeMillis = 2000, float sampleRateMillis = 2000, float readDurationMillis = 250) {
        this->pin = pin;
        this->sensorFixAgeMillis = sensorFixAgeMillis;
        this->sampleRateMillis = sampleRateMillis;

    }

    void setup() {
        pinMode(this->pin, INPUT);
    }

    float getAverageSampleDurationMillis() {
        return this->averageSampleDurationMillis;
    }

    TemperatureHumidityData* read() {
        float startMillis = millis();

        // Check if we should skip this read!
        if (this->lastSampleMillis != 0) {
            float timeSinceLastSample = startMillis - this->lastSampleMillis;
            if (timeSinceLastSample < this->sampleRateMillis) {
                Serial.println("Temperature and humidity sensor read skipped"); // TODO: Remove!
                return NULL;
            }
        }

        // Perform the read!
        if (!this->dhtSensor.read11(this->pin)) {
            Serial.println("Failed to read from DHT sensor");
            return NULL;
        }

        // Capture sample duration in millis
        float endMillis = millis();
        float sampleDuration = endMillis - startMillis;

        // Track the last sample time and duration
        this->lastSampleMillis = startMillis;
        this->lastDurationMillis = sampleDuration;

        // Capture a running average of the sample duration (2 samples)
        if (this->averageSampleDurationMillis == 0) {
            this->averageSampleDurationMillis = sampleDuration;
        } else {
            this->averageSampleDurationMillis = (this->averageSampleDurationMillis + sampleDuration) / 2;
        }

        // Convert everything to a data object and return it
        TemperatureHumidityData* data = new TemperatureHumidityData(sampleDuration);
        parseTemperatureHumidityData(data);
        return data;
    }
}
