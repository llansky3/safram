CC=gcc

CFLAGS = --std=c99 \
	-Wall

LDFLAGS = -Wl,-v \
	-T data_safram.ld

OBJS = 
			
th_safram_cplmnt: th_safram_cplmnt.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o th_safram_cplmnt th_safram_cplmnt.c $(LDFLAGS)

clean:
	$(RM) *.o
	$(RM) th_safram_cplmnt	