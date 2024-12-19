# Snowpiercer

This application is intended to be able to track snow buildup across all public thoroughfares of a desired municipality, and adjust depths as observed by snowplows for use in tracking and correcting buildup and generating a lake of snow management data. This could be leveraged for training snow management crews, assisting cities or smaller municipalities in tracking problem areas for snow removal, and determining where snow buildup occurs the fastest or where ice hazards are more likely.

Much of the research and implementation behind this is based on the paper "Reaction Time Optimization based on Sensor Data-Driven Simulation for Snow Removal Projects", by Jafari et al. (University of Alberta, 2018). Using GPS and RWIS data, as well as video feed from the front and back of snowplows, we want to use fuzzy matching and data interpolation to give at least a representative view of an entire city's roads at once, as well as being able to give a live approximation of snowplow response times. While this data will frequently lie, we can model the accumulation of snow and adjust this model based on the map of public roads from Google Maps and using GPS coordinates and Google Maps address data to make it as close as possible and to use live footage analysis and temporal data adjustment to replace inaccurate readings on a more granular level, representing the confidence of the data based on projected drift from the available sampled data.

This README would normally document whatever steps are necessary to get the
application up and running.

Things you may want to cover:

## System Dependencies

TODO

## Configuration

To start the application locally the first time, run:

```
# First-time setup
bundle install
rails db:create
rails db:migrate
# ...

# Starts the app
rails server
```

## Database creation

To create the database, run:

```
rails db:create
```

## Database initialization

To set up the database or perform any missed migrations, run:

```
rails db:migrate
```

## How to run the test suite

To run the test suite for the Rails API service, run:

```
rails test
```

## Application Design

Data Capture
    (army of plows) -> Camera, GPS, Timestamp -> (input processors)

Data Ingestion
    (input processors) -> Depth at location at time -> (data model)

Data Projection
    (Workers adjust the data model over time based on projection)

Data Analysis (ML model?)
    (data model) -> Information about snow depth at time -> (AI model)

Business Logic (Backend)
    (AI model, data model) -> Inference data -> (application, notifications)

User Interface (Frontend)
    (application) -> Depth map & insights -> (User)

## Services (job queues, cache servers, search engines, etc.)

TODO: Finish!

* Database (for tracking data acquisition process, not storing data)
* Application Instance
* Live Data Store/Lake (unsure how we're doing this, something with Spark? DynamoDB?)
* Redis
* Data Ingest Workers/Message Queues
* Elasticsearch
* Data Capture Cameras
* Data Processing Microservices(?)
* Frontend
* Google Maps Plugin
* Frontend (Vue?)

## Deployment instructions

TODO
