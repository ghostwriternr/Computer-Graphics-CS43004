all: exec 4a 4bb 4bi

exec:
	g++ -std=c++11 ass4a.cpp -o exa
	g++ -std=c++11 ass4b.cpp -o exb

4a:
	./exa icosa20.obj icosa20_poly_inter.obj icosa20_poly.obj
	./exa bunny64.obj bunny64_poly_inter.obj bunny64_poly.obj

4bi:
	$(info Enter space seperated co-ordinates for camera position (x,y,z))
	./exb icosa20_poly.obj icosa20_polyfront_inter.obj icosa20_polyfront.obj

4bb:
	$(info Enter space seperated co-ordinates for camera position (x,y,z))
	./exb bunny64_poly.obj bunny64_polyfront_inter.obj bunny64_polyfront.obj

rm:
	rm exa exb icosa20_poly.obj icosa20_polyfront.obj bunny64_poly.obj bunny64_polyfront.obj icosa20_poly_inter.obj icosa20_polyfront_inter.obj bunny64_poly_inter.obj bunny64_polyfront_inter.obj

clean: rm