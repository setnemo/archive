FROM debian

RUN apt-get update -y && apt-get upgrade -y && apt-get install clang -y 
RUN apt-get install binutils -y && apt-get install git -y 
RUN apt-get install vim -y && apt-get install make -y 
RUN apt-get install gcc -y 
RUN apt-get install libpcap0.8-dev -y 

RUN mkdir -p /home/alldata/
WORKDIR /home/alldata/
CMD /bin/bash

