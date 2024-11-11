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
    if(buffer) {
        delete[] buffer;
        buffer = nullptr;
    }
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

value_type & CircularBuffer::operator[](int i) {
    return value_index(i);
}

const value_type & CircularBuffer::operator[](int i) const {
    return value_index(i);
}

value_type & CircularBuffer::at(int i) {
    if (i < size_) {
        return value_index(i);
    }
    throw std::out_of_range("i >= size!");
}
const value_type & CircularBuffer::at(int i) const {
    if (i < size_) {
        return value_index(i);
    }
    throw std::out_of_range("i >= size!");
}

value_type & CircularBuffer::front() {
    return (*this)[0];
}
value_type & CircularBuffer::back() {
    return (*this)[end_ - 1];

}
const value_type & CircularBuffer::front() const {
    return (*this)[0];
}

const value_type & CircularBuffer::back() const {
    return (*this)[end_ - 1];
}


value_type * CircularBuffer::linearize() {
    if (is_linearized()) {
        return &buffer[0];
    }
    auto new_buffer = new value_type[capacity_];
    int new_index = 0;
    if (start_ == end_) {
        end_ = (end_ + 1)%capacity_;
    }
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

bool CircularBuffer::is_linearized() const {
    return start_ == 0 and end_ == size_;
}

void CircularBuffer::rotate(int new_begin) {
    if (new_begin >= static_cast<int>(size_)) {
        throw std::invalid_argument("new_begin >= size");
    }
    end_ = (end_ - (start_ - new_begin)) % capacity_;
    start_ = new_begin;
    if (new_begin < 0) {
        start_ = new_begin + capacity_;
    }
}

size_t CircularBuffer::size() const {
    return size_;
}

bool CircularBuffer::empty() const {
    return !size_;
}

bool CircularBuffer::full() const {
    return size_ == capacity_;
}

size_t CircularBuffer::capacity() const {
    return capacity_;
}

size_t CircularBuffer::reserve() const {
    return capacity_ - size_;
}
// this
void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity <= 0) {
        throw std::invalid_argument("Capacity <= 0");
    }
    auto new_buffer = new value_type[new_capacity];

    int elements = std::min(new_capacity,static_cast<int>(size_));
    for (int i = 0; i < elements; i++) {
        new_buffer[i] = (*this)[i];
    }
    size_ = elements;
    capacity_ = new_capacity;
    end_ = elements % capacity_;
    start_ = 0;
    delete[] buffer;
    buffer = new_buffer;
}

void CircularBuffer::resize(int new_size, const value_type & item) {
    if (new_size < 0) {
        throw std::invalid_argument("Size < 0");
    }
    if (new_size > capacity_) {
        capacity_ = new_size;
    }
    auto new_buffer = new value_type[capacity_];
    if (new_size > size_) {
        std::memcpy(new_buffer, buffer, size_ * sizeof(value_type));
        std::fill(new_buffer, new_buffer+(size_ - new_size), item);
    }
    else {
        for (int i = 0; i < new_size; i++) {
            new_buffer[i] = (*this)[i];
        }
    }
    end_ = new_size % capacity_;
    start_ = 0;
    size_ = new_size;
    delete[] buffer;
    buffer = new_buffer;
}

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

void CircularBuffer::swap(CircularBuffer & cb) {
    std::swap (this->buffer, cb.buffer);
    std::swap(this->size_, cb.size_);
    std::swap(this->capacity_, cb.capacity_);
    std::swap(this->end_, cb.end_);
    std::swap(this->start_, cb.start_);
}


void CircularBuffer::push_back(const value_type & item) {
    if (end_ == capacity_) {
        end_ = 0;
    }

    (*this)[end_] = item;

    end_ = (end_ + 1) % capacity_;

    if (size_ == capacity_) {
        start_ = (start_ + 1) % capacity_;
    }
    else {
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
    (*this)[0] = item;
}

void CircularBuffer::pop_back() {
    end_--;
    buffer[end_] = static_cast<value_type>(0);
    size_--;
}

void CircularBuffer::pop_front() {
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
    if (pos > capacity_ - 1) {
        throw std::out_of_range("wrong value");
    }
    (*this)[pos] = item;
}

void CircularBuffer::erase(int first, int last) {
    if (first < 0) {
        first = first + capacity_;
    }
    if (last < 0) {
        last = last + capacity_;
    }
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
            if (a.at(i) != b.at(i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
    return !(a == b);
}
