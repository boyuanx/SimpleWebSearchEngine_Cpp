//
// Created by Boyuan Xu on 3/31/18.
//

#ifndef HW4_UPDATED_SETUTILITY_H
#define HW4_UPDATED_SETUTILITY_H
#include <iostream>
#include <set>

template <typename T>
std::set<T> unionSet(std::set<T>& lhs, std::set<T>& rhs) {
    std::set<T> sum;
    for (typename std::set<T>::iterator it = lhs.begin(); it != lhs.end(); it++) {
        sum.insert(*it);
    }
    for (typename std::set<T>::iterator it = rhs.begin(); it != rhs.end(); it++) {
        sum.insert(*it);
    }
    return sum;
}

template <typename T>
std::set<T> intersectSet(std::set<T>& lhs, std::set<T>& rhs) {
    std::set<T> intersect;
    for (typename std::set<T>::iterator it = lhs.begin(); it != lhs.end(); it++) {
        if (rhs.count((*it))) {
            intersect.insert(*it);
        }
    }
    return intersect;
}

#endif //HW4_UPDATED_SETUTILITY_H
