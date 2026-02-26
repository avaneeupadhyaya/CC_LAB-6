FROM ubuntu:22.04

RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY app.cpp .

RUN g++ app.cpp -o app

EXPOSE 9090

CMD ["./app"]
