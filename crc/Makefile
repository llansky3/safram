CC=gcc

CFLAGS = \
	--std=c99 \
	-Wall

LDFLAGS = \
	-Wl,-v \
	-T data_safram.ld

OBJS = \
	safram_crc.o \
	crc8.o

all: clean th_safram_crc th_safram_corruption

th_safram_crc: safram_crc.o crc8.o
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) -o th_safram_crc th_safram_crc.c $(LDFLAGS)
	
safram_crc.o: safram_crc.c
	$(CC) $(CFLAGS) -c safram_crc.c

crc8.o: crc8.c
	$(CC) $(CFLAGS) -c crc8.c	

th_safram_corruption:
	$(CC) $(CFLAGS) -o th_safram_corruption th_safram_corruption.c

clean:
	$(RM) *.o
	$(RM) th_safram_crc 
	$(RM) th_safram_corruption