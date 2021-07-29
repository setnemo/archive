docker volume create my_hosting
docker run -d --restart on-failure --mount type=volume,source=my_hosting,destination=/etc/mysql --env MYSQL_DATABASE="my_sqldb" --env MYSQL_ROOT_PASSWORD=classic42 --name for_hosting mysql
docker run -d -p 1111:80 --link for_hosting:mysql --name lair wordpress
