//
// Created by sam on 04/12/17.
//
#
#include "Neuron.hpp"

using namespace boost::numeric;

Neuron::Neuron(const ublas::vector<double> &weights, double (*functionAct)(double)) : weights(weights),
                                                                                      functionAct(functionAct) { this->gradient = 0.05; }

double Neuron::getOutput(boost::numeric::ublas::vector<double> const &e) {
    if (weights.size() != e.size()) {
        std::cerr << "Problem Neuron.getOutput"
                  << " size weigths : " << weights.size()
                  << " size entri : " << e.size()
                  << std::endl;
    }
    double somme_pond = ublas::inner_prod(weights, e);
    return functionAct(somme_pond / e.size());
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

void Neuron::correctWeitghs(ublas::vector<double> const &e, double const result, double const expected) {
    if (weights.size() != e.size()) {
        std::cout << "problem ici" << std::endl;
    }
    weights = weights + (e * (this->gradient * (expected - result)));
}
