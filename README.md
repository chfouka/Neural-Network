
#### Compilation
	
	mkdir build
	cd build
	cmake ..
	make

### Network simulator:
	
You can use the simulator to run the NN
	
	./simulator --help
	
this prints the simulator usage. 
Warning: not all combinations have a sense.

### Example :

	./simulator -i 6 -o 2 -d ../../item/LOC/trainLoc -z 1 -n ../../item/LOC/normvaluesLoc  -E 0 -e 80000 -v 1 -u 10 -S 0.04 -L 0.005 -a 0.00 -l 0.00
	
this simulates the NN using the dataset in ../../item/LOC/trainLoc. With ( -z 1 ) we require the normalization of the dataset given 
the range of values in ../../item/LOC/normvaluesLoc. With (-u 10) we specify 10 units for the NN hidden layer. With (-E 0) we 			disable the early stopping criterion. With (-e 80000) we specify the number of epochs for the learning. With (-v 1) we choose the simple validation instead of a crossvalidation.. etc.


