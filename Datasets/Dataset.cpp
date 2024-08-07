//
// Created by Luca Schmitt on 07.08.24.
//

#include "Dataset.h"

#include <cstdio>
#include <algorithm>
#include <random>
#include <iostream>

// ___________________________________________________________________________
template<typename T>
Dataset<T>::Dataset(size_t size, u_int8_t diversity) {
    size_ = size;
    diversity_ = diversity;

    // Set the start and stop indices to the first and last elements to handle immediate sorting requests
    subsectionStart_ = 0;
    subsectionStop_ = size - 1;
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::normalizeDataset() {
    // Find the maximum value as a reference for normalization
    T maxVal = *std::max_element(data_.begin(), data_.end());

    // Loop over all data points and normalize them
    for (size_t i = 0; i < size_; ++i) {
        normalizedData_[i] = static_cast<float>(data_[i]) / maxVal;
    }
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::createDataset() {

    // Create a source of randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate random values between 1 and diversity for every element in the range of size_. Also check for types
    if constexpr (std::is_same<T, int>::value) {
        // Instantiate integer distribution
        std::uniform_int_distribution<> dis(1, diversity_);

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = dis(gen);
        }
    } else {
        // Instantiate real distribution
        std::uniform_real_distribution<T> dis(1.0, static_cast<T>(diversity_));

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = dis(gen);
        }
    }
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::setSize(size_t size) {
    size_ = size;
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::setDiversity(u_int8_t diversity) {
    diversity_ = diversity;
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::setSubsectionStart(size_t subsectionStart) {
    subsectionStart_ = subsectionStart;
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::setSubsectionStop(size_t subsectionStop) {
    subsectionStop_ = subsectionStop;
}

// ___________________________________________________________________________
template<typename T>
size_t Dataset<T>::getSize() {
    return data_.size();
}

// ___________________________________________________________________________
template<typename T>
u_int8_t Dataset<T>::getDiversity() {
    return diversity_;
}

// ___________________________________________________________________________
template<typename T>
size_t Dataset<T>::getSubsectionStart() {
    return subsectionStart_;
}

// ___________________________________________________________________________
template<typename T>
size_t Dataset<T>::getSubsectionStop() {
    return subsectionStop_;
}

// ___________________________________________________________________________
template<typename T>
std::vector<float> Dataset<T>::getNormalizedData() {
    return normalizedData_;
}

// ___________________________________________________________________________
template<typename T>
std::vector<T> Dataset<T>::getData() {
    return data_;
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::sortSubsection(bool reverse) {
    // Defined the iterators for the sorting function
    auto startIt = data_.begin() + subsectionStart_;
    auto stopIt = data_.end() + subsectionStop_;

    // Sort the dataset in reverse order. Optionally only subsections
    if (reverse) {
        std::sort(startIt, stopIt, std::greater<T>());
    } else {
        // Sort the dataset. Optionally only subsections
        std::sort(startIt, stopIt);
    }

    // Normalize the dataset after sorting.
    normalizeDataset();
}

// ___________________________________________________________________________
template<typename T>
void Dataset<T>::shuffleSubsection() {
    // Create a source of randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the dataset or subsections of it
    std::shuffle(data_.begin() + subsectionStart_, data_.end() + subsectionStop_, gen);

    // Normalize the shuffled data set
    normalizeDataset();
}

template<typename T>
void Dataset<T>::updateData(std::pair<size_t, size_t> indices) {
    // Swap two elements in the data array to reduce computational cost
    T swapper = indices.first;
    data_[indices.first] = data_[indices.second];
    data_[indices.second] = swapper;
}

template<typename T>
void Dataset<T>::updateNormalizedData(std::pair<size_t, size_t> indices) {
    // Swap two elements in the normalized data array to reduce computational cost
    T swapper = indices.first;
    normalizedData_[indices.first] = normalizedData_[indices.second];
    normalizedData_[indices.second] = swapper;
}


// Explicit instantiations of the Dataset template for the currently supported types
template class Dataset<int>;
template class Dataset<float>;
template class Dataset<double>;
