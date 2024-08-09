//
// Created by Luca Schmitt on 08.08.24.
//



#include "Sorter.h"

#include <numeric>

// Here the move shouldn't affect the initial dataset. Only the instance passed to the constructor should be 
// copied from there
Sorter::Sorter(Dataset dataset) : dataset_(std::move(dataset)) {
    stepCounter_ = 0;
    stepIndex_ = 0;
    iterationIndex_ = 0;
    isSorted_ = false;
    
}

void Sorter::setDataset(Dataset dataset) {
    dataset_ = dataset;
    normalizedData_ = dataset.getNormalizedData();
}

std::vector<int> *Sorter::getComparisonTracker() {
    return &comparisonTracker_;
}

std::vector<int> *Sorter::getCopyTracker() {
    return &copyTracker_;
}

std::vector<int> *Sorter::getMoveTracker() {
    return &moveTracker_;
}

unsigned int Sorter::getStepCount() const {
    return stepCounter_;
}

bool Sorter::isSorted() const {
    return isSorted_;
}

double Sorter::benchmarkPerformance(u_int8_t repetitions, bool useCopy, bool accountForMemoryAllocation) {
    // Vector to store the run times
    std::vector<double> runTimes;

    // Run the performance sort for 'repetitions' iterations
    for (u_int8_t i = 0; i < repetitions; i++) {
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

        performanceSort(useCopy, accountForMemoryAllocation);

        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;

        runTimes.push_back(duration.count());
    }

    double averageTime = std::accumulate(runTimes.begin(), runTimes.end(), 0.0) / runTimes.size();
    return averageTime;
}


// --- BubbleSorter ---

BubbleSorter::BubbleSorter(Dataset dataset) : Sorter(std::move(dataset)) { }

std::pair<size_t, size_t> BubbleSorter::stepSort(bool useCopy) {
    // If sorted, return invalid indices. Make sure to check for these in the receiver functions
    if (isSorted_) {
        return std::pair(-1, -1);
    }

    // Increment the step counter
    stepCounter_++;

    // Bool to check if any pair was swapped
    bool swapped = false;
    std::pair<size_t, size_t> swappedIndices;

    // Tracker variables
    int compares = 0;
    int copies = 0;
    int moves = 0;

    // Perform one step of bubble sorting. Is this necessary with the counter-resets?
    if (stepIndex_ < normalizedData_.size() - 1) {
        // Update compare tacker
        compares += 1;

        if (normalizedData_[stepIndex_] > normalizedData_[stepIndex_ + 1]) {
            // Swap the two elements and set swapped to true
            std::swap(normalizedData_[stepIndex_], normalizedData_[stepIndex_ + 1]);
            swapped = true;

            // Update copy / move tracker variables
            copies += useCopy ? 3 : 1;
            moves += useCopy ? 0 : 2;
        }
        // Increment the step index counter
        stepIndex_++;

        swappedIndices = std::pair<size_t, size_t>(stepIndex_ - 1, stepIndex_);

        // If the last element has been reached, increment iterationIndex and reset stepIndex
        if (stepIndex_ == normalizedData_.size()) {
            iterationIndex_++;
            stepIndex_ = iterationIndex_;
        }
    }

    // Add the tracker results to the vectors
    comparisonTracker_.push_back(compares);
    copyTracker_.push_back(copies);
    moveTracker_.push_back(moves);

    // Check if the array is sorted
    if (!swapped) {
        isSorted_ = true;

        // Return the sorted flags via indices
        return std::pair(-1, -1);
    }

    return swappedIndices;
}

void BubbleSorter::performanceSort(bool useCopy, bool accountForMemoryAllocation) {

}

