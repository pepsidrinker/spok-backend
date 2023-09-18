FROM nvidia/cuda:12.2.0-devel-ubuntu22.04
RUN apt update
RUN apt install -y nano libmemcached-dev libssl-dev zlib1g-dev mlocate less wget g++ gcc make cmake net-tools libxxhash-dev  valgrind
RUN updatedb