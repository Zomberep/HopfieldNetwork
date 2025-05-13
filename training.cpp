#include "hopfieldnetwork.h"
#include <fstream>
#include <bitset>

int main() {
    u_int8_t letter[32]{0};
    Image* images = new Image[33];

    std::ifstream in{"./BinaryFiles/russian_alphabet.bin", std::ios::in | std::ios::binary};

    if (in.is_open()) {
        for (size_t i = 0; i < 33; ++i) {
            in.read((char *)letter, 32);
            images[i] = Image(256, letter, 16, 16);
        }

        in.close();

        HopfieldNetwork network{256, 33, images};    
        network.train();
    
        network.save("./BinaryFiles/trained_network.bin");
    }

    delete[] images;

    return 0;
};