#include "CircularBuffer.h"
#include <iostream>

CircularBuffer::CircularBuffer() {
    buffer = nullptr;
    start_ = 0;
    end_ = 0;
    capacity_ = 0;
    size_ = 0;
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
    buffer = nullptr;
}

CircularBuffer::CircularBuffer(int capacity) {
    buffer = new value_type[capacity];
    capacity_ = capacity;
    start_ = 0;
    size_ = 0;
    end_ = 0;
}

CircularBuffer::CircularBuffer(const CircularBuffer &cb ) {
    this->start_ = cb.start_;
    this->end_ = cb.end_;
    this->capacity_ = cb.capacity_;
    this->size_ = cb.size_;
    this->buffer = new value_type[cb.capacity_];
    std::memcpy(this->buffer, cb.buffer, cb.capacity_ * sizeof(value_type));
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem) {
    buffer = new value_type[capacity];
    capacity_ = capacity;
    start_ = 0;
    size_ = capacity_;
    end_ = size_;
    std::fill(buffer, buffer+capacity, elem);
}

//Доступ по индексу. Не проверяют правильность индекса.
value_type & CircularBuffer::operator[](int i) {
    value_type & elem = buffer[(start_+i)%capacity_];
    return elem;
}
const value_type & CircularBuffer::operator[](int i) const {
    const char & elem = buffer[(start_+i)%capacity_];
    return elem;
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
value_type & CircularBuffer::at(int i) {
    if (i < capacity_) {
        char & elem = buffer[(start_+i)%capacity_];
        return elem;
    }
    throw std::out_of_range("i >= capacity!");
}
const value_type & CircularBuffer::at(int i) const {
    if (i < capacity_  and i >= 0) {
        const char & elem = buffer[(start_+i)%capacity_];
        return elem;
    }
    throw std::out_of_range("i >= capacity!");
}

value_type & CircularBuffer::front() {
    if (capacity_) {
        if (size_ == 0) {
            throw std::logic_error("Buffer is empty");
        }
        value_type & elem = buffer[0];
        return elem;
    }
    throw std::logic_error("Capacity = 0");
}
value_type & CircularBuffer::back() {
    if (capacity_) {
        if (size_ == 0) {
            throw std::logic_error("Buffer is empty");
        }
        value_type & elem = buffer[end_];
        if (end_ == size_) {
            elem = buffer[end_-1];
        }
        return elem;

    }
    throw std::logic_error("Capacity = 0");

}
const value_type & CircularBuffer::front() const {
    if (capacity_) {
        if (size_ == 0) {
            throw std::logic_error("Buffer is empty");
        }
        const value_type & elem = buffer[0];
        return elem;
    }
    throw std::logic_error("Capacity = 0");

}
const value_type & CircularBuffer::back() const {
    if (capacity_) {
        if (size_ == 0) {
            throw std::logic_error("Buffer is empty");
        }
        size_t index_element = end_;
        if (end_ == size_) {
            index_element = end_ - 1;
        }
        const value_type & elem = buffer[index_element];
        return elem;
    }
    throw std::logic_error("Capacity = 0");
}




value_type * CircularBuffer::linearize() {
    if (size_ <= 0) {
        throw std::logic_error("Size == 0");
    }
    if (is_linearized()) {
        return &buffer[0];
    }
    auto new_buffer = new value_type[capacity_];
    int new_index = 0;
    if (start_ == end_) {
        end_ = (end_ + 1)%capacity_;
    } // no test
    while(start_ != end_) {
        start_ = start_ % capacity_;
        new_buffer[new_index] = buffer[0];
        new_index++;
        start_++;
    }
    delete[] buffer;
    buffer = new_buffer;
    start_ = 0;
    end_ = size_;
    return &buffer[0];
}

//Проверяет, является ли буфер линеаризованным.
bool CircularBuffer::is_linearized() const {
    if (start_ == 0 and end_ == size_) {
        return true;
    }
    return false;
}

void CircularBuffer::rotate(int new_begin) {
    if (new_begin < 0 or new_begin >= size_) {
        throw std::invalid_argument("new_begin < 0");
    }
    end_ = (end_ - (start_ - new_begin)) % capacity_;
    start_ = new_begin;
}

size_t CircularBuffer::size() const {
    return size_;
}

bool CircularBuffer::empty() const {
    if (size_) {
        return false;
    }
    return true;
}

bool CircularBuffer::full() const {
    if (size_ == capacity_) {
        return true;
    }
    return false;
}

size_t CircularBuffer::capacity() const {
    return capacity_;
}

size_t CircularBuffer::reserve() const {
    return capacity_ - size_;
}

void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity <= 0) {
        throw std::invalid_argument("Capacity <= 0");
    }
    auto new_buffer = new value_type[new_capacity];

    int elements = std::min(new_capacity,static_cast<int>(size_));
    for (int i = 0; i < elements; i++) {
        new_buffer[i] = buffer[i];
    }
    size_ = elements;
    capacity_ = new_capacity;
    end_ = elements % capacity_;
    start_ = 0;
    delete[] buffer;
    buffer = new_buffer;
}
//Изменяет размер буфера.
//В случае расширения, новые элементы заполняются элементом item.
void CircularBuffer::resize(int new_size, const value_type & item) {
    if (new_size < 0) {
        throw std::invalid_argument("Capacity <= 0");
    }
    if (new_size > capacity_) {
        capacity_ = new_size;
    }
    auto new_buffer = new value_type[capacity_];
    if (new_size > size_) {
        for (int i = 0; i < new_size; i++) {
            if (buffer[i]) {
                new_buffer[i] = buffer[i];
            }
            else {
                new_buffer[i] = item;
            }
        }
    }
    else {
        for (int i = 0; i < new_size; i++) {
            new_buffer[i] = buffer[i];
        }
    }
    end_ = new_size % capacity_;
    start_ = 0;
    size_ = new_size;
    delete[] buffer;
    buffer = new_buffer;
}
//Оператор присваивания.
CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb) {
    delete[] this->buffer;
    this->capacity_ = cb.capacity_;
    this->size_ = cb.size_;
    this->end_ = cb.end_;
    this->start_ = cb.start_;
    this->buffer = new value_type[this->capacity_];
    for (int i = 0; i < this->size_; i++) {
        this->buffer[i] = cb.buffer[i];
    }
    return *this;
}

