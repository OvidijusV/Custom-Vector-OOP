#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <random>
#include <iostream>
#include <memory>
#include <iterator>
#include <utility>
#include <deque>
#include <algorithm>
#include <vector>


template<class T>
class Vector {
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::allocator<T> allocator_type;
    typedef typename std::allocator_traits<allocator_type>::pointer pointer;
    typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    T &at(size_type it) {
        return itt[it];
    }
    reference back() {
        return *(avail - 1);
    }
    T &front() {
        if (avail > 0)
            return itt[0];

        else
            throw std::logic_error("Empty container");
    }
    T *data() noexcept;


    Vector() { create(); }
    Vector(Vector<T>&& v) noexcept : itt(v.itt), avail(v.avail), limit(v.limit) {
        v.swap(*this);
    }
    Vector(std::initializer_list<T> list) { create(list.begin(), list.end()); }
    explicit Vector(size_type n, const T &t = T{}) { create(n, t); }

    Vector(const Vector &v) { create(v.begin(), v.end()); }

    Vector &operator=(const Vector &);
    Vector &operator=(Vector&& other) noexcept {
        if (&other == this) {
            return *this;
        }
        uncreate();
        create(other.begin(), other.end());
        return *this;
    }

    ~Vector() { uncreate(); }

    T &operator[](size_type i) {
        if (i > size() || i < 0)
            throw std::out_of_range("Out of bounds! (operator[])");
        return itt[i];
    }
    const T &operator[](size_type i) const {
        if (i > size() || i < 0)
            throw std::out_of_range("Out of bounds! (operator[])");
        return itt[i];
    }

    size_type max_size() const noexcept;
    size_type size() const { return avail - itt; }
    size_type capacity() const { return limit - itt; }

    iterator begin() { return itt; }
    const_iterator begin() const { return itt; }
    iterator cbegin() { return itt; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(avail); }
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(avail); }
    const_reverse_iterator crbegin() const noexcept { return reverse_iterator(avail); }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }
    iterator cend() { return avail; }

    reverse_iterator rend() noexcept { return reverse_iterator(itt); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(itt); }
    const_reverse_iterator crend() const noexcept { return reverse_iterator(itt); }

    bool operator==(const Vector<T> &v) const;
    bool operator!=(const Vector<T> &v) const;
    bool operator<(const Vector<T> &v) const;
    bool operator<=(const Vector<T> &v) const;
    bool operator>(const Vector<T> &v) const;
    bool operator>=(const Vector<T> &v) const;

    void push_back(const T &t) {
        if (avail == limit)
            grow();
        unchecked_append(t);
    }
    void assign(size_type n, const value_type& val);
    void assign(const_iterator i, const_iterator j);
    void assign(std::initializer_list<T> list);
    void pop_back();
    void insert(const_iterator position, const value_type& val);
    void insert(const_iterator position, size_type n, const value_type& val);
    void insert(iterator position, const_iterator first, const_iterator last);
    void clear();
    void erase(const_iterator position);
    //void erase(const_iterator first, const_iterator last);
    iterator erase(iterator first, iterator last);
    void resize(size_type n, const value_type& val);
    void resize(size_type n);
    void swap(Vector<T> &v);
    void shrink_to_fit();
    void reserve(size_type n);
    bool empty() { return begin() == end(); }
    template <class... Args>
    void emplace(const_iterator position, Args&&... args);
    template <class... Args>
    void emplace_back(Args&&... args);

private:
    iterator itt;
    iterator avail;
    iterator limit;
    std::allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    void uncreate();
    void grow();
    void unchecked_append(const T &);
};

template<class T>
void Vector<T>::assign(const_iterator i, const_iterator j) {
    uncreate();
    create(i, j);
}

template<class T>
void Vector<T>::assign(size_type n, const T& value) {
    uncreate();
    itt = alloc.allocate(n);
    limit = avail = itt + n;
    std::uninitialized_fill(itt, limit, value);
}
template<class T>
void Vector<T>::assign(std::initializer_list<T> list) {
    assign(list.begin(), list.end());
}

template<class ForwardIt, class T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T &value);
template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first);

template<class T>
void Vector<T>::create() {
    itt = avail = limit = nullptr;
}

template<class T>
void Vector<T>::create(size_type n, const T &val) {
    itt = alloc.allocate(n);
    limit = avail = itt + n;
    std::uninitialized_fill(itt, limit, val);
}

template<class T>
void Vector<T>::create(const_iterator i, const_iterator j) {
    itt = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, itt);
} 

template<class T>
void Vector<T>::uncreate() {
    if (itt) {
        iterator it = avail;
        while (it != itt)
            alloc.destroy(--it); 
        alloc.deallocate(itt, limit - itt);
    }
    itt = limit = avail = nullptr;
}

