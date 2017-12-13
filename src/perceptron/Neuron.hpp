//
// Created by sam on 04/12/17.
//

#ifndef PERCEPTRON_NEURON_HPP
#define PERCEPTRON_NEURON_HPP

#include <iostream>
#include <vector>
#include <boost/numeric/ublas/vector.hpp>


class Neuron {
private:
    boost::numeric::ublas::vector<double> weights;
    double gradient;
    double (*functionAct)(double);

public:
    Neuron(const boost::numeric::ublas::vector<double> &weights, double (*functionAct)(double));

    double getOutput(boost::numeric::ublas::vector<double> const &entries);

    const boost::numeric::ublas::vector<double> &getWeights() const;

    void setWeights(const boost::numeric::ublas::vector<double> &weights);

    void setFunctionAct(double (*functionAct)(double));

    void correctWeitghs(boost::numeric::ublas::vector<double> const &e, double result, double expected);
};


#endif //PERCEPTRON_NEURON_HPP
