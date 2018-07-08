docker build -t sniffer .
docker run -it -v $(pwd)/../:/home/sniffer/ sniffer
