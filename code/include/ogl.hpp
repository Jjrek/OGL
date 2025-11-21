#ifndef INCLUDE_OGL_HPP_
#define INCLUDE_OGL_HPP_

#include "window.hpp"

#include <memory>

///@brief Library namespace
namespace ogl{

    class Ogl{
        private:
            bool isValid = true;
            std::shared_ptr<Window> window_i;

            Ogl(const Ogl& old) = delete;
            Ogl(Ogl&& old) = delete;
            Ogl& operator=(const Ogl& old) = delete;
            Ogl& operator=(Ogl&& old) = delete;

        public:
            Ogl()noexcept;
            ~Ogl();
			operator bool(){return isValid;}

            std::shared_ptr<Window> window(){return window_i;}
    };

}

#endif // INCLUDE_OGL_HPP_
