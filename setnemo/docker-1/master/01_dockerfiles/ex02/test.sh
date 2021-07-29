docker build -t test01ex02 .
docker run -v /var/www:/var/www -p 5000:80 -t test01ex02