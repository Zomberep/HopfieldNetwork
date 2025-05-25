#include "hopfieldnetwork.h"

size_t* HopfieldNetwork::get_random_permutation() {
    size_t* numbers = new size_t[dim];

    for (size_t i = 0; i < dim; ++i) {
        numbers[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers, numbers + dim, std::default_random_engine(seed));

    return numbers;
};

HopfieldNetwork::HopfieldNetwork(size_t dim, size_t len, Image* images) {
    if (dim == 0 || len == 0) {
        throw std::invalid_argument("Dimension and length cannot be zero");
    }
    if (images == nullptr) {
        throw std::invalid_argument("Images array is nullptr");
    }
    if (len > 0.14 * dim) {
        std::cout << "WARNING: Capacity exceeded (len > 0.14 * dim)\n" << std::endl;
    }

    this->dim = dim;
    this->len = len;

    for (size_t i = 0; i < len; ++i) {
        if (images[i].get_length() != dim)
            throw std::invalid_argument("Image " + std::to_string(i) + " has wrong dimension");
        if (!images[i].get_is_data())
            throw std::invalid_argument("Image " + std::to_string(i) + " is empty");
    }

    try {
        this->images = new Image[len];
        links = new Matrix{dim, dim};
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed");
    }

    for (size_t i = 0; i < len; ++i) {
        this->images[i] = images[i];
    }
}

void HopfieldNetwork::train() {
    Matrix* curr_image = new Matrix, *curr_image_T = new Matrix;
    double* curr_data = new double[dim];

    for (size_t i = 0; i < len; ++i) {
        images[i].get_data<double>(curr_data);

        curr_image->set_matrix(1, dim, curr_data);
        curr_image_T->set_matrix(dim, 1, curr_data);
        *links += *curr_image_T * *curr_image;
    }

    links->zero_main_diag();
    *links *= (1.0 / dim);

    if (curr_image)
        delete curr_image;
    if (curr_image_T)
        delete curr_image_T;
    if (curr_data)
        delete[] curr_data;
}

Image* HopfieldNetwork::recognize(const Image& im) {
    if (!im.get_is_data()) {
        throw std::invalid_argument("Given image is empty");
    }
    if (im.get_length() != this->dim) {
        throw std::invalid_argument("Dimension of the image should be the same with 'dim' parameter");
    }

    short* neurons = new short[dim], *prev_neurons = new short[dim];
    im.get_data<short>(neurons);
    memcpy(prev_neurons, neurons, sizeof(short) * dim);

    while (true) {
        size_t* permutation = this->get_random_permutation();
        for (size_t i = 0; i < dim; ++i) {

            const double* curr_row = links->get_row(permutation[i]);
            double influence = 0;

            for(size_t j = 0; j < dim; ++j)
                influence += curr_row[j] * neurons[j];

            neurons[permutation[i]] = this->sign<double>(influence);
        }

        delete[] permutation;

        if (!memcmp(neurons, prev_neurons, sizeof(short) * dim)) {
            break;
        } else {
            memcpy(prev_neurons, neurons, sizeof(short) * dim);
        }
    }

    for (size_t i = 0; i < dim; ++i) {
        neurons[i] = (neurons[i] > 0) ? 1 : 0;
    }

    Image* recognized_image = new Image{neurons, dim, im.get_n(), im.get_m()};

    if (neurons)
        delete[] neurons;
    if (prev_neurons)
        delete[] prev_neurons;

    return recognized_image;
}

void HopfieldNetwork::save(std::string path) {
    std::ofstream file{path, std::ios::out | std::ios::binary};
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for writing!");

    file.write((char *)(&(this->dim)), sizeof(size_t));

    double** matrix = links->get_matrix();
    for (size_t i = 0; i < this->dim; ++i) {
        file.write((char*)matrix[i], sizeof(double) * this->dim);
    }

    file.close();    
}

HopfieldNetwork* HopfieldNetwork::receive(std::string path) {
    std::ifstream file{path, std::ios::in | std::ios::binary};
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for reading!");
    
    size_t dim{0};
    file.read((char *)(&dim), sizeof(size_t));

    double* matrix_data{new double[dim * dim]};
    Matrix* matrix = new Matrix{};

    file.read((char*)matrix_data, sizeof(double) * dim * dim);
    matrix->set_matrix(dim, dim, matrix_data);
    
    HopfieldNetwork* network = new HopfieldNetwork{};
    network->set_links(*matrix);
    network->set_dim(dim);
    
    delete[] matrix_data;
    delete matrix;
    file.close();

    return network;
}