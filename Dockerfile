FROM nvidia/cuda:12.2.0-devel-ubuntu22.04
RUN apt update && apt install -y nano libmemcached-dev libssl-dev zlib1g-dev mlocate less wget g++ gcc make cmake net-tools libxxhash-dev  valgrind
RUN updatedb
RUN mkdir -p /etc/personal && ln -s /workspace /etc/personal/spok-backend