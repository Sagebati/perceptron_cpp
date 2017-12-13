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

    void learn(std::vector<ItemNN<double>> const & items,size_t numCycles);

    void test(std::vector<ItemNN<double>> const &e);

    bool test(ItemNN<double> const &e);

//TODO void addBiais(size_t nbrBiais);
};

std::vector<double> intToVec(size_t x);

std::vector<double> intToVec(double x);

size_t getIdMax(std::vector<double> output);

#endif //PERCEPTRON_PERCEPTRONMONOLAYER_HPP
