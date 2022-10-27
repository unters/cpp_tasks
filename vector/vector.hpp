#ifndef AL_VECTOR
#define AL_VECTOR

#include <stdlib.h> // for size_t
#include <utility>  // for std::swap


namespace al {
    template <typename T>
    class vector {
    public:

        typedef T         value_type;
        typedef T *       pointer;
        typedef T &       reference;
        typedef T const * const_pointer;
        typedef T const & const_reference;
        // TODO: iterator
        // TODO: const_iterator

        vector() noexcept
            : data_(nullptr)
            , size_(0)
            , capacity_(0) {}

        vector(size_t const & n, T const & value = T())
            : size_(n)
            , capacity_(n) { 
            data_ = static_cast<T *>(calloc(n, sizeof(value)));

            for (int i = 0; i < n; ++i)
                data_[i] = value;
        }

        // TODO: must have.
        vector(vector<T> & v);

        vector(vector<T> && v) : vector() { swap(v); }

        // TODO: memory leak possible.
        ~vector() {
            for (size_t i = 0; i < size_; ++i)  // Shouldn't there be i < capacity_? After resize
                (data_ + i)->~T();              // there could be T objects after data_[size_ - 1];

            delete [] reinterpret_cast<int8_t*>(data_);   // I don't remember what is this. TODO
        }

        vector<T> & operator= (vector<T> const & v) {
            if (this == &v)
                return *this;

            delete [] data_;
            size_ = v.size_, capacity_ = size_;
            data_ = static_cast<T *>(calloc(capacity_, sizeof(T)));

            for (int i = 0; i < size_; ++i)
                data_[i] = T(v[i]);

            return *this;
        }

        vector<T> & operator= (vector<T> && v) noexcept {
            swap(v);
            return *this;
        }

        T & operator[] (size_t n) {
            return data_[n];
        }

        T const & operator[] (size_t n) const {
            return data_[n];
        }

        bool empty() {
            if (size_)
                return false;

            return true;
        }

        size_t size() { return size_; }

        size_t capacity() { return capacity_; }

        /* Increase capacity.  */
        void reserve(size_t n) {
            if (n <= capacity_)
                return;

            T * new_data = reinterpret_cast<T *>(new int8_t[n * sizeof(T)]);

            for (size_t i = 0; i < size_; ++i)
                new (new_data + i) T(std::move(data_[i]));

            for (size_t i = 0; i < size_; ++i)
                (data_ + i)->~T();

            delete [] reinterpret_cast<int8_t*>(data_);

            data_     = new_data;
            capacity_ = n;
        }

        /* Increase or decrease size. Increasing means adding new elements
         * using default or cypy constructor. Decreasing just changes size_
         * value - nothing happens with elements after data_[new_size].  */
        void resize(size_t n, T const & value = T()) {
            if (n > capacity_)
                reserve(n);

            for (int i = size_; i < n; ++i)
                new (data_ + i) T(value);

            size_ = n;
        }

        void shrink_to_fit() {
            if (size == capacity)
                return;

            T * new_data = reinterpret_cast<T *>(new int8_t[size_ * sizeof(T)]);

            for (size_t i = 0; i < size_; ++i)
                new (new_data + i) T(std::move(data_[i]));

            for (size_t i = 0; i < size_; ++i)
                (data_ + i)->~T();

            delete [] reinterpret_cast<int8_t*>(data_);
            data_     = new_data;
            capacity_ = size_;
        }

        // TODO:
        void push_back(T const & value) {
            if (size_ == capacity_)
                reserve(capacity_ * 2);

            // new (data_ + size++) T(value);
        }

        // TODO:
        void emplace_back(T && value) {
            if (size_ == capacity_)
                reserve(capacity_ * 2);

            // new (data_ + size++) T(std::move(value));
        }

        // TODO:
        T & pop_back() {
            return data_[size--];
        }

    protected:
        T * data_;
        // Number of valid elements in data array
        size_t size_;
        // Number of elements that can be stored in memory allocated for data
        size_t capacity_;

        void swap(vector<T> & v) {
            std::swap(data_, v.data_);
            std::swap(size_, v.size_);
            std::swap(capacity_, v.capacity_);
        }
    };
}

#endif
