#include "hopfieldnetwork.h"

enum learning_params {
    letter_amount=6,
    dim=64,
    req_len=(dim / (8 * sizeof(u_int8_t)) + (dim % (8 * sizeof(u_int8_t)) != 0)),
    n=8,
    m=8,
};

int main(int argc, char** argv) {
    HopfieldNetwork* network{nullptr};
    Image* im{nullptr}, *rec_im{nullptr};
    try {
        if (argc < 2) {
            throw std::runtime_error("Incorrect number of arguments!");
        }

        std::string path{argv[1]};

        network = HopfieldNetwork::receive("./BinaryFiles/trained_network.bin");
        std::cout << "Input data: " << std::endl;
        std::cout << "-----------------------------------";
        im = Image::receive(path, dim, n, m);
        im->show_data();
        std::cout << "-----------------------------------" << std::endl;

        std::cout << "Recognized data: " << std::endl;
        std::cout << "-----------------------------------";
        rec_im = network->recognize(*im);
        rec_im->show_data();
        std::cout << "-----------------------------------" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception!" << std::endl;
    }
    
    if (network)
        delete network;
    if (im)
        delete im;
    if (rec_im)
        delete rec_im;
    
    return 0;
}