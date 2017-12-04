//
// Created by sam on 28/11/17.
//

#include "NeuralNetwork.hpp"
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric;
using namespace std;

/**
 * Primary constructor
 */
NeuralNetwork::NeuralNetwork(const size_t nbrNeuronnes, const size_t couches, const size_t nbrNeuronnesOutput, double (*funSeuil)(double)) {
    for (int i = 0; i < couches; ++i) {
        this->neuralNetwork.push_back(new ublas::matrix<double>(nbrNeuronnes, nbrNeuronnes));
    }
    this->neuralNetwork.push_back(new ublas::matrix<double>(nbrNeuronnes, nbrNeuronnesOutput));
    this->fonctSeuil = funSeuil;
    for (ublas::matrix<double> *m : neuralNetwork)
        NeuralNetwork::initMatrix(*m);
}
/**
 * Copy constructor
 * @param nn
 */
NeuralNetwork::NeuralNetwork(const NeuralNetwork &nn) {
    for (int i = 0; i < nn.neuralNetwork.size(); ++i) {
        this->neuralNetwork.push_back(new ublas::matrix<double>(*nn.neuralNetwork[i]));
    }
    this->neuralNetwork.push_back(new ublas::matrix<double>(**nn.neuralNetwork.end()));
    this->fonctSeuil = nn.fonctSeuil;
}

/**
 * Destructor
 */
NeuralNetwork::~NeuralNetwork() {
    for (ublas::matrix<double> *&i : neuralNetwork) {
        delete (i);
    }
}
/**
 *Fais fonctionner le reseau avec une entrée donnée
 */
ublas::vector<double>
NeuralNetwork::propager(const ublas::vector<double> &e) {
    // vecteur double qui contient les valeurs des entrées
    ublas::vector<double> buff = e;

    for (ublas::matrix<double> *&i : neuralNetwork) {//pour chaque couche de la matrice
        buff = propagerEtape(buff, *i);
    }
    return buff;
}

boost::numeric::ublas::vector<double>
NeuralNetwork::propagerEtape(const ublas::vector<double> &e, const ublas::matrix<double> &w) {
    if (e.size() != w.size2()) {
//        cerr<<"pas la même taille taille vecteur e:"<<e.size()<<" taille matrice: "<<w.size1()<<","<<w.size2()<<endl;
    }
    ublas::vector<double> e2 = ublas::prod(ublas::trans(w), e); //produit de la matrice des poids tranformé et de l'entrée
    for (auto &&item  :e2) {
        item = this->fonctSeuil(item);
    }
    return e2;
}

void NeuralNetwork::initMatrix(){
    initMatrix(0.5);
}

void NeuralNetwork::initMatrix(double init) {
    for (ublas::matrix<double> *item : neuralNetwork) {
        for(size_t i=0;i<item->size1();i++){
            for (size_t j = 0; j < item->size2(); ++j) {
                item->insert_element(i,j,init);
            }
        }
    }
}

void NeuralNetwork::propagerErreur(boost::numeric::ublas::vector<double> sortie, double target) {
    double gradient = 0.05;
    //TODO à implementer
}





