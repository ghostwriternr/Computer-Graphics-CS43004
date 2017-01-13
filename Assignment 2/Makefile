all: exec 2a 2b

exec:
	g++ -std=c++11 ass2.cpp -o ex

2a:
	$(info Input desired color in hex format, ex. #abcdef)
	./ex 0 icosa20.cen > 2a.svg

2b:
	$(info Input desired color in hex format, ex. #abcdef)
	./ex 0 bunny64.cen > 2b.svg

rm:
	rm ex 2a.svg 2b.svg

clean: rm