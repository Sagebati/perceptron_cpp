//
// Created by sam on 11/12/17.
//

#ifndef PERCEPTRON_ITEMNN_HPP
#define PERCEPTRON_ITEMNN_HPP

#include <boost/numeric/ublas/vector.hpp>
#include <opencv2/core.hpp>

template<typename typeEntry>
class ItemNN {
private:
    /**
     * vector who contains all the set of the image
     */
    std::vector<boost::numeric::ublas::vector<typeEntry>> entries;
    cv::Mat const mat_image;
    typeEntry const expected;

    boost::numeric::ublas::vector<typeEntry> (*f_itemToVec)(const cv::Mat &);

public:
    ItemNN(const double expected, const cv::Mat item, boost::numeric::ublas::vector<typeEntry> (*f_itemToVec)(const cv::Mat &)):expected( expected), mat_image(item), f_itemToVec(f_itemToVec) {
        entries.push_back(f_itemToVec(item));
        //To present to the perceptron the images in all the orientations size uncomment this
//        for (int i = 0; i < 3; ++i) {
//            cv::Mat dst;
//            cv::rotate(item, dst, cv::ROTATE_90_CLOCKWISE + 1);
//            entries.push_back(f_itemToVec(dst));
//        }
//        cv::Mat dst;
//        cv::flip(item, dst, 1);
//        entries.push_back(f_itemToVec(dst));
    };

    /**
     * function that return the image without bieng rotated or flipped
     * @return the vector of elements
     */
    const boost::numeric::ublas::vector<typeEntry> &getEntry() const {
        return entries[0];
    }
    const cv::Mat &getItem() const {
        return mat_image;
    }
    const std::vector<boost::numeric::ublas::vector<typeEntry>> &getVecEntries() const {
        return this->entries;
    }

    typeEntry const getExpected() const {
        return expected;
    }
};

#endif //PERCEPTRON_ITEMNN_HPP
