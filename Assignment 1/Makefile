all: exec a0c a1c b0c b1c

exec:
	cc graphics.c  -o ex

a0c:
	./ex 0 icosa20.cen > 1a0.svg

a1c:
	./ex 1 icosa20.cen > 1a1.svg

b0c:
	./ex 0 bunny64.cen > 1b0.svg

b1c:
	./ex 1 bunny64.cen > 1b1.svg

reset:
	reset

rm:
	rm ex 1a0.svg 1a1.svg 1b0.svg 1b1.svg

clean: rm