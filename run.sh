docker build -t sniffer .
docker run -it -v $(pwd)/all_data/:/home/alldata/ sniffer
