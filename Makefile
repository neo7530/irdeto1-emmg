VERSION = 0.02
CFLAGS  = -Wall -O2 # -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS = -lm
OUT = $(shell uname -m)

CC      = /usr/bin/g++




OBJ = linux_emmg.o irdeto_core.o parser.o 

all: $(OBJ)
	$(CC) $(CFLAGS) -o irdeto-emmg.$(OUT) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.$(OUT)