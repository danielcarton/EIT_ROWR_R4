FROM ros:melodic

ARG distro=melodic
ENV DEBIAN_FRONTEND=noninteractive

# Change the default shell to Bash
SHELL [ "/bin/bash" , "-c" ]
 
 # Create ghost_trawler user
RUN useradd -ms /bin/bash \
    --home /home/ghost_trawler  ghost_trawler
RUN echo "ghost_trawler:ghost_trawler" | chpasswd
RUN usermod -aG sudo ghost_trawler

# Install Git
RUN apt-get update && apt-get install -y git

RUN apt update && \
    apt install -y \
    ros-$distro-roslint \
    ros-$distro-move-base-msgs \
    ros-$distro-tf \
    ros-$distro-tf2 \
    ros-$distro-eigen-conversions \
    libeigen3-dev \
    ros-$distro-imu-tools \
    libeigen3-dev \
    libglfw3-dev \
    libglew-dev \
    libjsoncpp-dev \
    libtclap-dev \
    python3-catkin-tools \
    python3-vcstool \
    net-tools \     
    tcpdump \
    python-pip \
    software-properties-common

RUN pip install \
    pyserial \
    rospkg

# Copy workspace into image
COPY ./ /ghost_trawler_ws/src/EIT_ROWR_R4

# ROS Wrapper for Mynt Eye
# RUN cd /ghost_trawler_ws/src && sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
# RUN sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
# RUN sudo apt update
RUN sudo add-apt-repository ppa:slightech/mynt-eye-s-sdk
RUN sudo apt-get update
RUN sudo apt-get install mynt-eye-s-sdk

RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN source ~/.bashrc
# RUN cd /ghost_trawler_ws && catkin build



# Install ros wrapper for ZED camera
# RUN source /opt/ros/noetic/setup.bash
# RUN cd /ghost_trawler_ws/src
# RUN git clone --recursive https://github.com/stereolabs/zed-ros-wrapper.git
# RUN cd /ghost_trawler_ws && rosdep install --from-paths src --ignore-src -r -y
# RUN cd /ghost_trawler_ws &&  catkin_make -DCMAKE_BUILD_TYPE=Release
# RUN source /dhost_trawler_ws && /devel/setup.bash

# Create a Catkin workspace 
# RUN source /opt/ros/noetic/setup.bash \
#  && mkdir -p /turtlebot3_ws/src \
#  && cd /turtlebot3_ws/src \
#  && catkin_init_workspace \
#  && git clone -b noetic-devel https://github.com/ROBOTIS-GIT/turtlebot3.git \
#  && git clone -b noetic-devel https://github.com/ROBOTIS-GIT/turtlebot3_msgs.git \
#  && git clone -b noetic-devel https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
# RUN echo "export TURTLEBOT3_MODEL=waffle_pi" >> ~/.bashrc
 
# Build the Catkin workspace and ensure it's sourced
# RUN source /opt/ros/noetic/setup.bash \
#  && cd turtlebot3_ws \
#  && catkin_make
# RUN echo "source /turtlebot3_ws/devel/setup.bash" >> ~/.bashrc
 
# Set the working folder at startup
WORKDIR /ghost_trawler_ws