
class DataFrame {
private:
    time_t timestamp;
    TemperatureHumidityData* temperatureHumidityData;
    GPSData* gpsData;

public:
    DataFrame(time_t timestamp, TemperatureHumidityData* temperatureHumidityData, GPSData* gpsData) {
        this->timestamp = timestamp;
        this->temperatureHumidityData = temperatureHumidityData;
        this->gpsData = gpsData;
    }

    byte[] getBytes() {
        // TODO: Convert to a JSON payload!
        
    }
}
