# Network Sniffer (daemon with cli)

Simple network traffic sniffer, writting on C.

## Getting Started

The program is written for the Linux system, tested in Debian 9 and the Docker container with Debian 9. To start - clone project to your computer.

```
git clone https://gitlab.com/omentes/sniffer-c.git
```
```
cd sniffer-c
```

### Installing

If you are a Linux user

```
make
```

If you want to test the program in Docker

```
cd docker-run
chmod +x run.sh
./run.sh
```

## Built With

* [Libpcap](http://www.tcpdump.org/) - a portable C/C++ library for network traffic capture
* [Article](https://www.binarytides.com/packet-sniffer-code-c-libpcap-linux-sockets/) - C Packet Sniffer Code with libpcap and linux sockets By Silver Moon 
```
apt-get install libpcap0.8-dev -y 
```

## Authors

* **Artem Pakhomov** - [omentes](https://gitlab.com/omentes)

## License

This project is licensed under the MIT License
