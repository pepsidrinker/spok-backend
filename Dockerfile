FROM nvidia/cuda:12.2.0-devel-ubuntu22.04
RUN apt update && apt install -y nano libmemcached-dev libssl-dev zlib1g-dev mlocate less wget g++ gcc make cmake net-tools libxxhash-dev valgrind tar
RUN updatedb
RUN mkdir -p /etc/personal && ln -s /workspace /etc/personal/spok-backend

RUN mkdir -p /temp/external
COPY external/* /temp/external

RUN cd /temp/external && tar -xvf komu.tar && cd komu && chmod +x compiler.sh && ./compiler.sh
RUN cd /temp/external && tar -xvf cedruslibani.tar && cd cedruslibani && chmod +x compiler.sh && ./compiler.sh