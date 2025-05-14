#include "hopfieldnetwork.h"
#include <fstream>
#include <bitset>

enum params {
    letter_amount=4,
    dim=10,
    req_len=(dim / (8 * sizeof(u_int8_t)) + (dim % (8 * sizeof(u_int8_t)) != 0))
};

int main() {
    u_int8_t letter[req_len]{0};
    Image* images = new Image[letter_amount];

    std::ifstream in{"./hopfield_binary.bin", std::ios::in | std::ios::binary}; //

    if (in.is_open()) {
        for (size_t i = 0; i < letter_amount; ++i) {
            in.read((char *)letter, req_len);
            images[i] = Image(dim, letter, 2, 5); //
        }

        in.close();

        HopfieldNetwork network{dim, letter_amount, images};    
        network.train();
    
        network.save("./BinaryFiles/trained_network.bin");
    }

    delete[] images;

    return 0;
};