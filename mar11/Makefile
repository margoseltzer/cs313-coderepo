
PROGRAMS = ptest fdtest fdtest2 forktest threadtest duptest
INCLUDES = -I.

CFLAGS = -O3 -Wall $(INCLUDES)
LDFLAGS = -lpthread

all: $(PROGRAMS)


%.s:%.c
	$(CC) -S $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROGRAMS) *.o core 
