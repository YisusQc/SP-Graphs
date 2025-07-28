#ifndef UNSA_MIN_HEAP_HPP
#define UNSA_MIN_HEAP_HPP

#include <vector>
#include <cstddef>  // std::size_t
#include <stdexcept>

namespace unsa {

/**
 * @brief Estructura de datos MinHeap (montículo mínimo).
 * 
 * Representa una cola de prioridad donde el menor elemento siempre está en el tope.
 * Internamente utiliza un vector para almacenar los elementos en forma de árbol binario.
 * 
 * @tparam T Tipo de elementos almacenados (debe ser comparable con <).
 */
template <typename T>
class MinHeap {
public:
    using value_type = T;
    using size_type = std::size_t;

    // Constructor por defecto
    MinHeap();

    // Inserta un elemento en el heap
    void push(const T& value);

    // Elimina el elemento mínimo
    void pop();

    // Accede al mínimo sin eliminarlo
    const T& top() const;

    // Retorna true si el heap está vacío
    bool empty() const noexcept;

    // Retorna el número de elementos almacenados
    size_type size() const noexcept;

    // Elimina todos los elementos
    void clear();

private:
    std::vector<T> data;

    // Reorganiza hacia arriba el último elemento insertado
    void heapify_up(size_type index);

    // Reorganiza hacia abajo desde el tope
    void heapify_down(size_type index);

    // Calcula índice del padre
    size_type parent(size_type index) const;

    // Índices de hijos izquierdo y derecho
    size_type left(size_type index) const;
    size_type right(size_type index) const;
};

} // namespace unsa

#include "min_heap.tpp"

#endif // UNSA_MIN_HEAP_HPP
