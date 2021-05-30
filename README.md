# chungus-cpuminer

Chunguscoin CPU miner using Equihash

*Forked from kost/nheqminer*

# Features

Platforms:
- Linux
- Mac OS X (testing needed)
- Windows (testing needed)

# Usage

### pool
`chungusminer -l pool.org:3333 -u addr.worker -p x`

## Production usage

Basic watchdog:
`while true; do chungusminer -l pool.org:3333 -u addr.worker -p x; echo "sleep & restart"; sleep 30; done`

# Building

## Linux cmake **recommended** (Tested on Arch Linux):
You should have **CMake** installed (2.8 minimal version), boost (install from the repositories or download boost manually build and install it manually), download the sources manually or via git. 
Under Ubuntu open a terminal and run the following commands:
  - `sudo apt-get install cmake build-essential libboost-all-dev`
  - `git clone --recursive https://github.com/kost/nheqminer.git`
  - `cd nheqminer/nheqminer`
  - `mkdir build`
  - `cd build`
  - `cmake ..`
  - `make`

## Windows cmake **recommended** (Tested on Arch Linux):
You should have **CMake** installed (2.8 minimal version), boost (install from the repositories or download boost manually build and install it manually), download the sources manually or via git. 
Under Ubuntu open a terminal and run the following commands:
  - `sudo apt install mingw64-winpthreads-static mingw64-boost-static cmake make git`
  - `git clone https://github.com/kost/nheqminer.git`
  - `cd nheqminer/nheqminer`
  - `mkdir build`
  - `cd build`
  - `cmake -DSTATIC_BUILD=1 -DMARCH="-m64" ..`
  - `make`

## Full static Linux cmake (Tested on Arch Linux):
You should have **CMake** installed (2.8 minimal version), boost (install from the repositories or download boost manually build and install it manually), download the sources manually or via git. 
Under Alpine open a terminal and run the following commands:
  - `sudo apk add --update git cmake make gcc g++ libc-dev boost-dev`
  - `git clone --recursive https://github.com/kost/nheqminer.git`
  - `cd nheqminer/nheqminer`
  - `mkdir build`
  - `cd build`
  - `cmake -DSTATIC_BUILD=1 -DMARCH="-m64" ..`
  - `make`


## Mac OS X  (Tromp and Xenoncat):
You need to have git, cmake, make and Mac OS X Developer stuff (compiler, etc).
Under Mac open a terminal and run the following commands:
  - `git clone --recursive https://github.com/kost/nheqminer.git`
  - `cd nheqminer/nheqminer`
  - `mkdir build`
  - `cd build`
  - `cmake -DSTATIC_BUILD=1 ..`
  - `make`

## Windows (Microsoft Visual Studio - needs tweaking):
Windows builds made by us are available here: https://github.com/kost/nheqminer/releases

Download and install:
- Visual Studio 2013 Community: https://www.visualstudio.com/en-us/news/releasenotes/vs2013-community-vs
- Visual C++ Compiler November 2013 CTP: https://www.microsoft.com/en-us/download/details.aspx?id=41151

Open **chungusminer.sln** under **miner/chungusminer.sln** and build.


# Run instructions:

If run without parameters, miner will start mining with 75% of available virtual cores on flypool with developers account using best engine. Feel free to donate that way. Use parameter -h to learn about available parameters:

```
Parameters:
        -h              Print this help and quit
        -l [location]   Stratum server:port
        -u [username]   Username (pool worker)
        -x [enginenum]  Engine (-1=auto,0=tromp,1=AVX1,2=AVX2)
        -p [password]   Password (default: x)
        -t [num_thrds]  Number of threads (default: number of sys cores)
        -d [level]      Debug print level (0 = print all, 5 = fatal only, default: 2)
        -b [hashes]     Run in benchmark mode (default: 100 hashes)
        -a [port]       Local API port (default: 0 = do not bind)
```

<i>Note: if you have a 4-core CPU with hyper threading enabled (total 8 threads) it is best to run with only 6 threads (experimental benchmarks shows that best results are achieved with 75% threads utilized)</i>

# Acknowledgments and credits

## Acknowledgements

This miner is based on Equihash Miner for NiceHash
Thanks to Zcash developers for providing most of the code
Special thanks to tromp for providing optimized CPU equihash solver

## Credits

Author of the fork: Kost
Author of Chunguscoin and this miner: Shafil Alam
