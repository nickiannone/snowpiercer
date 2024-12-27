# Application Design

Snowpiercer is intended to be a large SaaS application with many moving parts, and this repository will eventually only contain the backend DB, the REST API, and the frontend Vue application. For now, though, we are modeling as much as we can within this repository in the prototype phase.

## Backend

The backend is a Rails application, which serves up dynamic frontend assets, handles user authorization, provides an API for the frontend components, and queries into the database and data lake as needed.

### API

The API mostly serves to provide the frontend instances with authorization and data analysis, which is performed by querying the DB and data lake for information based on requests from the frontend. Things like figuring out which truck last plowed a specific street, and projecting the depth of that section of street at a given time, marking streets as closed, and so forth.

## Frontend

The frontend will be implemented in Vue(?), and will consist of a base Google Maps overlay interface with dialogue windows and side frames containing analytics and operational data about the scene being displayed. A modular design will allow additional live video, communications, and other data feeds to be added and removed from the live interface. A user model and auth will also be necessary for determining whether the user can see the map, perform actions, etc.

## Database

The database will be largely operational and authorizational information for authenticating the data which is acquired and tracking who sent it. Backup procedures, access control, ETL, data lake management, and other optimizations will follow.

## Microservices

We will have several smaller microservices to handle things outside of the scope of the main Rails application.

### Mapmaker

This component pulls in and updates base street data for the 

### Search

We want to have Elasticsearch available on the actual data for analytical purposes, so the actual records can be indexed without the rest of the system taking a performance hit.

### Data Accumulators

We need to have some sort of system for feeding the incoming data into our data lake, checking it for consistency, and processing it for depth and condition information. The accumulators will handle HTTP requests with time-based depth and condition data, as well as streaming video feeds for analysis, process and clean them as needed, and stuff them into the data lake.

### Data Lake

The data lake will be our interface for storing and recalling GPS data, weather condition data, and other information about road conditions over time. Depending on which data lake solution we choose, we will either be storing this information in various smaller databases with a single queryable interface for storing and accessing that data, or one of the various Big Data solutions (ie. Apache Spark/Databricks).

We expect to be able to know or extrapolate the following:

- Time
- Location (street address & GPS)
- Condition data
    - Snow depth
    - Ice accumulation
    - Black ice presence
    - Loss of traction control?
    - Video (forward)
    - Video (backward)
    - Tags
    - Confidence
    - Nearby data points (basis for calculation)

## Data Model

User
Session
Jurisdiction
    Roadway
        Lane
            Span
Truck
GPSPosition
WeatherDataPoint (NWIS?)
GeoTag

## Other Research

Google Maps Overlay:
- Map
- Marker (can animate, use custom icon, etc.)
- Polyline/Polygon (path, stroke color, stroke opacity, stroke weig)
- Circle
- Rectangle
- Info Window
- Custom Overlays

## Original Stories

1. [datalake] Create model for a Truck
2. [datalake] Create model for a Jurisdiction
3. [datalake] Create model for a Roadway
4. [datalake] Create model for a Lane
5. [datalake] Create model for a Span
6. [datalake] Create model for a Video
7. [datalake] Create model for a GPSPosition
8. [datalake] Create model for a WeatherDataPoint (NWIS?)
9. [datalake] Create model for a GeoTag
10. [datalake] Create model for a User
11. [datalake/accumulator] Receive Map information for Jurisdiction from Google Maps
12. [datalake/accumulator] Store Map information into data lake
13. [datalake/accumulator] Receive Weather information for Jurisdiction from Weather.gov (https://api.weather.gov/openapi.json) and store in Data Lake
    https://www.reddit.com/r/learnpython/comments/15zm4pq/best_weather_api/ 
14. [datalake/accumulator] Receive Onboard Conditions for Truck and store in data lake
15. [onboard] Send Onboard Conditions to Accumulator
16. [onboard] Measure some onboard conditions (Temperature?)
17. [onboard] Capture current GPS position
18. [onboard] Request truck registration from API
19. [api] Add Authentication for API requests
20. [api] Add endpoints for Truck registration
21. [api] Add endpoints for Truck start-capture and stop-capture
22. [onboard] Add commands to start and stop data capture
23. 
