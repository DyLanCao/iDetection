
CXXFLAGS:= $(shell pkg-config --cflags opencv)

LDLIBS:= $(shell pkg-config --libs opencv)




#test: main.o direc.o
test: train_HOG.o 
	g++ -o test train_HOG.o $(CXXFLAGS) $(LDLIBS)

train_HOG.o: train_HOG.cpp 
	g++ -c train_HOG.cpp   $(CXXFLAGS) 


#direc.o: direc.cpp direc.h
#	g++ -c direc.cpp  $(CXXFLAGS)


clean: 
	rm -f *.o
