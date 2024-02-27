FROM ubuntu:22.04

RUN apt-get update && apt-get -y upgrade && \
    apt-get install -y  \
      build-essential \
      cmake \
      perl \
      git \
      ninja-build

RUN apt-get -y install libgl1-mesa-dev \
                       libglu1-mesa-dev

RUN git clone -b v6.2.4 https://code.qt.io/qt/qt5.git qt_6_2_4 && \
    cd qt_6_2_4 && \
    perl init-repository --module-subset=qtbase,qtsvg,qtmultimedia,qtshadertools && \
    \
    cmake . -GNinja && \
    \
    cmake --build . && \
    cmake --install . \


