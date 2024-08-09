//
// Created by Luca Schmitt on 07.08.24.
//

#ifndef FINALSORTVISUALIZER_MAINAPPLICATION_H
#define FINALSORTVISUALIZER_MAINAPPLICATION_H

#include "../SwiftifySFML/Application.h"
#include "../Settings/Settings.h"
#include "../Sorter/Sorter.h"

class MainApplication: public sw::Application {
public:
    explicit MainApplication(sf::RenderWindow& window);

    // Create the sorter instances
    void createSorters(const std::vector<std::string>& sorterNameList);

    // Set the dataset
    void setDataset(size_t size, u_int8_t diversity);

    // Get a reference to the vector with the sorter instances
    std::vector<std::unique_ptr<Sorter>>& getSorters();
private:
    // Vector storing the different sorter instances
    std::vector<std::unique_ptr<Sorter>> sorters_;

    // Variant that can store the templated datasets
    Dataset dataset_;

};

#endif //FINALSORTVISUALIZER_MAINAPPLICATION_H
