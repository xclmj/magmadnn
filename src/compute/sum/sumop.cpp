/**
 * @file sumop.cpp
 * @author Daniel Nichols
 * @version 0.1
 * @date 2019-05-20
 * 
 * @copyright Copyright (c) 2019
 */
#include "compute/sum/sumop.h"

namespace magmadnn {
namespace op {

template <typename T>
SumOp<T>::SumOp(std::vector<Operation<T> *> ops, bool copy) : Operation<T>::Operation(ops), ops(ops), copy(copy) {
    if (ops.empty()) return;

    if (copy) {
        ret = new Tensor<T> (ops.at(0)->get_output_shape(), {ZERO, {}}, ops.at(0)->get_memory_type());
    } else {
        std::fprintf(stderr, "no_copy sum not supported yet.\n");
    }
}

template <typename T>
Tensor<T> *SumOp<T>::eval() {
    std::vector<Tensor<T> *> vals (ops.size());

    for (unsigned int i = 0; i < ops.size(); i++) {
        vals[i] = ops[i]->eval();
    }

    assert( ret != NULL );
    internal::sum_full(vals, *ret);
    
    return ret;
}

template <typename T>
std::string SumOp<T>::to_string() {
    std::string ret = "(";
    for (typename std::vector<Operation<T> *>::iterator vit = this->ops.begin(); vit != this->ops.end(); vit++) {
        if (vit != ops.begin()) {
            ret += "+";
        }
        ret += " " + (*vit)->to_string() + " ";
    }
    return ret + ")";
}

template class SumOp<int>;
template class SumOp<float>;
template class SumOp<double>;

template <typename T>
Operation<T> *sum(std::vector<Operation<T> *> ops, bool copy) {
    return new SumOp<T> (ops, copy);
}
template Operation<int> *sum(std::vector<Operation<int> *> ops, bool copy);
template Operation<float> *sum(std::vector<Operation<float> *> ops, bool copy);
template Operation<double> *sum(std::vector<Operation<double> *> ops, bool copy);

}   // namespace op
}   // namespace magmadnn