
PROGRAMS = layout layout-row layout-column mm-blas mm-ijk
INCLUDES = -I.

CFLAGS = -O3 -Wall $(INCLUDES)

all: $(PROGRAMS) layout.s


%.s:%.c
	$(CC) -S $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) -c $<

layout: layout.o
	$(CC) $(CFLAGS) -o $@ $<

layout-column: layout-column.o nop.o
	$(CC) $(CFLAGS) -o layout-column $< nop.o

layout-row: layout-row.o nop.o
	$(CC) $(CFLAGS) -o layout-row $< nop.o

mm-ijk: mm-ijk.o
	$(CC) $(CFLAGS) -o mm-ijk $< -lm

mm-blas: mm-blas.o
	$(CC) $(CFLAGS) -m32 -std=gn99 -o mm-blas $< -llapacke -lblas -lm

clean:
	rm -f $(PROGRAMS) *.o core a.out data layout.s
