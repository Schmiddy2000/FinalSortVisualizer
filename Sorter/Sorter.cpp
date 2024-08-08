//
// Created by Luca Schmitt on 08.08.24.
//



#include "Sorter.h"

#include <numeric>

template<class T>
Sorter::Sorter(Dataset<T> dataset) {
    stepCounter_ = 0;
    isSorted_ = false;
}

template<class T>
void Sorter::setDataset(Dataset<T> dataset) {
    dataset_ = dataset;
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



