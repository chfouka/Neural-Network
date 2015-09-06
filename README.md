
#### Compilation
	
	mkdir build
	cd build
	cmake ..
	make

### Network simulator:
	
You can use the simulator to run the NN
	
	./simulator --help

this prints the simulator usage. 


### Example :

	./simulator -i 6 -o 2 -d ../../item/LOC/trainLoc -z 1 -n ../../item/LOC/normvaluesLoc  -E 0 -e 80000 -v 1 -u 10 -S 0.04 -L 0.005 -a 0.00 -l 0.00
	

this simulates the NN using the dataset in ../../item/LOC/trainLoc.
-z 1: requires the normalization of the dataset given <br/>

-n 1 : gives the range of values in ../../item/LOC/normvaluesLoc for the normalization. <br/>

-u 10: specifies 10 units for the NN hidden layer. <br/>

-E 0: disables the early stopping criterion. <br/>

-e 80000: sets the number of epochs <br/>

-v 1: chooses a simple validation instead of a crossvalidation <br/>
...
...


