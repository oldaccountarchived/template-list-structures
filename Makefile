all: SSLL.hpp PSLL.hpp SDAL.hpp CDAL.hpp 
	/usr/local/bin/g++-4.9 -std=c++0x -g -c SSLL.cpp PSLL.cpp SDAL.cpp CDAL.cpp

test: all
	/usr/local/bin/g++-4.9 -std=c++0x -g -o tests tests.cpp && ./tests 

clean:
	rm -rf *.o *.dSYM a.out tests
