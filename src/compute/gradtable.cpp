/**
 * @file gradtable.cpp
 * @author Daniel Nichols
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright (c) 2019
 */
#include "compute/gradtable.h"

namespace magmadnn {
namespace op {


template <typename T>
GradTable<T>::GradTable() {
    // init
}

template <typename T>
unsigned int GradTable<T>::get_size() {
    return _table.size();
}

template <typename T>
Operation<T>* GradTable<T>::get(Variable<T> *var) {
    tmp_map_iterator = _table.find(var->get_name());

    // return NULL if not found
    if (tmp_map_iterator == _table.end()) {
        return (Operation<T> *) NULL;
    }

    return tmp_map_iterator->second;
}

template <typename T>
void GradTable<T>::set(Variable<T> *var, Operation<T> *grad) {
    if (var == NULL) return;

    _table[var->get_name()] = grad;
    
}


template class GradTable<int>;
template class GradTable<float>;
template class GradTable<double>;

}   // namespace op
}   // namespace magmadnn