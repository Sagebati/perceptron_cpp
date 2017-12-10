#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operations.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <random>
#include "reader.hpp"
#include "PerceptronMonoLayer.hpp"

using namespace cv;
using namespace boost::numeric;
using namespace std;


void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix);

void randomizeVector(boost::numeric::ublas::vector<double> &vect);

double (*sigmoide)(double) = [](double x) {
    return 1 / (1 + exp(-x));
};

double supa0(double x) {
    return x > 0 ? 1 : 0;
};

double sup255(double x ){
    return x > 256./2. ? 1:0;
}

double (*seuil)(double) = supa0;


ublas::vector<double> *imageToVector(cv::Mat const &mat, size_t const nbrPixels) {
    auto *v = new ublas::vector<double>(nbrPixels);
    for (size_t i = 0; i < nbrPixels; i++) {
        auto a = (double) mat.at<unsigned char>(i);
        a = a>0?1:0;
        v->insert_element(i, a);
    }
    return v;
}

int main() {
    using namespace boost::numeric::ublas;

    string filename = "res/train-images-idx3-ubyte";
    size_t image_size = 28 * 28;

    std::vector<cv::Mat> vec_entrees;
    std::vector<double> vec_labels;
    std::vector<cv::Mat> vec_entrees_test;
    std::vector<double> vec_labels_test;
    read_Mnist(filename, vec_entrees);
    read_Mnist_Label("res/train-labels-idx1-ubyte", vec_labels);
    read_Mnist("res/t10k-images-idx3-ubyte", vec_entrees_test);
    read_Mnist_Label("res/t10k-labels-idx1-ubyte", vec_labels_test);

//    cout<<vec_entrees.size()<<endl;
//    cv::imshow("1st", vec_entrees[0]);
//    cv::waitKey();

    std::vector<Image> vecteurEntres;
    for (cv::Mat &m : vec_entrees) {
        Image image = {&m, imageToVector(m, image_size)};
        vecteurEntres.push_back(image);
    }
    std::vector<Image> vecteurEnTest;
    for (cv::Mat &m : vec_entrees_test) {
        Image image = {&m, imageToVector(m, image_size)};
        vecteurEnTest.push_back(image);
    }
//    cout << *vecteurEntres[0].e << endl;



    auto *neuronnes = new std::vector<Neuron>;
    for (int i = 0; i < 10; ++i) {
        ublas::vector<double> weigthN(image_size);
        randomizeVector(weigthN);
        neuronnes->emplace_back(weigthN, seuil);
    }


    PerceptronMonoLayer perceptronMonoLayer(*neuronnes, vecteurEntres, vec_labels);
    perceptronMonoLayer.learn();
    cout << "Fini d'learn" << endl;
    cout << "lancement du test" << endl;
    perceptronMonoLayer.test(vecteurEnTest, vec_labels_test);

    for (Image toDel : vecteurEntres) {
        delete (toDel.e);
    }

    cv::Mat imageTest = imread("res/test.png",CV_LOAD_IMAGE_GRAYSCALE);

    Image im = {&imageTest,imageToVector(imageTest,image_size)};

    cout << "Essai perso (6):" <<
         perceptronMonoLayer.test(im, 6.) << endl;


    delete (neuronnes);


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


