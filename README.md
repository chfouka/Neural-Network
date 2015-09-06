Precondition {  boost and cmake installed }

To compile the project:


cd src
		mkdir build
		cd build
		cmake ..
		make

#### to run the NN use the simulator. For the usage type:

	./simulator --help
	
	this visualizes all the option for the NN. Warning: not all combination are meaningful.

#### Example of usage:

	./simulator -i 6 -o 2 -d ../../item/LOC/trainLoc -z 1 -n ../../item/LOC/normvaluesLoc  -E 0 -e 80000 -v 1 -u 10 -S 0.04 -L 0.005 -a 0.00 -l 0.00
	
	this simulates the NN using the dataset in ../../item/LOC/trainLoc. With ( -z 1 ) we require the normalization of the dataset given 
	the range of values in ../../item/LOC/normvaluesLoc. With (-u 10) we specify 10 units for the NN hidden layer. With (-E 0) we disable
	the early stopping criterion. With (-e 80000) we specify the number of epochs for the learning. With (-v 1) we choose the simple 
	validation instead of a crossvalidation.. etc.

### if you want the report mailto: hind.chf@gmail.com 
### of any other info mailto: hind.chf@gmail.com