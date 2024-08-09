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
    template<class T>
    void createSorters(const std::vector<std::string>& sorterNameList);

    // Set the dataset
    template <class T>
    void setDataset(Dataset<T>);
private:
    // Vector storing the different sorter instances
    std::vector<Sorter> sorters_;

    // Variant that can store the templated datasets
    // std::variant<Dataset<int>, Dataset<float>, Dataset<double>> dataset_;

};

#endif //FINALSORTVISUALIZER_MAINAPPLICATION_H
