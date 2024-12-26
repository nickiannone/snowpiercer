def load_data(source):
    """Load data from the specified source."""
    from pyspark.sql import SparkSession

    spark = SparkSession.builder.appName("DataLoader").getOrCreate()
    data = spark.read.csv(source, header=True, inferSchema=True)
    return data

def process_data(data):
    """Apply transformations to the data."""
    # Example transformation: filter out rows with null values
    processed_data = data.dropna()
    return processed_data