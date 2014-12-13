/*
 * Implementation of a resizable array that support.
 */

#ifndef LED_ANIM_ARRAY_H
#define LED_ANIM_ARRAY_H

#include <stdint.h>
#include <Arduino.h>

template<typename T>
class Array {
private:
    T * contents;
    int count;
    int capacity;
public:
    Array();
    Array(uint16_t initCapacity);
    ~Array();

    /* Adds item to the end of the array. */
    void append(const T item);

    /* Inserts item at the i-th slot of the array. */
    void insert(uint16_t index, const T item);

    /* Returns the i-th element from the array, or NULL if invalid. */
    T get(uint16_t index);

    /* Removes the i-th element from the array. Returns null if invalid. */
    T remove(uint16_t index);

    /* Returns the number of items in the array */
    uint16_t size() const;

    void print();
private:
    /* Resizes the array */
    void resize(const uint16_t newCapacity);

    void exit(const char* message) const;
};

#define DEFAULT_SIZE 8
#define MIN_SIZE 4

template<typename T>
Array<T>::Array() {
    contents = (T *) malloc(sizeof(T) * DEFAULT_SIZE);
    if (!contents) {
        exit("Allocation failed");
    }
    count = 0;
    capacity = DEFAULT_SIZE;
}

template<typename T>
Array<T>::Array(uint16_t initCapacity) {
    contents = (T *) malloc(sizeof(T) * initCapacity);
    if (!contents) {
        exit("Allocation failed");
    }
    count = 0;
    capacity = initCapacity;
}

template<typename T>
Array<T>::~Array() {
    free(contents);
}

template<typename T>
void Array<T>::append(const T item) {
    if (count == capacity) {
        resize(2 * capacity);
    }
    contents[count] = item;
    count++;
}

template<typename T>
void Array<T>::insert(uint16_t index, const T item) {
    if (index <= count) {
        if (count == capacity) {
            resize(2 * capacity);
        }
        uint16_t numAfter = count - index;
        if (numAfter > 0) {
            memmove(contents + index + 1, contents + index, sizeof(T) * numAfter); 
        }
        contents[index] = item;
        count++;
    }
}

template<typename T>
T Array<T>::get(uint16_t index) {
    if (index < count) {
        return contents[index];
    } else {
        return NULL;
    }
}

template<typename T>
T Array<T>::remove(uint16_t index) {
    if (index < count) {
        T value = contents[index];
        uint16_t numAfter = count - index - 1;
        if (numAfter > 0) {
            memmove(contents + index, contents + index + 1, sizeof(T) * numAfter); 
        }
        count--;
        return value;
    } else {
        return NULL;
    }
}

template<typename T>
uint16_t Array<T>::size() const {
    return count;
}

template<typename T>
void Array<T>::print() {
    for (int i = 0; i < count; ++i) {
        Serial.print(contents[i]);
        Serial.print(" ");
    }
    Serial.print("\n");
}

template<typename T>
void Array<T>::resize(const uint16_t newCapacity) {
    contents = (T* ) realloc(contents, sizeof(T) * newCapacity);
    if (!contents) {
        exit("Allocation failed");
    }
    capacity = newCapacity;
}

template<typename T>
void Array<T>::exit(const char* message) const {
    Serial.print("Error: ");
    Serial.print(message);
    Serial.print("\n");
}

#undef DEFAULT_SIZE
#undef MIN_SIZE

#endif