#ifndef MAP_H
#define MAP_H
template <class K, class V>
class Map {
private:
    K* keys;
    V* values;
    int capacity;
    int size;

    void resize();

public:
    Map();
    ~Map();

    void insert(const K& key, const V& value);
    V& operator[](const K& key);
    bool get(const K& key, V& value) const;
    bool erase(const K& key);
    int getSize() const;
    bool isEmpty() const;
    void clear();
};
#endif
