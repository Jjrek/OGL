#ifndef INCLUDE_OGL_PROGRAM_HPP_
#define INCLUDE_OGL_PROGRAM_HPP_

#include "GLInterface.hpp"
#include "shader.hpp"
#include "variable.hpp"
#include "log.hpp"

#include <memory>
#include <vector>
#include <map>

namespace ogl{

	///@brief Wrapper class containing single OpenGL program
	class Program{
			friend class ObjectFactory;
		private:
			bool isValid;

			std::shared_ptr<GLInterface> gl;
			GLuint id;
			GLuint vertexArrayID;

			std::map<std::string, std::shared_ptr<Variable>> variables;

			Program(const Program& old) = delete;
			Program(Program&& old) = delete;
			Program& operator=(const Program& old) = delete;
			Program& operator=(Program&& old) = delete;

			void poll(GLenum resourceType, auto factory);
			void pollVariables();

		protected:
			///@param interface - Interface for OpenGL calls.
			Program(std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;

		public:
			~Program();
			operator bool(){return isValid;}

			///@brief Builds and links passed shaders into program.
			bool build(const std::vector<std::shared_ptr<Shader>>& shaders);

			///@brief Activates program.
			void activate();

			///@brief Returns stored variable wrapper or empty pointer if not found.
			std::shared_ptr<Variable> get(std::string varName);

			///@brief Returns stored variable wrapper with type casting or empty pointer if not found or not matching.
			template<typename T>
			std::shared_ptr<T> get(std::string varName){
				auto p = std::dynamic_pointer_cast<T>(get(varName));
				if(!p)LOG(ogl::LogType::WRN)<<"Program "
										<<id
										<<" does not contain variable "
										<<varName
										<<" or types not match\n";
				return p;
			}
	};

}
#endif // INCLUDE_OGL_PROGRAM_HPP_
