namespace s21 {

// Inner class ListIterator
template <typename T>
List<T>::ListIterator::ListIterator() : curr_(nullptr), listHead_(nullptr), listTail_(nullptr) {}

template <typename T>
List<T>::ListIterator::ListIterator(const List &l) {
    if (l.head_ == nullptr) {
        throw std::invalid_argument("Передан пустой лист");
    }
    curr_ = l.head_;
    listHead_ = l.head_;
    listTail_ = l.tail_;
}

// template <typename T>
// List<T>::ListIterator::ListIterator(const ListIterator &l) : curr_(l.curr_), listHead_(l.listHead_), listTail_(l.listTail_) {}

template <typename T>
typename List<T>::ListIterator& List<T>::ListIterator::operator++() {
    if (listHead_ == nullptr) {
        throw std::invalid_argument("Операция невозможна, пустой лист");
    }

    if (curr_ == nullptr) {
        curr_ = listHead_;
    } else {
        curr_ = curr_->next_;
    }
    return *this;
}

template <typename T>
typename List<T>::ListIterator& List<T>::ListIterator::operator--() {
    if (listHead_ == nullptr) {
        throw std::invalid_argument("Операция невозможна, пустой лист");
    }

    if (curr_ == nullptr) {
        curr_ = listTail_;
    } else {
        curr_ = curr_->prev_;
    }
    return *this;
}

template <typename T>
typename List<T>::ListIterator List<T>::ListIterator::operator+(size_type count) {
    if (listHead_ == nullptr) {
        throw std::invalid_argument("Операция невозможна, пустой лист");
    }

    iterator temp = *this;
    while (count--) {
        ++temp;
    }
    return temp;
}

template <typename T>
typename List<T>::reference List<T>::ListIterator::operator*() const {
    if (curr_ == nullptr) {
        return listHead_->data_;
    }
    return curr_->data_;
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator& other) const noexcept {
    return curr_ == other.curr_;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator& other) const noexcept {
    return curr_ != other.curr_;
}

template <typename T>
bool List<T>::ListIterator::operator<(const ListIterator& other) const noexcept {
    bool res = false;
    iterator temp = other;
    temp.curr_ = temp.listHead_;
    for (; temp != other; ++temp) {
        if (temp == *this) {
            res = true;
            break;
        }
    }

    return res;  
}

template <typename T>
bool List<T>::ListIterator::operator<=(const ListIterator& other) const noexcept {
    return *this < other || *this == other;
}


// Inner class ConstListIterator
// template <typename T>
// List<T>::ConstListIterator(const ListIterator &l) : curr_(l.curr_), listHead_(l.listHead_), listTail_(l.listTail_) {}

template <typename T>
typename List<T>::const_reference List<T>::ConstListIterator::operator*() const noexcept {
    if (this->curr_ == nullptr) {
        return this->listHead_->data_;
    }
    return this->curr_->data_;
}

template <typename T>
typename List<T>::ConstListIterator& List<T>::ConstListIterator::operator=(const ListIterator& other) {
    this->curr_ = other.curr_;
    this->listHead_ = other.listHead_;
    this->listTail_ = other.listTail_;
    return *this;
}



// List constructors
template <typename T>
List<T>::List() : size_(0U), head_(nullptr), tail_(nullptr) {}

template <typename T>
List<T>::List(size_type n) : List() {
    if (n > max_size()) {
        throw std::length_error("Лист имеет максимальный размер");
    }

    while (n--) {
        push_back(value_type());
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> const &items) : List() {
    for (auto i : items) {
        push_back(i);
    }
}

template <typename T>
List<T>::List(const List &l) : List() {
    Node* temp = l.head_;
    for (size_type i = 0; i < l.size_; ++i) {
        push_back(temp->data_);
        temp = temp->next_;
    }
}

template <typename T>
List<T>::List(List &&l) : List() {
    std::swap(size_, l.size_);
    std::swap(head_, l.head_);
    std::swap(tail_, l.tail_);
}


// List destructor
template <typename T>
List<T>::~List() {
    clear();
}


// List operators
template <typename T>
List<T>& List<T>::operator=(const List &l) {
    List<T> temp = l;
    *this = std::move(temp);
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List &&l) {
    std::swap(this->size_, l.size_);
    std::swap(this->head_, l.head_);
    std::swap(this->tail_, l.tail_);
    return *this;
}


// List element access
template <typename T>
typename s21::List<T>::const_reference List<T>::front() {
    if (!head_) {
        throw std::out_of_range("Вектор пуст");
    }
    return head_->data_;
}

template <typename T>
typename s21::List<T>::const_reference List<T>::back() {
    if (!tail_) {
        throw std::out_of_range("Вектор пуст");
    }
    return tail_->data_;
}


// List iterators
template <typename T>
typename List<T>::iterator List<T>::begin() {
    iterator iter (*this);
    return iter;
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    iterator iter (*this);
    iter.curr_ = nullptr;
    return iter;
}


// List capacity
template <typename T>
bool List<T>::empty() {
    return !head_;
}

template <typename T>
typename s21::List<T>::size_type List<T>::size() {
    return size_;
}

template <typename T>
typename s21::List<T>::size_type List<T>::max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
}


// List Modifiers
template <typename T>
void List<T>::clear() {
    if (head_) {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
        tail_ = nullptr;
        size_ = 0;
    }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const_reference value) {
    check_iterator(pos);
    if (size_ == max_size()) {
        throw std::length_error("Лист имеет максимальный размер");
    }

    iterator res (*this);
    if (pos == end()) {
        push_back(value);
        res = end();
    } else if (pos == begin()) {
        push_front(value);
        res = begin();
    } else {
        Node* temp = new Node(value, pos.curr_, pos.curr_->prev_);
        pos.curr_->prev_->next_ = temp;
        pos.curr_->prev_ = temp;
        res.curr_ = temp;
        ++size_;
    }
    
    return res;
}

template <typename T>
void List<T>::erase(iterator pos) {
    if (pos.curr_ == nullptr) {
        throw std::invalid_argument("Невозможно удалить элемент, "
            "итератор указывает на nullptr");
    }
    check_iterator(pos);
    if (pos.curr_->prev_ == nullptr) {
        pop_front();
    } else if (pos.curr_->next_ == nullptr) {
        pop_back();
    } else {
        Node* temp = pos.curr_;
        temp->prev_->next_ = temp->next_;
        temp->next_->prev_ = temp->prev_;
        delete temp;
        --size_;
    }
} 

template <typename T>
void List<T>::push_back(const_reference value) {
    if (size_ == max_size()) {
        throw std::length_error("Лист имеет максимальный размер");
    }

    if (size_ == 0) {
        head_ = tail_ = new Node(value);
    } else {
        tail_->next_ = new Node(value, nullptr, tail_);
        tail_ = tail_->next_;
    }
    ++size_;
}

template <typename T>
void List<T>::pop_back() {
    Node* temp = tail_;
    tail_ = tail_->prev_;
    tail_->next_ = nullptr;
    delete temp;
    --size_;
}

template <typename T>
void List<T>::push_front(const_reference value) {
    if (size_ == max_size()) {
        throw std::length_error("Лист имеет максимальный размер");
    }

    if (size_ == 0) {
        head_ = tail_ = new Node(value);
    } else {
        head_->prev_ = new Node(value, head_, nullptr);;
         head_ = head_->prev_;
    }
    ++size_;
}

template <typename T>
void List<T>::pop_front() {
    Node* temp = head_;
    head_ = head_->next_;
    head_->prev_ = nullptr;
    delete temp;
    --size_;
}

template <typename T>
void List<T>::swap(List& other) {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
}

template <typename T>
void List<T>::merge(List& other) {
    iterator t_end = end();
    iterator o_end = other.end();

    for (iterator i = begin(), j = other.begin(); j != o_end; ) {
        if (i == t_end || *i >= *j) {
            i = insert(i, *j);
            ++j;
        }
        ++i;
    }
}

template <typename T>
void List<T>::splice(const_iterator pos, List& other) {
    check_iterator(pos);
    iterator i = pos;
    iterator j = other.begin();
    for (size_type k = 0; k < other.size_; ++k, ++j, ++i) {
        i = insert(i, *j);
    }
}

template <typename T>
void List<T>::reverse() {
    iterator start = begin();
    iterator finish = --end();
    for (size_type i = 0; i < size_ / 2; ++i, ++start, --finish) {
        std::swap(*start, *finish);
    }
}

template <typename T>
void List<T>::unique() {
    iterator i = begin();
    iterator j = i + 1;
    iterator i_end = end();
    while(j != i_end) {
        if (*i == *j) {
            iterator temp = j;
            ++j;
            erase(temp);
        } else {
            ++j;
            ++i;
        }
    }
}

template <typename T>
void List<T>::sort() {
    quick_sort(begin(), --end());
}


// utility methods
template <typename T>
void List<T>::check_iterator(iterator pos) const {
    if (head_ != pos.listHead_ && tail_ != pos.listTail_) {
        throw std::invalid_argument("Этого итератора нет в листе >> check_iterator");
    }
}

template <typename T>
void List<T>::check_iterator(const_iterator pos) const {
    if (head_ != pos.listHead_ && tail_ != pos.listTail_) {
        throw std::invalid_argument("Этого итератора нет в листе >> check_iterator");
    }
}

template <typename T>
void List<T>::quick_sort(const iterator& l_board, const iterator& r_board) {
    value_type middle = *l_board;
    iterator left = l_board, right = r_board;
    while (left <= right) {
        while (*left < middle) {
            ++left;
        }

        while (*right > middle) {
            --right;
        }

        if (left <= right) {
            if (left < right) {
                std::swap(*left, *right);
            }
            ++left;
            --right;
        }
    }

    if (l_board < right) {
        quick_sort(l_board, right);
    }

    if (left < r_board) {
        quick_sort(left, r_board);
    }
}
} // close namespace s21