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

    /**
     *
     * @param entries
     * @return the output of the neuron with the function
     */
    double getOutput(boost::numeric::ublas::vector<double> const &entries);

    void correctWeitghs(boost::numeric::ublas::vector<double> const &e, double result, double expected);

    const boost::numeric::ublas::vector<double> &getWeights() const;

    void setWeights(const boost::numeric::ublas::vector<double> &weights);

    void setFunctionAct(double (*functionAct)(double));
};


#endif //PERCEPTRON_NEURON_HPP
