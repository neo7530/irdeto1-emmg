#!/bin/bash
g++ -Wall linux_emmg.cpp -o irdeto-emmg.x86
arm-linux-gnueabi-g++ -Wall linux_emmg.cpp -o irdeto-emmg.arm
arm-linux-gnueabihf-g++ -Wall linux_emmg.cpp -o irdeto-emmg.armhf
sh4-linux-gnu-g++ -Wall linux_emmg.cpp -o irdeto-emmg.sh4
mipsel-linux-gnu-g++ -Wall linux_emmg.cpp -o irdeto-emmg.mipsel
mips-linux-gnu-g++ -Wall linux_emmg.cpp -o irdeto-emmg.mips
powerpc-linux-gnu-g++ -Wall linux_emmg.cpp -o irdeto-emmg.ppc
powerpc-linux-gnuspe-g++  -Wall linux_emmg.cpp -o irdeto-emmg.ppcspe
aarch64-linux-gnu-g++  -Wall linux_emmg.cpp -o irdeto-emmg.arm64

