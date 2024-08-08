//
// Created by Luca Schmitt on 08.08.24.
//

#ifndef FINALSORTVISUALIZER_SORTER_H
#define FINALSORTVISUALIZER_SORTER_H

#include "../Datasets/Dataset.h"

class Sorter {
public:
    // Constructor and destructor
    template<class T>
    explicit Sorter(Dataset<T> dataset);
    ~Sorter() = default;

    // Set the copy to a dataset instance
    template<class T>
    void setDataset(Dataset<T> dataset);

    // Getters for operation trackers
    std::vector<int>* getComparisonTracker();
    std::vector<int>* getCopyTracker();
    std::vector<int>* getMoveTracker();

    // Get iteration information
    unsigned int getStepCount() const;
    bool isSorted() const;

    // Function that can benchmark the sorting time
    double benchmarkPerformance(u_int8_t repetitions, bool useCopy, bool accountForMemoryAllocation);

    // Abstract method for step-by-step sorting. Implements the class-specific sorting algorithm that can be executed
    // step by step. Handles dataclass function calls internally. Returns the indices that were swapped.
    virtual std::pair<size_t, size_t> stepSort(bool useCopy) = 0;

private:
    // performanceSort() has no tracking components and just sorts the dataset with the class instances sorting
    // algorithm
    virtual void performanceSort(bool useCopy, bool accountForMemoryAllocation) = 0;

    // Keeping track of the number of iterations needed, and if the set is already sorted
    unsigned int stepCounter_;
    bool isSorted_;

    // Dataset instance
    Dataset<std::variant<int, float, double>> dataset_;

    // Operation trackers
    std::vector<int> comparisonTracker_;
    std::vector<int> copyTracker_;
    std::vector<int> moveTracker_;
};


#endif //FINALSORTVISUALIZER_SORTER_H
