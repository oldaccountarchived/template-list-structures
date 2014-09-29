tests:
	c++ -g -c SSLL.cpp 
	c++ -g -c PSLL.cpp 	
	c++ -g -c SDAL.cpp 
	c++ -g -c CDAL.cpp 
	c++ -g -c tests.cpp
	c++ -g -o tests SSLL.o PSLL.o SDAL.o CDAL.o tests.o 

clean:
	rm -rf *.o *.dSYM a.out tests
