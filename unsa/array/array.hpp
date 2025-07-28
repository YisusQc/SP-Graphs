#ifndef UNSA_ARRAY_HPP
#define UNSA_ARRAY_HPP

#include <cstddef>      // std::size_t
#include <utility>      // std::swap
#include <type_traits>  // std::is_nothrow_swappable

namespace unsa {

/**
 * @brief Clase plantilla que implementa un array de tamaño fijo.
 * 
 * Proporciona una interfaz similar a std::array con acceso seguro y eficiente a
 * elementos en tiempo constante. El tamaño se define en tiempo de compilación.
 * 
 * @tparam T Tipo de los elementos almacenados.
 * @tparam N Número fijo de elementos en el array.
 */
template <typename T, std::size_t N>
class Array {
public:
    // ===== Alias de tipos para compatibilidad y conveniencia =====
    using value_type = T;                 ///< Tipo de los elementos
    using size_type = std::size_t;       ///< Tipo para índices y tamaños
    using reference = value_type&;       ///< Referencia mutable a un elemento
    using const_reference = const value_type&; ///< Referencia constante a un elemento
    using pointer = value_type*;         ///< Puntero mutable a elementos
    using const_pointer = const value_type*; ///< Puntero constante a elementos

    using iterator = pointer;             ///< Iterador mutable (puntero)
    using const_iterator = const_pointer;///< Iterador constante (puntero)

    // ===== Métodos de acceso con comprobación y sin ella =====

    /**
     * @brief Accede al elemento en la posición `pos` con verificación de rango.
     * 
     * @param pos Índice del elemento (debe ser menor que size()).
     * @return Referencia al elemento en `pos`.
     * @throws std::out_of_range Si `pos` está fuera del rango válido.
     */
    constexpr reference at(size_type pos);

    /**
     * @brief Versión constante de at().
     */
    constexpr const_reference at(size_type pos) const;

    /**
     * @brief Acceso sin comprobación al elemento en `pos`.
     * 
     * Similar al operador [] de los arrays C. Comportamiento indefinido
     * si `pos` está fuera de rango.
     * 
     * @param pos Índice del elemento.
     * @return Referencia al elemento en `pos`.
     */
    constexpr reference operator[](size_type pos) noexcept;

    /**
     * @brief Versión constante del operador [].
     */
    constexpr const_reference operator[](size_type pos) const noexcept;

    /**
     * @brief Obtiene una referencia al primer elemento.
     * 
     * Comportamiento indefinido si el array está vacío (N == 0).
     * 
     * @return Referencia al primer elemento.
     */
    constexpr reference front() noexcept;

    /**
     * @brief Versión constante de front().
     */
    constexpr const_reference front() const noexcept;

    /**
     * @brief Obtiene una referencia al último elemento.
     * 
     * Comportamiento indefinido si el array está vacío (N == 0).
     * 
     * @return Referencia al último elemento.
     */
    constexpr reference back() noexcept;

    /**
     * @brief Versión constante de back().
     */
    constexpr const_reference back() const noexcept;

    /**
     * @brief Obtiene un puntero al buffer interno del array.
     * 
     * Útil para interoperabilidad con APIs que requieren punteros nativos.
     * 
     * @return Puntero al primer elemento.
     */
    constexpr pointer data() noexcept;

    /**
     * @brief Versión constante de data().
     */
    constexpr const_pointer data() const noexcept;

    // ===== Iteradores simples =====

    /**
     * @brief Iterador al inicio del array.
     * 
     * Permite iterar desde el primer elemento.
     * 
     * @return Iterador apuntando al primer elemento.
     */
    constexpr iterator begin() noexcept;

    /**
     * @brief Iterador constante al inicio.
     */
    constexpr const_iterator begin() const noexcept;

    /**
     * @brief Iterador al final del array (uno más allá del último elemento).
     * 
     * Permite iterar hasta el final.
     * 
     * @return Iterador apuntando al final.
     */
    constexpr iterator end() noexcept;

    /**
     * @brief Iterador constante al final.
     */
    constexpr const_iterator end() const noexcept;

    // ===== Capacidad =====

    /**
     * @brief Retorna el tamaño fijo del array.
     * 
     * @return Número de elementos (constante en tiempo de compilación).
     */
    constexpr size_type size() const noexcept;

    /**
     * @brief Indica si el array está vacío (solo si N == 0).
     * 
     * @return true si está vacío, false en caso contrario.
     */
    constexpr bool empty() const noexcept;

    // ===== Utilidades =====

    /**
     * @brief Llena todos los elementos con un valor dado.
     * 
     * Ejecuta std::fill_n sobre el buffer interno.
     * 
     * @param value Valor con el que rellenar el array.
     */
    void fill(const T& value);

    /**
     * @brief Intercambia el contenido con otro array del mismo tipo y tamaño.
     * 
     * Usa std::swap_ranges internamente y garantiza no lanzar excepciones
     * si el tipo T es no-throw swappable.
     * 
     * @param other Array con el que intercambiar contenidos.
     */
    void swap(Array& other) noexcept(std::is_nothrow_swappable<T>::value);

private:
    T elems[N > 0 ? N : 1]; ///< Almacenamiento interno contiguo.
};

/**
 * @brief Función auxiliar para obtener la referencia al elemento en índice
 * de tiempo de compilación `I`.
 * 
 * Equivalente a std::get<I> para std::array.
 * 
 * @tparam I Índice del elemento a obtener (debe ser menor que N).
 * @tparam T Tipo de elementos.
 * @tparam N Tamaño del array.
 * @param a Array del que obtener el elemento.
 * @return Referencia al elemento en índice `I`.
 */
template <std::size_t I, typename T, std::size_t N>
constexpr T& get(Array<T, N>& a) noexcept;

/**
 * @brief Versión constante de get<I>().
 */
template <std::size_t I, typename T, std::size_t N>
constexpr const T& get(const Array<T, N>& a) noexcept;

} // namespace unsa

#include "array.tpp"  // Implementación en archivo separado

#endif // UNSA_ARRAY_HPP
