OUT = kmeans 
CXX = g++ 
CXXFLAGS = -Wall -g
OBJS = main.o k_means.o
LIBS = -lopencv_highgui -lopencv_core -lopencv_contrib -lopencv_imgproc -lopencv_legacy 


kmeans:$(OBJS)
	$(CXX) -o $(OUT) $(OBJS) $(LIBS)

main.o:main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

k_means.o:k_means.h k_means.cpp
	$(CXX) -c $(CXXFLAGS) k_means.cpp

.PHONY:clean

clean:
	rm -f $(OBJS)
