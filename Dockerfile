FROM ubuntu:latest

WORKDIR app

COPY . .

RUN apt-get update && apt-get install -y build-essential libssl-dev git cmake

RUN git clone https://github.com/catchorg/Catch2.git && cd Catch2 && \
    cmake -Bbuild -H. -DBUILD_TESTING=OFF &&  cmake --build build/ --target install

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release