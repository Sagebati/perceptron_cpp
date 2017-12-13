#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operations.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <random>
#include "mnist/reader.hpp"
#include "perceptron/PerceptronMonoLayer.hpp"
#include "perceptron/act_funs.hpp"
#include "perceptron/ItemNN.hpp"

using namespace cv;
using namespace boost;
using namespace boost::numeric;
using namespace std;


void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix);

void randomizeVector(boost::numeric::ublas::vector<double> &vect);


ublas::vector<double> imageToVector(cv::Mat const &mat) {
    size_t nbPixels = mat.rows * mat.cols;
    ublas::vector<double> v(nbPixels);
    for (size_t i = 0; i < nbPixels; i++) {
        auto a = (double) mat.at<unsigned char>(i);
        v.insert_element(i, a>(255./2.)?1:0);
    }
    return v;
}

int main() {

    using namespace boost::numeric::ublas;

    double (*seuil)(double) = act_f::noActFun<double>;


    string filename = "../res/train-images-idx3-ubyte";
    size_t image_size = 28 * 28;

    std::vector<cv::Mat> vec_entrees;
    std::vector<double> vec_labels;
    std::vector<cv::Mat> vec_entrees_test;
    std::vector<double> vec_labels_test;
    read_Mnist(filename, vec_entrees);
    read_Mnist_Label("../res/train-labels-idx1-ubyte", vec_labels);
    read_Mnist("../res/t10k-images-idx3-ubyte", vec_entrees_test);
    read_Mnist_Label("../res/t10k-labels-idx1-ubyte", vec_labels_test);

    std::vector<ItemNN<double>> vec_train;
    for (int i = 0; i < vec_entrees.size(); ++i) {
        vec_train.emplace_back(vec_labels[i], vec_entrees[i], imageToVector);
    }
    vec_entrees.clear();
    vec_labels.clear();
    std::vector<ItemNN<double>> vec_test;
    for (int i = 0; i < vec_entrees_test.size(); ++i) {
        vec_test.emplace_back(vec_labels_test[i], vec_entrees_test[i], imageToVector);
    }
    vec_entrees_test.clear();
    vec_labels_test.clear();

    auto *neuronnes = new std::vector<Neuron>;
    for (int i = 0; i < 10; ++i) {
        ublas::vector<double> weigthN(image_size);
        randomizeVector(weigthN);
        neuronnes->emplace_back(weigthN, seuil);
    }


    PerceptronMonoLayer perceptronMonoLayer(*neuronnes);
    perceptronMonoLayer.learn(vec_train,10);
    cout << "Fini d'learn" << endl;
    cout << "lancement du test" << endl;
    perceptronMonoLayer.test(vec_test);


    cv::Mat imageTest = imread("../res/test.png",CV_LOAD_IMAGE_GRAYSCALE);

    ItemNN<double> itemNN(5,imageTest,imageToVector);

    cout << "Essai perso (5):" <<(
         perceptronMonoLayer.test(itemNN)? "true":"false") << endl;


    return 0;
}

/**
 * Générateur de droite 2D on lui passe un vecteur, et une valuer
 * et il retourne la valeur en fonction du vecteur
 * @param vecDroite
 * @param x
 * @return
 */
double f(vector<double> vecDroite, double x) { //vecteur
    return (vecDroite[1] * x) / -vecDroite[2];
};

/**
 * Fonction qui permet d'initialiser une matrice a des poids aléatoires
 * entre -1 et 1
 * @param vector à initialiser
 */
void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1, 1);

    for (size_t i = 0; i < matrix.size1(); i++) {
        for (size_t j = 0; j < matrix.size2(); j++) {
            matrix(i, j) = dist(mt);
        }
    }
}

/**
 * Fonction qui permet d'initialiser un vecteur a des poids aléatoires
 * entre -1 et 1
 * @param vect à initialiser
 */
void randomizeVector(boost::numeric::ublas::vector<double> &vect) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    for (size_t i = 0; i < vect.size(); i++) {
        vect(i) = dist(mt);
    }
}


