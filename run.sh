docker build -t sniffer .
docker run -it -v $(pwd)/all_data/:/home/all_data/ sniffer