//Обменивает содержимое буфера с буфером cb.
void CircularBuffer::swap(CircularBuffer & cb) {
    value_type* buffer_new = cb.buffer;
    cb.buffer = this->buffer;
    this->buffer = buffer_new;
    std::swap(this->size_, cb.size_);
    std::swap(this->capacity_, cb.capacity_);
    std::swap(this->end_, cb.end_);
    std::swap(this->start_, cb.start_);
}


void CircularBuffer::push_back(const value_type & item) {
    buffer[end_] = item;

    end_ = (end_ + 1) % capacity_;

    if (size_ == capacity_) {
        start_ = (start_ + 1) % capacity_;
    } else {
        size_++;
    }

}

void CircularBuffer::push_front(const value_type & item) {
    if (start_ == 0) {
        start_ = capacity_ - 1;
    }
    else {
        start_--;
    }
    if (size_ == capacity_) {
        end_ = (end_ == 0) ? capacity_ - 1 : end_ - 1;
    }
    else {
        size_++;
    }
    buffer[start_] = item;
}

void CircularBuffer::pop_back() {
    if (size_ == 0) {
        throw std::out_of_range("Size == 0");
    }
    end_--;
    // if (end_ == 0) {
    //     end_ = capacity_ - 1;
    // }
    // else {
    //     end_--;
    // }
    buffer[end_] = static_cast<value_type>(0);
    size_--;
}

void CircularBuffer::pop_front() {
    if (size_ == 0) {
        throw std::out_of_range("Size == 0");
    }
    buffer[0] = static_cast<value_type>(0);
    if (start_ == capacity_ - 1) {
        start_ = 0;
    }
    else {
        start_++;
    }
    size_--;
}

void CircularBuffer::insert(int pos, const value_type & item) {
    if (pos < 0 && pos > capacity_ - 1) {
        throw std::out_of_range("wrong value");
    }
    buffer[pos] = item;
}

//Удаляет элементы из буфера в интервале [first, last).
void CircularBuffer::erase(int first, int last) {
    if (first < 0 or last < 0 or first > capacity_-1 or last > capacity_-1) {
        throw std::out_of_range("wrong value");
    }
    if (first > last) {
        throw std::invalid_argument("invalid argument");
    }
    int length = last - first;

    std::memmove(buffer + first, buffer + last, capacity_-last);
    for (int i = 0; i < length; i++) {
        buffer[capacity_ - i - 1] = static_cast<value_type>(0);
        size_--;
    }
    end_ = (start_ + size_)%capacity_;
 }

void CircularBuffer::clear() {
    while(size_ != 0) {
        pop_front();
    }
    start_ = 0;
    end_ = 0;
}

bool operator==(const CircularBuffer & a, const CircularBuffer & b) {
    if ((a.capacity() == b.capacity()) and (a.size() == b.size())) {
        size_t capacity = a.capacity();
        for (int i = 0; i < capacity; i++) {
            if (a.at(i) == b.at(i)) {
                continue;
            }
            return false;
        }
        return true;
    }
    return false;
}
bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
    if ((a.capacity() == b.capacity()) and (a.size() == b.size())) {
        size_t capacity = a.capacity();
        for (int i = 0; i < capacity; i++) {
            if (a.at(i) == b.at(i)) {
                continue;
            }
            return true;
        }
        return false;
    }
    return true;
}
// 0 1 2  3  4  5 6
// 5 8 12 13 41 2 42