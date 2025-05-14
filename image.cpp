#include "image.h"

void Image::show_data() const {
    if (!is_data) {
        throw std::invalid_argument("Your image is empty");
    }
    if (!n || !m) {
        throw std::invalid_argument("Dimensions (n, m) should be set before");
    }

    size_t byte_index{0};
    u_int8_t bit_mask = 0b10000000;
    
    for (size_t i = 0; i < length; ++i) {
        if (i % m == 0)
            std::cout << '\n';
        
        std::cout << ((data[byte_index] & bit_mask) ? '*' : ' ');
        
        bit_mask >>= 1;
        if (!bit_mask) {
            bit_mask = 0b10000000;
            ++byte_index;
        }
    }

    std::cout << '\n';
};

size_t Image::allocate_memory(size_t l) {
    size_t req_len = (l / (8 * sizeof(u_int8_t))) + ((l % (8 * sizeof(u_int8_t))) != 0);
    try {
        this->data = new u_int8_t[req_len]{0};
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation error: your image requires too much memory" << std::endl;
    }

    this->is_allocated = (data != nullptr);

    return req_len;
};

void Image::set_length(size_t l) {
    if (is_allocated)
        this->clean_data();

    this->length = l;
};

void Image::set_data(u_int8_t* data) {
    if (!this->length)
        throw std::invalid_argument("The length of data should be set before");
    else {
        if (!data) {
            throw std::invalid_argument("Data cannot be nullptr");
        }

        if (is_allocated)
            this->clean_data();
        
        size_t req_len = this->allocate_memory(this->length);
        if (is_allocated) {
            memcpy(this->data, data, req_len * sizeof(u_int8_t));
            is_data = true;
        }

    }
};

void Image::set_size(size_t n, size_t m) {
    if (this->length && n && m && (n * m == this->length)) {
        this->n = n;
        this->m = m;
    } else {
        throw std::invalid_argument("The transmitted dimensions don't correspond to the data"); 
    }
};

Image::Image(size_t l, u_int8_t* data, size_t n, size_t m) {
    this->n = n;
    this->m = m;

    if (l) {
        size_t req_len = this->allocate_memory(l);
        this->length = l;

        if (is_allocated && data) {
            memcpy(this->data, data, req_len * sizeof(u_int8_t));
            is_data = true;
        }
    }
};

Image& Image::operator = (const Image& other) {
    if (&other != this) {
        if (is_allocated)
            this->clean_data();
        
        this->length = other.length;
        this->m = other.m;
        this->n = other.n;

        if (other.is_data) {
            size_t req_len = this->allocate_memory(this->length);
            if (is_allocated) {
                memcpy(this->data, other.data, req_len * sizeof(u_int8_t));
                this->is_data = true;
            }
        } else
            this->is_data = false;
    }

    return *this;
};

Image* Image::receive(std::string path, size_t len, size_t n, size_t m) {
    std::ifstream file{path, std::ios::in | std::ios::binary};
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for reading!");

    size_t i{0}, req_len{(len / (8 * sizeof(u_int8_t))) + (len % (8 * sizeof(u_int8_t)) != 0)}; 
    u_int8_t* data = new u_int8_t[req_len]{0};
    char curr_byte{0};

    while (file.get(curr_byte)) {
        data[i++] = curr_byte;
    }

    Image* im = new Image{len, data, n, m};

    file.close();
    delete[] data;

    return im;
}