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

    std::ifstream in{"./BinaryFiles/images.bin", std::ios::in | std::ios::binary};

    try {
        if (in.is_open()) {
            for (size_t i = 0; i < letter_amount; ++i) {
                in.read((char *)letter, req_len);
                images[i] = Image(dim, letter, n, m);
                std::cout << i << " image:" << std::endl;
                std::cout << "-----------------------------------";
                images[i].show_data();
                std::cout << "-----------------------------------" << std::endl;
            }

            HopfieldNetwork network{dim, letter_amount, images};    
            network.train();
        
            network.save("./BinaryFiles/trained_network.bin");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception!" << std::endl;
    }

    delete[] images;
    if (in) 
        in.close();

    return 0;
};