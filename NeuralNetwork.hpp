//
// Created by sam on 28/11/17.
//

#ifndef PERCEPTRON_NEURALNETWORK_HPP
#define PERCEPTRON_NEURALNETWORK_HPP


#include <cstddef>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <random>

class NeuralNetwork {
public:
    /**
     * @param nbrNeuronnes de neuronnes par couche
     * @param couches nbrDecouches dans le reseau
     * @param nbrNeuronnesOutput le nbr de neuronnes dans la couche de sortie
     * @param funSeuil fonction seuil
     */
    NeuralNetwork(size_t nbrNeuronnes, size_t couches, size_t nbrNeuronnesOutput, double(*funSeuil)(double));

    /**
     * Contructor copy
     * @param nn
     */
    NeuralNetwork(const NeuralNetwork &);

    ~NeuralNetwork();

    /**
     * @param e les données d'entrée
     * @return le resultat de la propagation dans le nn
     */
    boost::numeric::ublas::vector<double> propager(const boost::numeric::ublas::vector<double> &e);


private:
    /**
     * vecteur de matrices de poids
     */
    std::vector<boost::numeric::ublas::matrix<double>*> neuralNetwork;

    /**
     * function seuil
     * @return le retour de fontion
     */
    double (*fonctSeuil)(double);

    /**
    * Fonction qui permet d'initialiser une matrice a des poids aléatoires
    * entre -1 et 1
    * @param vector à initialiser
    */
    static void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-1, 1);

        for (size_t i = 0; i < matrix.size1(); i++) {
            for (size_t j = 0; j < matrix.size2(); j++) {
                matrix(i, j) = dist(mt);
            }
        }
    }

    void initMatrix();
    void initMatrix(double init);

    boost::numeric::ublas::vector<double>
    propagerEtape(const boost::numeric::ublas::vector<double> &e,
                  const boost::numeric::ublas::matrix<double> &m);
    void
    propagerErreur(boost::numeric::ublas::vector<double> sortie,double target);
};

#endif //PERCEPTRON_NEURALNETWORK_HPP
