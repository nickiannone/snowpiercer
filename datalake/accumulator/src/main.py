from pyspark.sql import SparkSession

def main():
    # Initialize Spark session
    spark = SparkSession.builder \
        .appName("Accumulator Example") \
        .getOrCreate()

    # Load data
    data = spark.read.csv("path/to/your/data.csv", header=True, inferSchema=True)

    # Process data (example transformation)
    processed_data = data.groupBy("column_name").count()

    # Show results
    processed_data.show()

    # Stop the Spark session
    spark.stop()

if __name__ == "__main__":
    main()