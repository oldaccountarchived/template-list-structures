all: SSLL.hpp PSLL.hpp SDAL.hpp CDAL.hpp 
	c++ -g -c SSLL.cpp PSLL.cpp SDAL.cpp CDAL.cpp

test: all
	c++ -g -o tests tests.cpp && ./tests 

clean:
	rm -rf *.o *.dSYM a.out tests
