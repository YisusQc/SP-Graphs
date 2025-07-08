#pragma once 
#include <cstddef> // for size_t

template <typename T>
class Vector{
private:
    T* _data;
    int idx=0;
    size_t _capacity;

public:
    Vector(size_t size = 0) : size_(size), data_(new T[size]) {}
    ~Vector() { delete[] _data; }

    void push_back(T _data);
    void pop_back();
    void erase(int index);

    T* begin();
    T* end();
    bool empty() const; 
};

template <typename T>
void Vector<T>::push_back(T data) {
    if (index >= _capacity) {
        T* temp= _data;
        _datta= new T[_capacity * 2];
        for (size_t i = 0; i < _capacity; ++i) {
            _data[i] = temp[i];
        }
        delete[] temp;
        _capacity *= 2;
    }
    _data[index++] = data;
}

template <typename T>
void find(int index, T* p) {}

template <typename T>
void Vector<T>::erase(int index) {
    if(index < 0 || index >= idx) { //Fuera de rango
        return; 
    }
    if (index > 0  && index < idx) {//Caso interno
        --idx;
        _data[index] = 0;

        for (int i = index; i < idx; ++i) {
        _data[i] = _data[i + 1];
        }
    }

    if(idx<capacity / 4) { //Reduccion de capacidad
        T* temp = _data;
        _data = new T[_capacity / 4];
        for (size_t i = 0; i < idx; ++i) {
            _data[i] = temp[i];
        }
        delete[] temp;
        _capacity /= 4;
    }
}

/*
##PLACEMENT AND PARAMETER FUNCTIONS
*/

template <typename T>
T* Vector<T>::begin() {
    return _data;
}   

template <typename T>
T* Vector<T>::end() {
    return _data + idx;
}

template <typename T>
bool Vector<T>::empty() const {
    return idx == 0;
}