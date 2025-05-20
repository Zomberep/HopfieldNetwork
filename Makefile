CFLAGS = -Wall -Wextra -std=c++23
HOP_LIB = hopfieldnetwork.cpp
MAT_LIB = matrix.cpp
IM_LIB = image.cpp
TARGET_NETWORK = network
TARGET_TRAINING = training

all: $(TARGET_NETWORK) $(TARGET_TRAINING)

$(TARGET_NETWORK):
	g++ -o $@ $(CFLAGS) network.cpp $(HOP_LIB) $(IM_LIB) $(MAT_LIB)

$(TARGET_TRAINING):
	g++ -o $@ $(CFLAGS) training.cpp $(HOP_LIB) $(IM_LIB) $(MAT_LIB)

clean:
	rm -f $(TARGET_NETWORK) $(TARGET_TRAINING)