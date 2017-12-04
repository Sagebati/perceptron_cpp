#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <cmath>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operations.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <random>
#include "reader.hpp"
#include "NeuralNetwork.hpp"

using namespace cv;
using namespace boost::numeric;
using namespace std;



void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix);

double (*sigmoide)(double) = [](double x){
    return 1/(1+exp(-x));
};

double (*seuil)(double) = sigmoide;



ublas::vector<double>* imageToVector(cv::Mat const &mat, size_t const nbrPixels){
    ublas::vector<double> * v = new ublas::vector<double>(nbrPixels);
    for(size_t i=0;i<nbrPixels;i++){
        v->insert_element(i,(double)mat.at<unsigned char>(i));
    }
    return v;
}

int main() {
    using namespace boost::numeric::ublas;

    string filename = "res/train-images-idx3-ubyte";
    int number_of_images = 10000;
    int image_size = 28 * 28;

    //read MNIST iamge into OpenCV Mat vector
    std::vector<cv::Mat> vec;
    read_Mnist(filename, vec);
    std::vector<double> vec_labels;
    read_Mnist_Label("res/train-labels-idx1-ubyte", vec_labels);

//    cout<<vec.size()<<endl;
//    cv::imshow("1st", vec[0]);
//    cv::waitKey();


    NeuralNetwork nn(image_size,0,9,sigmoide);
    std::vector<ublas::vector<double>*> vecteurEntres;
    for(cv::Mat m : vec){
        vecteurEntres.push_back(imageToVector(m,image_size));
    }
    cout<<*vecteurEntres[0]<<endl;
//    cout<<"[";
//    for(double const &item:vec_labels ){
//        cout<<item<<",";
//    }
//    cout<<"]"<<endl;
    for (ublas::vector<double> *e : vecteurEntres){
        cout<<nn.propager(*e)<<endl;
    }



    return 0;
}

/**
 * Générateur de droite 2D on lui passe un vecteur, et une valuer
 * et il retourne la valeur en fonction du vecteur
 * @param vecDroite
 * @param x
 * @return
 */
double f(vector<double> vecDroite, double x){ //vecteur
    return (vecDroite[1]*x)/-vecDroite[2];
};

/**
 * Fonction qui permet d'initialiser une matrice a des poids aléatoires
 * entre -1 et 1
 * @param vector à initialiser
 */
void randomizeMatrix(boost::numeric::ublas::matrix<double> &matrix){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1,1);

    for(size_t i=0;i<matrix.size1();i++){
        for(size_t j=0;j<matrix.size2();j++){
            matrix(i,j) = dist(mt);
        }
    }
}


