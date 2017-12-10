//
// Created by sam on 04/12/17.
//

#include <boost/numeric/ublas/io.hpp>
#include <cv.hpp>
#include "PerceptronMonoLayer.hpp"


PerceptronMonoLayer::PerceptronMonoLayer(std::vector<Neuron> neuronnes, std::vector<Image> ensApprentissage, std::vector<double> lsExpected)
        : neuronnes(std::move(neuronnes)), ensApprendtissage(std::move(ensApprentissage)), lsExpected(std::move(lsExpected)) {}


void PerceptronMonoLayer::learn() {
    size_t sizeEns = ensApprendtissage.size();
    size_t i = 0, j = 0;
    size_t correct;
    size_t incorrect;
    std::vector<double> succes_rates;
    succes_rates.push_back(0.);
    std::vector<double> outputs;
    do {
        correct = 0;
        i = 0;
        incorrect = 0;
        for (Image const &image:ensApprendtissage) {
            double expected = lsExpected[i];
            for (auto &neuronne : neuronnes) {
                double output = neuronne.getOutput(*image.e);
                outputs.push_back(output);
            }
            auto vec_expected = intToVec(expected);
            double outputInt = getIdMax(outputs);
            auto vec_result = intToVec(outputInt);

            if (vec_result == vec_expected) {
                correct++;
            } else {
                for (int y = 0; y < vec_expected.size(); y++) {
                        neuronnes[y].correctWeitghs(*image.e, vec_expected[y], outputs[y]);
                }
                incorrect++;
            }
            outputs.clear();
            ++i;
        }
        double succes_rate = (correct * 1.0) / ensApprendtissage.size() * 100;
        succes_rates.push_back(succes_rate);
        std::cout << "success rate:\n" << succes_rate << std::endl;
    } while (succes_rates[++j] != succes_rates[j - 1] && j < 2);
}

void PerceptronMonoLayer::test(std::vector<Image> const &e, std::vector<double> const &labels) {
    size_t i = 0;
    size_t correct = 0, incorrect = 0;
    for (Image const &image:e) {
        if (test(image, labels[i]))
            correct++;
        else
            incorrect++;

        ++i;
    }
    std::cout << "success rate test: " << (correct * 1.0) / e.size() * 100 << std::endl;
}

bool PerceptronMonoLayer::test(Image const &e, double const label) {
    std::vector<double> neuroActives;
    for (auto &neuronne : neuronnes) {
        double output = neuronne.getOutput(*e.e);
        neuroActives.push_back(output);
    }
    return (intToVec(getIdMax(neuroActives)) == intToVec(label));
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
    size_t res=0;
    double buff = -DBL_MAX;
    for (size_t i = 0; i < output.size(); ++i) {
        if (output[i] > buff) {
            buff = output[i];
            res = i;
        }
    }
    return res;
}