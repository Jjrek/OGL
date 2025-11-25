#ifndef INCLUDE_OGL_HPP_
#define INCLUDE_OGL_HPP_

#include "./wrappers/window.hpp"
#include "./wrappers/program.hpp"

#include <memory>

///@brief Library namespace
namespace ogl{

    class ObjectFactory{
            friend class Ogl;
        protected:
            ObjectFactory()noexcept{};
        public:
            template<typename T, typename... Args>
                T create(Args&&... args){
                    return {std::forward<Args>(args)...};
                }

            template<typename T, typename... Args>
                std::shared_ptr<T> createPointer(Args&&... args){
                    //Using new due to private constructors
                    //NOLINTNEXTLINE
                    return std::shared_ptr<T>{new T(std::forward<Args>(args)...)};
                }
    };

    class Ogl{
        private:
            bool isValid = true;
            std::shared_ptr<Window> window_i;

            Ogl(const Ogl& old) = delete;
            Ogl(Ogl&& old) = delete;
            Ogl& operator=(const Ogl& old) = delete;
            Ogl& operator=(Ogl&& old) = delete;

        public:
            Ogl(std::string windowTitle = "title",
                glm::uvec2 windowSize = {480,320})noexcept;
            ~Ogl();
			operator bool(){return isValid;}

            std::shared_ptr<ObjectFactory> factory(){
                        //Using new due to private constructor
                        //NOLINTNEXTLINE
                        return isValid  ?std::shared_ptr<ObjectFactory>(new ObjectFactory)
                                        :nullptr;}

            std::shared_ptr<Window> window(){return window_i;}
    };

}

#endif // INCLUDE_OGL_HPP_
