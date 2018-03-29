//
// Created by sam on 04/12/17.
//

#include <boost/numeric/ublas/io.hpp>
#include <cv.hpp>
#include "PerceptronMonoLayer.hpp"

PerceptronMonoLayer::PerceptronMonoLayer(const std::vector<Neuron> &neurons) : neurons(neurons) {}

void PerceptronMonoLayer::learn(std::vector<ItemNN<double>> const &items) {
    size_t cycles = 25;
    this->learn(items, 25);
}

/**
 * Method to begin learning with the perceptron
 * @param numCycles number of times that the perceptron loop on the set of learning
 */
void PerceptronMonoLayer::learn(std::vector<ItemNN<double>> const &items, size_t numCycles) {
    size_t sizeSet = items.size();
    size_t j = 0;
    size_t correct, incorrect;
    std::vector<double> succes_rates;
    succes_rates.push_back(0.);
    std::vector<double> outputs;
    do {
        correct = 0;
        incorrect = 0;
        for (ItemNN<double> const &item:items) {
            for (auto &entry: item.getVecEntries()) {
                for (auto &neuron : neurons) {
                    double output = neuron.getOutput(entry);
                    outputs.push_back(output);
                }
                auto vec_expected = intToVec(item.getExpected());
                double outputInt = getIdMax(outputs);
                auto vec_result = intToVec(outputInt);
                if (vec_result == vec_expected) {
                    correct++;
                } else {
                    for (int i = 0; i < vec_expected.size(); i++) {
                        neurons[i].correctWeitghs(entry, vec_expected[i], outputs[i]);
                    }
                    incorrect++;
                }
                outputs.clear();
            }
        }
        double succes_rate = (correct * 1.0) / (items.size() * items[0].getVecEntries().size()) * 100;
        succes_rates.push_back(succes_rate);
        std::cout << "success rate:\n" << succes_rate << std::endl;
    } while (succes_rates[++j] != succes_rates[j - 1] && j < numCycles);
}

void PerceptronMonoLayer::test(std::vector<ItemNN<double>> const &e) {
    size_t i = 0;
    size_t correct = 0, incorrect = 0;
    for (ItemNN<double> const &item:e) {
        if (test(item))
            correct++;
        else
            incorrect++;

        ++i;
    }
    std::cout << "success rate test: " << (correct * 1.0) / e.size() * 100 << std::endl;
}

bool PerceptronMonoLayer::test(ItemNN<double> const &e) {
    std::vector<double> outputs;
    for (auto &neuronne : neurons) {
        double output = neuronne.getOutput(e.getEntry());
        outputs.push_back(output);
    }
    return (intToVec(getIdMax(outputs)) == intToVec(e.getExpected()));
}


std::vector<double> intToVec(size_t x) {
    std::vector<double> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    res[x] = 1;
    return res;
}

std::vector<double> intToVec(double x) {
    std::vector<double> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    res[x] = 1;
    return res;
}

size_t getIdMax(std::vector<double> output) {
    size_t res = 0;
    double buff = -DBL_MAX;
    for (size_t i = 0; i < output.size(); ++i) {
        if (output[i] > buff) {
            buff = output[i];
            res = i;
        }
    }
    return res;
}