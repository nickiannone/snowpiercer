
class GPSData {
public:
    // Latitude and longitude are in decimal degrees
    float latitude;
    float longitude;
    int locationFixAge;

    // Date is in a standard string format
    String date;
    int dateFixAge;

    // Time is in a standard string format
    String time;
    int timeFixAge;

    // Speed is in MPH
    float speedRaw;
    float speedMph;
    int speedFixAge;

    // Course is in degrees
    float courseRaw;
    float courseDeg;
    int courseFixAge;

    // Altitude is in feet
    float altitudeRaw;
    float altitudeFeet;
    int altitudeFixAge;

    // Number of satellites in view
    int satellites;
    int satelliteFixAge;

    // HDOP = Horizontal Dilution of Precision
    // <1 is ideal, 1-2 is excellent, 2-5 is good, 5-10 is moderate, 10-20 is fair, 20-50 is poor, >50 is bad
    float hdopRaw;
    float hdop;
    int hdopFixAge;
}
