echo Construindo o container
docker build -t payment_system .

echo Executando o app
docker run -it payment_system