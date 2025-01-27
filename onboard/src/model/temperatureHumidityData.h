
class TemperatureHumidityData {
public:
    // Temperature in Celsius
    float temperature;
    float temperatureFahrenheit;

    // Humidity in percentage
    float humidity;

    // Sample rate & duration
    float sampleRateMillis;
    float sampleDurationMillis;

    // Sensor fix age
    int sensorFixAgeMillis;
}
