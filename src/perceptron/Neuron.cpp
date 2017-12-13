//
// Created by sam on 04/12/17.
//
#


#include "Neuron.hpp"

using namespace boost::numeric;

Neuron::Neuron(const ublas::vector<double> &weights, double (*functionAct)(double)) : weights(weights),
                                                                                      functionAct(functionAct) { this->gradient = 0.05; }

/**
 * function that gives the output of the neuron on entry given
 * @param entries vector of entries
 * @return the output
 */
double Neuron::getOutput(boost::numeric::ublas::vector<double> const &entries) {
    if (weights.size() != entries.size()) {
        std::cerr << "Problem Neuron.getOutput"
                  << " size weigths : " << weights.size()
                  << " size entri : " << entries.size()
                  << std::endl;
    }
    double somme_pond = ublas::inner_prod(weights, entries);

    return functionAct(somme_pond/weights.size());
}


const ublas::vector<double> &Neuron::getWeights() const {
    return weights;
}

void Neuron::setWeights(const ublas::vector<double> &weights) {
    Neuron::weights = weights;
}


void Neuron::setFunctionAct(double (*functionAct)(double)) {
    Neuron::functionAct = functionAct;
}

bool equalsBlas(ublas::vector<double> const &a, ublas::vector<double> const &b) {
    auto res = true;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            res = false;
        }
    }
    return res;
}

/**
 * Function that correct weigths
 * @param e entries
 * @param result result
 * @param expected result expected
 */
void Neuron::correctWeitghs(ublas::vector<double> const &e, double const expected, double const result) {
    if (weights.size() != e.size()) {
        std::cout << "problem ici" << std::endl;
    }
    this->setWeights(weights + (e * (this->gradient * (expected - result))));
}



