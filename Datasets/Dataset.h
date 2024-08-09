//
// Created by Luca Schmitt on 07.08.24.
//

#ifndef FINALSORTVISUALIZER_DATASET_H
#define FINALSORTVISUALIZER_DATASET_H

#include <cstdio>
#include <utility>
#include <vector>

/*
 * Manage the dataset to be sorted and visualized.
 *
 * Responsibilities:
 * - Create, normalize, sort, and shuffle a dataset (or sections of it).
 * - Provide data for visualization.
 *
 * Interactions:
 * - Interacted with by MainApplication to manage data (storing the initial dataset for later optional benchmarking).
 * - Interacted with by DatasetVisualization (subclass of UIComponent) to reflect data state in the UI.
 * - Interacted with by Sorter (containing the sorting algorithm) to (efficiently) sort data and normalized data
 *
 * Thoughts on the rule of three / five:
 * - We do dynamically allocate memory, so we also have to delete it again --> Destructor
 * - The Dataset will have to be copied (or at least the dataset within). Depending on the internal functioning of
 * screen and UI component transitions, the dataset should probably also be moveable...
 *
 * Additional thoughts:
 * - Should data_ rather be a vector? Would work better for visualizations, but what are the drawbacks?
 * - Add safeguards against renormalization
 *
 *
 * --- Implement copy semantics ---
 */
class Dataset {
public:
    // Constructor and destructor
    Dataset(size_t size, u_int8_t diversity);
    ~Dataset() = default;

    // Copy constructor and assignment operator
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);

    // Move constructor and assignment operator. Likely not needed
    Dataset(Dataset&& other) noexcept;
    Dataset& operator=(Dataset&& other) noexcept;

    // Normalize the dataset so it can be visualized
    void normalizeDataset();

    // Create a dataset. Here I still have to think about the data types to include and therefore also the best
    // template structure / instantiations (Meaning if I need separate functions for different types T)
    void createDataset();

    // Setter and getter functions (Here we also have to see if the subsection indicators will stay here...)
    void setSize(size_t size);
    void setDiversity(u_int8_t diversity);
    void setSubsectionStart(size_t subsectionStart);
    void setSubsectionStop(size_t subsectionStop);

    size_t getSize() const;
    [[nodiscard]] u_int8_t getDiversity() const;

    // The following two getters are very likely not needed... Or they might be. Depends on the subsection selection
    // animation...
    size_t getSubsectionStart();
    size_t getSubsectionStop();

    // Returns a copy of the data / normalized data. Used when giving the initial data to multiple sorter instances
    std::vector<float> getNormalizedData();
    std::vector<int> getData();

    // Takes the indices swapped in the stepSort function of a Sorter instance. Then swaps these two indices in the
    // normalized data to avoid computing everything again.
    void updateNormalizedData(std::pair<size_t, size_t> indices);
    void updateData(std::pair<size_t, size_t> indices);

    // Sort a subsection of the current dataset using built the built-in std::sort and the subsectionIndices
    void sortSubsection(bool reverse);
    void shuffleSubsection();

private:
    // Size of the data set
    size_t size_;

    // Parameter used as a factor in the data creation to control data diversity. Should this be increased to u_int16_t?
    u_int8_t diversity_;

    // The actual data
    std::vector<int> data_;

    // Field containing the normalized data, so we don't have to compute it every time for the visualization.
    // Should this be a float or double? (with u_int8_t (and even 16) float precision should be sufficient, I guess)
    std::vector<float> normalizedData_;

    // Storing selection for subsections (Can probably be out sources to the DataVisualization instance)
    size_t subsectionStart_;
    size_t subsectionStop_;
};



#endif //FINALSORTVISUALIZER_DATASET_H
