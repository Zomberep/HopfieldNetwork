#include <fstream>
#include "hopfieldnetwork.h"

int main(int argc, char** argv) {
    bool flag = true;

    if (argc < 2) {
        std::cout << "Incorrect number of arguments!" << std::endl;
        flag = false;
    }

    std::ifstream in{"./BinaryFiles/trained_network.bin", std::ios::in | std::ios::binary};
    if (in.is_open()) {
        
    }
}