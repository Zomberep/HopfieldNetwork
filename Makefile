CFLAGS=-Wall -Wextra -std=c++23
HOP_LIB=hopfieldnetwork.cpp
MAT_LIB=matrix.cpp
IM_LIB=image.cpp


network:
	g++ $(CFLAGS) network.cpp $(HOP_LIB) $(IM_LIB) $(MAT_LIB)

training:
	g++ $(CFLAGS) training.cpp $(HOP_LIB) $(IM_LIB) $(MAT_LIB)
