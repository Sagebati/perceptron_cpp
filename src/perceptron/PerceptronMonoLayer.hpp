//
// Created by sam on 04/12/17.
//

#ifndef PERCEPTRON_PERCEPTRONMONOLAYER_HPP
#define PERCEPTRON_PERCEPTRONMONOLAYER_HPP


#include <opencv2/core/mat.hpp>
#include "Neuron.hpp"
#include "ItemNN.hpp"


class PerceptronMonoLayer {
private:
    std::vector<Neuron> neurons;

public:
    explicit PerceptronMonoLayer(const std::vector<Neuron> &neurons);

    void learn(std::vector<ItemNN<double>> const & items);

    /**
     *
     * @param items set of learnin
     * @param numCycles number of times we want to loop on the set
     */
    void learn(std::vector<ItemNN<double>> const & items,size_t numCycles);
    /**
     * Function to test a set of images
     * @param e
     */
    void test(std::vector<ItemNN<double>> const &e);

    /**
     * Function to test one item
     * @param e
     * @return 1 if the was succefull
     */
    bool test(ItemNN<double> const &e);

//TODO void addBiais(size_t nbrBiais);
};

std::vector<double> intToVec(size_t x);

std::vector<double> intToVec(double x);

size_t getIdMax(std::vector<double> output);

#endif //PERCEPTRON_PERCEPTRONMONOLAYER_HPP
