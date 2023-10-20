FROM ubuntu:20.04


### To make the apt quiet
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update

### installing usefull tools
RUN apt install -y wget
RUN apt install -y curl 
RUN apt install -y gnupg
RUN apt install -y git



### installing gstreamer from 
### https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c#install-gstreamer-on-ubuntu-or-debian

RUN apt-get install -y libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly gstreamer1.0-libav \ 
    gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa \ 
    gstreamer1.0-gl gstreamer1.0-gtk3 \ 
    gstreamer1.0-qt5 gstreamer1.0-pulseaudio


### installing nvidia cuda

RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
RUN mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
RUN wget https://developer.download.nvidia.com/compute/cuda/11.4.0/local_installers/cuda-repo-ubuntu2004-11-4-local_11.4.0-470.42.01-1_amd64.deb
RUN dpkg -i cuda-repo-ubuntu2004-11-4-local_11.4.0-470.42.01-1_amd64.deb
RUN apt-key add /var/cuda-repo-ubuntu2004-11-4-local/7fa2af80.pub
RUN apt-get update
RUN apt-get -y install cuda

### Installing nvidia-container-toolkit

RUN curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | \ 
    gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
    && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
    sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
    tee /etc/apt/sources.list.d/nvidia-container-toolkit.list \
    && apt update

RUN apt install -y nvidia-container-toolkit

### Installing tensorRT

COPY ./nv-tensorrt-repo-ubuntu2004-cuda11.4-trt8.2.0.6-ea-20210922_1-1_amd64.deb  /tmp

RUN dpkg -i /tmp/nv-tensorrt-repo-ubuntu2004-cuda11.4-trt8.2.0.6-ea-20210922_1-1_amd64.deb && \
    apt-get update && \
    apt-get install -y tensorrt 

### installing cpp stuff
RUN apt install -y g++ cmake pkg-config

###installing opencv
RUN apt install libopencv-dev

### Installing yolov5_tensorRT lib (from https://github.com/noahmr/yolov5-tensorrt)
WORKDIR /tmp

RUN git clone https://github.com/noahmr/yolov5-tensorrt.git
RUN cd yolov5-tensorrt
RUN mkdir build && cd build
RUN cmake /tmp/yolov5-tensorrt -DBUILD_PYTHON=OFF
RUN make && make install

### Going to the app dir
WORKDIR /app_code

RUN rm -rf /var/lib/apt/lists/*