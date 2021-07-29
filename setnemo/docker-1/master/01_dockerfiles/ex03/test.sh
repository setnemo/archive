docker build -t test01ex03 .
docker run -v /var/www:/var/www -p 3000:3000 -t test01ex03