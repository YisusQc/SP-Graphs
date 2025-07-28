#ifndef UNSA_LINKED_LIST_HPP
#define UNSA_LINKED_LIST_HPP

#include <cstddef>     // std::size_t
#include <iterator>    // std::forward_iterator_tag

namespace unsa {

/**
 * @brief Implementación de una lista simplemente enlazada genérica.
 * 
 * Clase plantilla que representa una estructura de datos lineal donde los 
 * elementos se almacenan en nodos enlazados dinámicamente.
 * 
 * @tparam T Tipo de dato que almacenará la lista.
 */
template <typename T>
class LinkedList {
private:
    // Estructura interna para representar un nodo de la lista
    struct Node;

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    /**
     * @brief Iterador que permite recorrer la lista.
     * Cumple con los requisitos de un ForwardIterator.
     */
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* ptr);
        reference operator*() const;
        Iterator& operator++();     // Pre-incremento
        Iterator operator++(int);   // Post-incremento
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* current;
    };

    // === Constructores / operador de asignación ===
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;

    // === Métodos de modificación ===

    /**
     * @brief Inserta un elemento al inicio de la lista.
     * @param value Elemento a insertar (por copia).
     */
    void push_front(const T& value);

    /**
     * @brief Inserta un elemento al final de la lista.
     * @param value Elemento a insertar (por copia).
     */
    void push_back(const T& value);

    /**
     * @brief Elimina el primer elemento de la lista.
     * @throws std::out_of_range si la lista está vacía.
     */
    void pop_front();

    /**
     * @brief Elimina el último elemento de la lista.
     * @throws std::out_of_range si la lista está vacía.
     */
    void pop_back();

    // === Acceso ===

    reference front();             ///< Devuelve referencia al primer elemento.
    const_reference front() const;///< Versión constante de front().
    reference back();              ///< Devuelve referencia al último elemento.
    const_reference back() const; ///< Versión constante de back().

    // === Información ===

    bool empty() const noexcept;     ///< Retorna true si la lista está vacía.
    size_type size() const noexcept; ///< Retorna la cantidad de elementos.

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    void clear();

    // === Iteradores ===

    Iterator begin() noexcept; ///< Iterador al primer elemento.
    Iterator end() noexcept;   ///< Iterador al final (nullptr).

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr);
    };

    Node* head;   ///< Puntero al primer nodo.
    Node* tail;   ///< Puntero al último nodo.
    size_type count; ///< Número de elementos.

    void copy_from(const LinkedList& other); ///< Copia todos los nodos desde otra lista.
};

} // namespace unsa

#include "linked_list.tpp"

#endif // UNSA_LINKED_LIST_HPP
