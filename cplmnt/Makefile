CC=gcc

CFLAGS = \
	--std=c99 \
	-Wall

LDFLAGS = 
#\
#	-Wl,-v \
#	-T data_safram.ld

OBJS = 
		
clean:
	$(RM) *.o
	$(RM) th_safram_cplmnt
	
th_safram_cplmnt: th_safram_cplmnt.c
	$(CC) $(CFLAGS) $(OBJS) -o th_safram_cplmnt th_safram_cplmnt.c $(LDFLAGS)