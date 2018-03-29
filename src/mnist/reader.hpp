//
// Created by sam on 27/11/17.
//

#ifndef PERCEPTRON_READER_HPP
#define PERCEPTRON_READER_HPP


int ReverseInt(int i);

void read_Mnist(std::string const &filename, std::vector<std::vector<double> > &vec);

void read_Mnist(std::string const &filename, std::vector<cv::Mat> &vec);

void read_Mnist_Label(std::string const &filename, std::vector<double> &vec);

#endif //PERCEPTRON_READER_HPP
