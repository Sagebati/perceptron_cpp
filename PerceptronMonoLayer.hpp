//
// Created by sam on 04/12/17.
//

#ifndef PERCEPTRON_PERCEPTRONMONOLAYER_HPP
#define PERCEPTRON_PERCEPTRONMONOLAYER_HPP


#include <opencv2/core/mat.hpp>
#include "Neuron.hpp"

struct Image {
    cv::Mat *mat;
    boost::numeric::ublas::vector<double> *e;
};

struct PairImageLabel {
    Image image;
    double res;
};

class PerceptronMonoLayer {
private:
    std::vector<Neuron> neuronnes;
    std::vector<Image> ensApprendtissage;
    std::vector<double> lsExpected;

public:
    PerceptronMonoLayer(std::vector<Neuron> neuronnes, std::vector<Image> ensApprentissage, std::vector<double> lsExpected);

    void learn();

    void test(std::vector<Image> const &e, std::vector<double> const &labels);

    bool test(Image const &e, const double label);

    // Later
//    void addBiais(size_t nbrBiais);
};

std::vector<double> intToVec(size_t x);

std::vector<double> intToVec(double x);

size_t getIdMax(std::vector<double> output);

#endif //PERCEPTRON_PERCEPTRONMONOLAYER_HPP
