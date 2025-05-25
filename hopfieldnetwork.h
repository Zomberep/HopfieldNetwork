#ifndef H_HOPFIELD_NETWORK
#define H_HOPFIELD_NETWORK

#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
#include <fstream>
#include "image.h"
#include "matrix.h"

class HopfieldNetwork {
    Image* images{nullptr};
    Matrix* links{nullptr};
    size_t dim{0}, len{0};

    template<typename Type>
    inline int sign(Type arg) {return (arg >= 0) - (arg < 0);};
    inline void set_links(Matrix& matrix) {links = new Matrix{}; *links = matrix;};
    size_t* get_random_permutation();
    
    HopfieldNetwork() = default;
    inline void set_dim(size_t dim) {this->dim = dim;};
    inline void set_len(size_t len) {this->len = len;}; 
public:
    static HopfieldNetwork* receive(std::string path);

    HopfieldNetwork(size_t dim, size_t len, Image* images);
    inline size_t get_dim() const {return dim;};
    inline size_t get_len() const {return len;};
    inline const Image* get_images() const {return images;};
    inline const Matrix* get_links() const {return links;};
    void train();
    void save(std::string path);
    Image* recognize(const Image& im);
    ~HopfieldNetwork() {
        if (images)
            delete[] images;
        if (links)
            delete links;
    }
};

#endif