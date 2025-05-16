#include "hopfieldnetwork.h"

enum learning_params {
    letter_amount=6,
    dim=64,
    req_len=(dim / (8 * sizeof(u_int8_t)) + (dim % (8 * sizeof(u_int8_t)) != 0)),
    n=8,
    m=8,
};

int main() {
    u_int8_t letter[req_len]{0};
    Image* images = new Image[letter_amount];

    std::ifstream in{"./BinaryFiles/images.bin", std::ios::in | std::ios::binary}; //

    if (in.is_open()) {
        for (size_t i = 0; i < letter_amount; ++i) {
            in.read((char *)letter, req_len);
            images[i] = Image(dim, letter, n, m);
            images[i].show_data();
        }

        in.close();

        HopfieldNetwork network{dim, letter_amount, images};    
        network.train();
    
        network.save("./BinaryFiles/trained_network.bin");
    }

    delete[] images;

    return 0;
};