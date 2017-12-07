//
// Created by sam on 04/12/17.
//
#


#include "Neuron.hpp"

using namespace boost::numeric;

Neuron::Neuron(const ublas::vector<double> &weights, double (*functionAct)(double)) : weights(weights),
                                                                                      functionAct(functionAct) { this->gradient = 0.5; }

/**
 * function that gives the output of the neuron oa entry given
 * @param e vecotr of entrie
 * @return the output
 */
double Neuron::getOutput(boost::numeric::ublas::vector<double> const &e) {
    if (weights.size() != e.size()) {
        std::cerr << "Problem Neuron.getOutput"
                  << " size weigths : " << weights.size()
                  << " size entri : " << e.size()
                  << std::endl;
    }
    double somme_pond = ublas::inner_prod(weights, e);
    return somme_pond / weights.size();
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

/**
 * Function that correct weigth
 * @param e entries
 * @param result result
 * @param expected result expected
 */
void Neuron::correctWeitghs(ublas::vector<double> const &e, double const result, double const expected) {
    if (weights.size() != e.size()) {
        std::cout << "problem ici" << std::endl;
    }
    auto hey = weights + (e * (this->gradient * (expected - result)));
//    std::cout<<" "<<(hey == weights)<<" "<<std::endl;
    this->setWeights(weights + (e * (this->gradient * (expected - result))));
}
