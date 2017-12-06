//
// Created by sam on 04/12/17.
//

#include <boost/numeric/ublas/io.hpp>
#include <cv.hpp>
#include "PerceptronMonoLayer.hpp"


PerceptronMonoLayer::PerceptronMonoLayer(std::vector<Neuron> neuronnes, std::vector<Image> ensApprentissage, std::vector<double> lsExpected)
        : neuronnes(std::move(neuronnes)), ensApprendtissage(std::move(ensApprentissage)), lsExpected(std::move(lsExpected)) {}


void PerceptronMonoLayer::apprendre() {
    size_t sizeEns = ensApprendtissage.size();
    size_t i = 0;
    size_t correct;
    size_t incorrect;
//    do {
    correct = 0;
    i = 0;
    incorrect = 0;
    for (Image const &image:ensApprendtissage) {
        for (size_t in = 0; in < neuronnes.size(); ++in) {
            double output = neuronnes[in].getOutput(*image.e);
//                std::cout << "expected:" << lsExpected[i] << "n neuronne : " << in << " output : " << output;
            if (intToVec(in) != intToVec(lsExpected[i])) {
                incorrect++;
                if (in == lsExpected[i]) {
                    if (output == 1) {
//                      std::cout << " correct";
                    } else {
//                      std::cout << " incorrect";
                        neuronnes[in].correctWeitghs(*image.e, output, lsExpected[i]);
                    }
                } else {
                    if (output == 0) {
//                      std::cout << " correct";
                    } else {
//                      std::cout << " incorrect";
                        neuronnes[in].correctWeitghs(*image.e, output, lsExpected[i]);
                    }
                }
            } else {
                correct++;
            }
//                std::cout << std::endl;
        }
//            std::cout << "fin de boucle" << std::endl;
//            std::cout<<"nbr boucles"<<i<<std::endl;
        ++i;
//            std::cout<<"correct: "<<correct<<std::endl;
//            std::cout<<"incorrect: "<<incorrect<<std::endl;
    }
    std::cout << "success rate: " << (correct * 1.0) / ensApprendtissage.size() * 100 << std::endl;
//    } while (correct != (sizeEns * 9));
}

void PerceptronMonoLayer::tester(std::vector<Image> const &e, std::vector<double> const &labels) {
    size_t i = 0;
    size_t correct;
    size_t incorrect;
    correct = 0;
    i = 0;
    incorrect = 0;
    for (Image const &image:e) {
        for (size_t in = 0; in < neuronnes.size(); ++in) {
            double output = neuronnes[in].getOutput(*image.e);
            if (intToVec(in) != intToVec(labels[i])) {
                incorrect++;
            } else {
                correct++;
            }
        }
        ++i;
    }
    std::cout << "success rate test: " << (correct * 1.0) / e.size() * 100 << std::endl;
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
