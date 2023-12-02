@echo off

echo "Construindo o container"
docker build -t payment_system .

echo "Executando o app"
docker run -it --name=payment_system payment_system

docker wait payment_system

clear

echo "App finalizado, salvando banco de dados"

docker cp payment_system:/app/includes/server/database ./includes/server/
docker cp payment_system:/app/includes/client/database ./includes/client/

docker rm payment_system