#ifndef INCLUDE_OGL_HPP_
#define INCLUDE_OGL_HPP_

namespace ogl{

    class Ogl{
        private:
            Ogl(const Ogl& old) = delete;
            Ogl(Ogl&& old) = delete;
            Ogl& operator=(const Ogl& old) = delete;
            Ogl& operator=(Ogl&& old) = delete;

        public:
            Ogl()noexcept;
            ~Ogl(){};
    };

}

#endif // INCLUDE_OGL_HPP_
