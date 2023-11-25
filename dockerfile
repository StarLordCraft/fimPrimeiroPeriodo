FROM alpine

RUN apk update && apk add cmake ncurses gcc musl-dev

COPY . /app

WORKDIR /app

RUN mkdir build && cd build && cmake .. && make

CMD [ "./build/Payment_System"]