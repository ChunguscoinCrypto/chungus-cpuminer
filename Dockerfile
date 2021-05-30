FROM alpine

RUN apk add --no-cache --virtual=build-dependencies git cmake make gcc g++ libc-dev boost-dev && \
    git clone https://github.com/ChunguscoinCrypto/chungus-cpuminer && \
    cd /chungus-cpuminer/miner && \
    mkdir build && \
    cd /chungus-cpuminer/miner/build && \
    cmake -DSTATIC_BUILD=1 -DMARCH="-m64" .. && \
    make && \
    apk del --purge build-dependencies
    
ENTRYPOINT ["/chungus-cpuminer/chungus-cpuminer/build/chungusminer"]
