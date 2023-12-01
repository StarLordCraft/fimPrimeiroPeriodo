FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake libncurses5-dev gcc g++ make

COPY . /app

WORKDIR /app

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/Payment_System"]