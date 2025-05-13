#ifndef H_IMAGE
#define H_IMAGE

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstring>

class Image {
    u_int8_t* data{nullptr};
    size_t length{0}, n{0}, m{0};
    bool is_data{false}, is_allocated{false};

    size_t allocate_memory(size_t l);
    inline void clean_data() {
        delete[] data;
        this->is_allocated=false;
        this->is_data = false;
    };
public:
    Image(size_t l = 0, u_int8_t* data = nullptr, size_t n = 0, size_t m = 0);
    Image& operator = (const Image& other);
    ~Image() {
        if (is_allocated)
            delete[] data;
    };
    template <typename Type>
    Image(Type* array, size_t l, size_t n = 0, size_t m = 0);
    
    void show_data();
    void set_size(size_t n, size_t m);
    inline size_t get_m() const {return m;};
    inline size_t get_n() const {return n;};
    inline void set_length(size_t l);
    inline size_t get_length() const {return this->length;};
    inline bool get_is_data() const { return is_data;};
    inline const u_int8_t* get_bin_data() const {return this->data;};
    inline bool get_is_allocated() const {return is_allocated;};
    template <typename Type>
    void get_data(Type* data) const;
    void set_data(u_int8_t* data);
};

template <typename Type>
void Image::get_data(Type* data) const {
    size_t byte_index{0};
    u_int8_t bit_mask = 0b10000000;

    if (!this->is_data) {
        throw std::invalid_argument("You image is empty");
    }

    for (size_t j = 0; j < length; ++j) {
        data[j] = 2 * (Type)((this->data[byte_index] & bit_mask) != 0) - 1;
        
        bit_mask >>= 1;
        if (!bit_mask) {
            bit_mask = 0b10000000;
            ++byte_index;
        }
    }
}

template <typename Type>
Image::Image(Type* array, size_t l, size_t n, size_t m) {
    this->length = l;
    this->n = n;
    this->m = m;
    this->allocate_memory(l);
    std::fill(this->data, this->data + l, 255);

    u_int8_t bit_mask = 0b10000000;
    size_t byte_index = 0;

    for (size_t i = 0; i < l; ++i) {
        if (!array[i])
            this->data[byte_index] ^= bit_mask;
        
        bit_mask >>= 1;
        if (!bit_mask) {
            bit_mask = 0b10000000;
            ++byte_index;
        }
    }

    this->is_data = true;
}

#endif