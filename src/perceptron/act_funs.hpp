//
// Created by sam on 13/12/17.
//

#ifndef PERCEPTRON_ACT_FUNS_HPP
#define PERCEPTRON_ACT_FUNS_HPP

#include <cmath>

namespace act_f {

/**
 * function sigmoide
 * @tparam type
 * @param e
 * @return
 */
    template<typename type>
    type sigmoide(type e) {
        return 1 / (1 + exp(-e));
    };


    /**
     * function sup to 0
     * @tparam type
     * @param x
     * @return 1 is x is sup to 0
     */
    template<typename type>
    type supTo0(type x) {
        return x > 0 ? 1 : 0;
    };

    template<typename type>
    type supToY(type x, type y) {
        return x > 256. / 2. ? 1 : 0;
    }

    template<typename type>
    type noActFun(type x) {
        return x;
    }
}


#endif //PERCEPTRON_ACT_FUNS_HPP
