tests: tests.o SSLL.o PSLL.o SDAL.o CDAL.o
	c++ -g -o tests SSLL.cpp PSLL.cpp SDAL.cpp CDAL.cpp tests.cpp 
clean:
	rm -rf *.o *.dSYM a.out tests
