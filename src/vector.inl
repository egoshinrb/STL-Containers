namespace s21 {

// Vector constructors
template <typename T>
Vector<T>::Vector() : Vector(0U) {}

template <typename T>
Vector<T>::Vector(size_type size)  : size_(size), capacity_(size), arr_(size ? new value_type[size] : nullptr) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &other) : Vector(other.size()) {
    auto end = other.end();
    int i = 0;
    for (auto iter = other.begin(); iter != end; ++iter) {
        arr_[i++] = *iter;
    }
}

template <typename T>
Vector<T>::Vector(const Vector &other) : Vector(other.size_) {
    auto end = other.end();
    int i = 0;
    for (auto iter = other.begin(); iter != end; ++iter) {
        arr_[i++] = *iter;
    }
}

template <typename T>
Vector<T>::Vector(Vector &&other) : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
    other.arr_ = nullptr;
}


// Vector operators
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector &other) noexcept {
    Vector<T> temp = other;
    *this = std::move(temp);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector &&other) noexcept {
    std::swap(this->arr_, other.arr_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
    return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](const size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("Позиция аргумента выходит за границы вектора");
    }
    return arr_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](const size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("Позиция аргумента выходит за границы вектора");
    }
    return arr_[pos];
}


// Vector dectructor
template <typename T>
Vector<T>::~Vector() {
    clear();
}


// Vector Element access
template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("Позиция аргумента выходит за границы вектора");
    }
    return *(arr_ + pos);
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("Позиция аргумента выходит за границы вектора");
    }
    return *(arr_ + pos);
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    if (arr_ == nullptr) {
        throw std::out_of_range("Вектор пуст");
    }
    return *arr_;
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    if (arr_ == nullptr) {
        throw std::out_of_range("Вектор пуст");
    }
    return *(arr_ + size_ - 1);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::data() const noexcept {
    return arr_;
}


// Vector Iterators
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
    if (arr_ == nullptr) {
        throw std::out_of_range("Вектор пуст");
    }
    return arr_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const {
    if (arr_ == nullptr) {
        throw std::out_of_range("Вектор пуст");
    }
    return arr_ + size_;
}


// Vector Capacity
template <typename T>
bool Vector<T>::empty() const noexcept {
    if (arr_) {
        return false;
    }
    return true;
}

template <typename T>
size_t Vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t Vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T) / 2;
}

template <typename T>
void Vector<T>::reserve(size_type size) {
    if (size > max_size()) {
        throw std::out_of_range("Размер вектора больше максимального");
    }

    if (size <= capacity_) return;

    value_type* new_arr = new value_type[size]();
    for (int i = 0; i < size_; ++i) {
        new_arr[i] = arr_[i];
    }
    delete [] arr_;
    arr_ = new_arr;
    capacity_ = size;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ == size_) return;

    value_type new_arr = new value_type[size_];
    for (int i = 0; i < size_; ++i) {
        new_arr[i] = arr_[i];
    }
    delete [] arr_;
    arr_ = new_arr;
    capacity_ = size_;
}


// Vector Modifiers
template <typename T>
void Vector<T>::clear() {
    if (arr_) {
        delete [] arr_;
        size_ = 0;
        capacity_ = 0;
    }
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference value) {
    if (pos == nullptr) {
        throw std::out_of_range("Итератор не должен быть nullptr");
    }
    
    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Итератор выходит за границы вектора");
    }

    iterator t_pos = pos;
    if (capacity_ > size_) {
        iterator t_end = end() + 1;
        reference temp = *(const_cast<int*>(&value));
        for (; pos < t_end; ++pos) {
            std::swap(temp, *pos);
        }
    } else {
        if (capacity_ > max_size() / 2) {
            throw std::length_error("Слишком большой объем вектора");
        }
        capacity_ *= 2;
        value_type *new_arr = new value_type[capacity_]();
        for (size_type i = 0, j = 0; i < size_; ++i, ++j) {
            if (arr_ + i == pos) {
                new_arr[j++] = value;
                t_pos = new_arr + j - 1;
            }
            new_arr[j] = arr_[i];

            if (i + 1 == size_ && pos == end()) {
                new_arr[j + 1] = value;
            }
        }

        delete [] arr_;
        arr_ = new_arr;
        new_arr = nullptr;
    }
    ++size_;
    
    return t_pos;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
    if (pos == nullptr) {
        throw std::out_of_range("Итератор не должен быть nullptr");
    }
    
    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Итератор выходит за границы вектора");
    }

    iterator t_end = end();
    for (; pos < t_end; ++pos) {
        std::swap(*pos, *(pos + 1));
    }
    --size_;
}

template <typename T>
void Vector<T>::push_back(const_reference value) noexcept {
    insert(end(), value);
}

template <typename T>
void Vector<T>::pop_back() noexcept {
    erase(end() - 1);
}

template <typename T>
void Vector<T>::swap(Vector& other) noexcept {
    if (this != &other) {
        std::swap(arr_, other.arr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
}


} // close namespace s21