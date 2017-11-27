#include <iostream>
#include<boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <random>
#include <map>

using namespace boost::numeric::ublas;

struct Pair{
    vector<double> point;
    int resEspected;
};

void randomizeVector(boost::numeric::ublas::vector<double> &vector);
vector<double> computeeNewWeight(vector<double> w,double n,int (*fSeuil)(double),vector<double> x);
double* funcPerc();

int main() {

    double* hey = funcPerc();
    for(int i=0;i<3;i++){
        std::cout<<*(hey+i)<<std::endl;
    }
    delete(hey);
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

double* funcPerc(){

    std::vector<Pair> ensApprentissage;


    int (*seuil)(vector<double>,vector<double>)= [](vector<double> w,vector<double> point) {
        return point[1] - f(w,point[0])<0? -1:1; // si le point est au dessus on renvoie 1
    };

    int (*seuilPondere)(double) = [](double n){
        return n > 0? 1:-1;
    };


    double const points[6][2] = {
            {-2,1},
            {1,1},
            {1.5,-0.5},
            {-2,-1},
            {-1,-1.5},
            {2,-2}
    };


    for(int i=0;i<6;i++) {
        if (i < 3) {
            vector<double> v(2);
            v[0] = points[i][0];
            v[1] = points[i][1];
            Pair   ele = {v,1};
            ensApprentissage.push_back(ele);
        }else{
            vector<double> v(2);
            v[0] = points[i][0];
            v[1] = points[i][1];
            Pair  ele = {v,-1};
            ensApprentissage.push_back(ele);
        }
    }

    const double n = 0.2;
    vector<double> w(3);
    int i = 0;
    w[0] = 0;
    w[1] = 1;
    w[2] = 0.5;
 //   randomizeVector(w);

//    std::cout<< seuil(w,ensApprentissage[0].point);

    int nbrBoucles  =0;
    do {
        i=0;
        std::cout<<"nbr boucles:"<<nbrBoucles++<<std::endl;
        for (Pair p : ensApprentissage) {
            vector<double> x = p.point;
            x.resize(3, true);
            x[2] = x[1];
            x[1] = x[0];
            x[0]= 1;
            std::cout<<x<<std::endl;
//            x.insert_element(0, 1);
           std::cout << "w:" << w << " x:" << x << std::endl;
            double sommePond = inner_prod(w, x);
            //std::cout << "some pond:" << sommePond << std::endl;
            int  s = seuil(w,p.point);
//            int s = seuilPondere(sommePond);
            if (s != p.resEspected) {

                w = w + (x * (n * p.resEspected)); // on réajuste le w

            } else {
                i++;
            }
        }
    }while (i!=6);

    double * res = new double[3];
    double * it = res;
    for(double d:w){
        *(it++)=d;
    }
    return res;
}

void randomizeVector(boost::numeric::ublas::vector<double> &vector){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1,1);

    for (double &i : vector) {
        i = dist(mt);
    }
}
