docker-machine create -d virtualbox Char
eval $(docker-machine env Char)
docker-machine stop Char
cp -R ~/.docker "/tmp/"$USER""_docker/""
rm -rf ~/.docker
ln -s "/tmp/"$USER""_docker/"" .docker
docker-machine start Char
eval $(docker-machine env Char)