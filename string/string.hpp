/**     string.hpp
 * 
 * Description
 * This file contains daclaration of class al::string - "parody" of 
 * std::string made for academic purposes.
 * 
 * Notes
 * 
 * 1. al::string uses char array data_ as data storage. Throughout the 
 * lifecycle of any al::string object, data_ is a valid nullterminated 
 * cstring except for the situation, when such an object has been given as
 * rvalue reference. As far as I undestand, this is the only way to make 
 * c_str() work in O(1) time.
 * 
 * 2. I'm not sure if there is any better way to overload operator>>.
 * 
 * 3. I have declared only 
 **/

#ifndef AL_STRING
#define AL_STRING

#include <iostream>
#include <cstring>

#include <stddef.h>


namespace al {
    class string {
        public:
            string() noexcept;
            ~string() noexcept;

            string(string const &);
            string(string &&) noexcept;

            string(char const * );

            string & operator=(string const &);
            string & operator=(string &&) noexcept;

            char    operator[](size_t) const;
            char &  operator[](size_t);

            operator bool () const;
            operator char const * () const;
            size_t length() const noexcept;

            void clear();
            bool empty();

            char * data() noexcept;
            char const * c_str() const noexcept;

        private:
            size_t  size_;
            char *  data_;

            friend std::ostream & operator<<(std::ostream &, string const &);
            friend  std::istream & operator>>(std::istream &, string &);
    };

    // string & operator+(string const &, string const &);

    std::ostream & operator<<(std::ostream &, string const &);

    std::istream & operator>>(std::istream &, string const &);
}

#endif

