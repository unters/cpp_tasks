/**     string.cpp
 * 
 * Description
 * This file contains declarations of al::string methods from string.hpp.
 **/

#include "./string.hpp"


namespace al {
    string::string() noexcept               /* elements of char[]  */
        : size_(1), data_(new char[1]) {}   /* are \0 by default.  */
                                             

    string::~string() noexcept { delete [] data_; }


    string::string(string const & s)
        : size_(s.size_), data_(new char[size_])
    {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = s[i];
    }


    string::string(string && s) noexcept
        : size_(s.size_), data_(s.data_) { s.data_ = nullptr; }


    string::string(char const * c) 
        : size_(strlen(c) + 1), data_(new char[size_]) 
    {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = c[i];
    }


    string & string::operator=(string const & s) {  /* TODO: use al::swap.  */
        if (this == &s)
            return *this;

        delete [] data_;
        size_ = s.size_;
        data_ = new char[size_];

        for (size_t i = 0; i < size_; ++i)
            data_[i] = s.data_[i];

        return *this;
    }


    string & string::operator=(string && s) noexcept {  /* TODO: use al::swap.  */
        if (this == &s)
            return *this;

        delete [] data_;
        size_ = s.size_;
        data_ = s.data_, s.data_ = nullptr;
        /* s.data_ is not a valid null-terminated string anymore, but its
         * must be ok.  */

        std::cout << "Rvalue operator=!";

        return *this;
    }


    char string::operator[](size_t i) const { return data_[i]; }
    

    char & string::operator[](size_t i) { return data_[i]; }


    string::operator bool() const {
        return size_ - 1;
    }


    string::operator char const * () const {
        if (*this)
            return data_;

        return "";
    }


    size_t string::length() const noexcept { return size_ - 1; }


    void string::clear() {
        delete [] data_;

        size_ = 1;
        data_ = new char[1];
    }


    bool string::empty() { return !(size_ - 1); }


    char * string::data() noexcept { return data_; }


    char const * string::c_str() const noexcept { return data_; }


    // string & operator+(string const &, string const &);


    std::ostream & operator<<(std::ostream & os, string const & s) {
        os << s.data_;
        return os;
    }


    std::istream & operator>>(std::istream & is, string & s) {
        s.clear();
        
        size_t size = 128;
        size_t i    = 0;
        char * c    = new char[size];

        while(is.get(c[i])) {
            if (c[i] == ' ' || c[i] == '\n' || c[i] == '\0') 
                break;

            if (++i >= size) {
                size *= 2;
                char * cd = new char[size];
                strcpy(cd, c);
                delete [] c;
                c = cd;
            }
        }

        if (c[i] != '\0') {
            s.size_ = size + 1;
            s.data_ = new char[s.size_];

            for (i = 0; i < size; ++i)
                s.data_[i] = c[i];

            s.data_[size] = '\0';
        }

        else {
            s.size_ = size;
            s.data_ = new char[s.size_];

            for (i = 0; i < size; ++i)
                s.data_[i] = c[i];
        }

        return is;
    }
}