template<class T>
void Vector<T>::grow() {
    size_type new_size = std::max(2 * (limit - itt), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(itt, avail, new_data);

    uncreate();
    itt = new_data;
    avail = new_avail;
    limit = itt + new_size;
}

template<class T>
void Vector<T>::unchecked_append(const T &value) {
    alloc.construct(avail++, value);
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (&other != this) {
        uncreate();
        create(other.begin(), other.end());
    }
    return *this;
}

template<class T>
class alloc {
public:
    T *allocate(size_t);
    void deallocate(T *, size_t);
    void construct(T *, const T &);
    void destroy(T *);
};



template<class T>
template<class... Args>
void Vector<T>::emplace_back(Args &&... args) {
    iterator avail_ = avail;
    emplace(avail_, (args)...);
}

template<class T>
template<class... Args>
void Vector<T>::emplace(const_iterator position, Args &&... args) {
    if (sizeof...(args) + size() < capacity()) {
        size_type index = position - itt;
        iterator true_position = itt + index;

        iterator new_avail = std::move(true_position, avail, true_position + sizeof...(args));
        alloc.construct(true_position, std::forward<Args>(args)...);

        avail = new_avail;
    }
    else if (sizeof...(args) + size() >= capacity()) {
        size_type index = position - itt;
        grow();
        iterator new_position = itt + index;
        emplace(new_position, std::forward<Args>(args)...);
    }
}

template<class T>
void Vector<T>::insert(Vector<T>::const_iterator position, const value_type& val) {
    insert(position, 1, val);
}
template<typename T>
void Vector<T>::insert(const_iterator position, size_type n, const value_type& val) {
    if (size() + n < capacity()) {
        iterator position_ = position;

        iterator new_avail = std::move(position_, avail, position_ + n);
        std::fill(position_, position_ + n, val);

        avail = new_avail;
    } else if (size() + n >= capacity()) {
        size_type i = position - itt;
        grow();
        iterator new_position = itt + i;
        insert(new_position, n, val);
    }
}
template<typename T>
void Vector<T>::insert(Vector<T>::iterator position, const_iterator first, const_iterator last) {   // Range
    if (size() + (last - first) < capacity()) {
        size_type index = position - itt;
        size_type n = last - first;
        iterator true_position = itt + index;

        iterator new_avail = std::move(true_position, avail, true_position + n);
        std::copy(first, last, position);

        avail = new_avail;
    } else if (size() + (last - first) >= capacity()) {
        size_type index = position - itt;
        grow();
        iterator new_position = itt + index;
        insert(new_position, first, last);
    }
}

template<typename T>
void Vector<T>::clear() {
    iterator it = avail;
    while (it != itt) {
        alloc.destroy(--it);
    }
    avail = it;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    if (avail < limit) {
        limit = avail;
    }
}

template<typename T>
void Vector<T>::erase(Vector<T>::const_iterator position) {
    if (position < itt || position > avail)
        throw std::out_of_range{"Out of bounds! (Vector::erase)"};
    iterator new_avail = std::move(position + 1, avail, position);
    alloc.destroy(new_avail);
    avail = new_avail;
}

/*template<typename T>
void Vector<T>::erase(Vector<T>::const_iterator first, Vector<T>::const_iterator last) {
    if (first < itt || last > avail)
        throw std::out_of_range{"Out of bounds! (Vector::erase)"};
    iterator new_avail = std::move(last, avail, first);
    avail = new_avail;
}*/

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) 
{
    int i = 0;
    int temp = 0;
    auto it = (*this).begin();
    for (it; it != first; it++, i++);
    for (it = first; it != last; it++, temp++, i++);
    for (auto it = last; it != (*this).end(); it++, i++)
        itt[i - temp] = itt[i];
    avail -= temp;
    return last;
}

template<typename T>
void Vector<T>::resize(size_type n, const value_type& value) {
    if (n > capacity()) {
        grow();
        resize(n, value); // rekursija
    } else if (n > size()) {
        size_type i = size();
        avail += (n - size());

        for (; i < n; i++) {
            itt[i] = value;
        }
    } else resize(n);
}

template<typename T>
void Vector<T>::resize(size_type n) {
    if (n < size()) {
        // erase(itt + n, avail);
        iterator it = avail;
        while (it != begin() + n) {
            alloc.destroy(--it);
        }
        avail = begin() + n;
    } else if (n > capacity()) {
        grow();
        resize(n);
    } else if (n > size()) {
        avail += (n - size());
    }
}

template<typename T>
void Vector<T>::reserve(size_type n) {
    if (n > capacity()) {
        size_type new_size = n;

        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(itt, avail, new_data);

        uncreate();
        itt = new_data;
        avail = new_avail;
        limit = itt + new_size;
    }
}


template<typename T>
T *Vector<T>::data() noexcept {
    return data;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return (double) (std::numeric_limits<T>::max() - std::numeric_limits<T>::min());
}

template<typename T>
void Vector<T>::swap(Vector<T> &v) {
    iterator data2 = itt, avail2 = avail, limit2 = limit;
    itt = v.itt;
    limit = v.limit;
    avail = v.avail;

    v.itt = data2;
    v.avail = avail2;
    v.limit = limit2;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &v) const {
    if (v.size() != size())
        return false;
    else {
        size_type g = v.size();

        for (size_type k = 0; k < g; k++) {
            if (itt[k] != v.itt[k]) { return false; }
        }

        return true;
    }
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &v) const {
    if (v.size() != size())
        return true;
    else {
        size_type n = v.size();
        for (size_type i = 0; i < n; i++) {
            if (itt[i] != v.itt[i]) { return true; }
        }
        return false;
    }
}

template<typename T>
bool Vector<T>::operator<(const Vector<T> &v) const {
    bool tr;
    tr = operator==(v);
    if (tr)
        return false;

    else {
        size_type g = v.size();
        for (size_type a = 0; a < g; a++) {
            if (itt[a] < v.itt[a])
                return true;
            else if (itt[a] > v.itt[a])
                return false;
        }
    }
}

template<typename T>
bool Vector<T>::operator<=(const Vector<T> &v) const {
    bool tr;
    tr = operator==(v);

    if (tr)
        return true;

    else {
        tr = operator<(v);

        return tr; // tr==true or false
    }
}

template<typename T>
bool Vector<T>::operator>(const Vector<T> &v) const {
    bool t;
    t = operator<=(v);

    return !t;
}

template<typename T>
bool Vector<T>::operator>=(const Vector<T> &v) const {
    bool t;
    t = operator<(v);

    return !t;
}

template<class T>
void Vector<T>::pop_back() {
    iterator itavail = avail;
    alloc.destroy(--itavail);
    avail = itavail;
}

#endif