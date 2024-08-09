//
// Created by Luca Schmitt on 07.08.24.
//

#include "Dataset.h"

#include <cstdio>
#include <algorithm>
#include <random>
#include <iostream>

// ___________________________________________________________________________
Dataset::Dataset(size_t size, u_int8_t diversity) {
    size_ = size;
    diversity_ = diversity;

    // Set the start and stop indices to the first and last elements to handle immediate sorting requests
    subsectionStart_ = 0;
    subsectionStop_ = size - 1;

    // Set up the date
    createDataset();
    normalizeDataset();
}

// Copy Constructor
Dataset::Dataset(const Dataset& other)
        : size_(other.size_),
          diversity_(other.diversity_),
          data_(other.data_),
          normalizedData_(other.normalizedData_),
          subsectionStart_(other.subsectionStart_),
          subsectionStop_(other.subsectionStop_) {
    // Additional deep copy logic necessary?
}

// Copy Assignment Operator
Dataset& Dataset::operator=(const Dataset& other) {
    // Handle self-assignment
    if (this == &other) {
        return *this;
    }

    // Copy the data members
    size_ = other.size_;
    diversity_ = other.diversity_;
    data_ = other.data_;
    normalizedData_ = other.normalizedData_;
    subsectionStart_ = other.subsectionStart_;
    subsectionStop_ = other.subsectionStop_;

    return *this;
}

// Move Constructor
Dataset::Dataset(Dataset&& other) noexcept
        : size_(other.size_),
          diversity_(other.diversity_),
          data_(std::move(other.data_)),
          normalizedData_(std::move(other.normalizedData_)),
          subsectionStart_(other.subsectionStart_),
          subsectionStop_(other.subsectionStop_) {

    // Leave 'other' object in a valid state
    other.size_ = 0;
    other.diversity_ = 0;
    other.subsectionStart_ = 0;
    other.subsectionStop_ = 0;
}

// Move Assignment Operator
Dataset& Dataset::operator=(Dataset&& other) noexcept {
    // Handle self-assignment
    if (this == &other) {
        return *this;
    }

    // Transfer ownership from 'other' to 'this'
    size_ = other.size_;
    diversity_ = other.diversity_;
    data_ = std::move(other.data_);
    normalizedData_ = std::move(other.normalizedData_);
    subsectionStart_ = other.subsectionStart_;
    subsectionStop_ = other.subsectionStop_;

    // Leave 'other' object in a valid state
    other.size_ = 0;
    other.diversity_ = 0;
    other.subsectionStart_ = 0;
    other.subsectionStop_ = 0;

    return *this;
}

// ___________________________________________________________________________
void Dataset::normalizeDataset() {
    // Find the maximum value as a reference for normalization
    int maxVal = *std::max_element(data_.begin(), data_.end());

    // Loop over all data points and normalize them
    for (size_t i = 0; i < size_; ++i) {
        normalizedData_.push_back(static_cast<float>(data_[i]) / static_cast<float>(maxVal));
    }
}

// ___________________________________________________________________________
void Dataset::createDataset() {

    // Create a source of randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    // Instantiate integer distribution
    std::uniform_int_distribution<> dis(1, diversity_);

    // Generate random values between 1 and diversity for every element in the range of size_.
    for (size_t i = 0; i < size_; ++i) {
        data_.push_back(dis(gen));
    }
}

// ___________________________________________________________________________
void Dataset::setSize(size_t size) {
    size_ = size;
}

// ___________________________________________________________________________
void Dataset::setDiversity(u_int8_t diversity) {
    diversity_ = diversity;
}

// ___________________________________________________________________________
void Dataset::setSubsectionStart(size_t subsectionStart) {
    subsectionStart_ = subsectionStart;
}

// ___________________________________________________________________________
void Dataset::setSubsectionStop(size_t subsectionStop) {
    subsectionStop_ = subsectionStop;
}

// ___________________________________________________________________________
size_t Dataset::getSize() const {
    return data_.size();
}

// ___________________________________________________________________________
u_int8_t Dataset::getDiversity() const {
    return diversity_;
}

// ___________________________________________________________________________
size_t Dataset::getSubsectionStart() {
    return subsectionStart_;
}

// ___________________________________________________________________________
size_t Dataset::getSubsectionStop() {
    return subsectionStop_;
}

// ___________________________________________________________________________
std::vector<float> Dataset::getNormalizedData() {
    return normalizedData_;
}

// ___________________________________________________________________________
std::vector<int> Dataset::getData() {
    return data_;
}

// ___________________________________________________________________________
void Dataset::sortSubsection(bool reverse) {
    // Defined the iterators for the sorting function
    auto startIt = data_.begin() + subsectionStart_;
    auto stopIt = data_.end() + subsectionStop_;

    // Sort the dataset in reverse order. Optionally only subsections
    if (reverse) {
        std::sort(startIt, stopIt, std::greater<>());
    } else {
        // Sort the dataset. Optionally only subsections
        std::sort(startIt, stopIt);
    }

    // Normalize the dataset after sorting.
    normalizeDataset();
}

// ___________________________________________________________________________
void Dataset::shuffleSubsection() {
    // Create a source of randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the dataset or subsections of it
    std::shuffle(data_.begin() + subsectionStart_, data_.end() + subsectionStop_, gen);

    // Normalize the shuffled data set
    normalizeDataset();
}

void Dataset::updateData(std::pair<size_t, size_t> indices) {
    // Swap two elements in the data array to reduce computational cost
    int swapper = data_[indices.first];
    data_[indices.first] = data_[indices.second];
    data_[indices.second] = swapper;
}

void Dataset::updateNormalizedData(std::pair<size_t, size_t> indices) {
    // Swap two elements in the normalized data array to reduce computational cost
    float swapper = normalizedData_[indices.first];
    normalizedData_[indices.first] = normalizedData_[indices.second];
    normalizedData_[indices.second] = swapper;
}
