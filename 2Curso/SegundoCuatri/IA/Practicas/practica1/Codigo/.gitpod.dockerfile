FROM gitpod/workspace-full-vnc

RUN sudo apt-get update -q \
    && sudo apt-get install -y freeglut3 freeglut3-dev libjpeg-dev libopenmpi-dev openmpi-bin openmpi-doc libxmu-dev libxi-dev cmake libboost-all-dev \
    && sudo rm -rf /var/lib/apt/lists/*