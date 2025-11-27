#ifndef INCLUDE_OGL_DATA_BUFFER_HPP_
#define INCLUDE_OGL_DATA_BUFFER_HPP_

#include "GLInterface.hpp"

#include <memory>
#include <vector>

namespace ogl {

	///@brief Wrapper class for OpenGL buffer
	class DataBuffer{
			friend class ObjectFactory;
		private:
			std::shared_ptr<GLInterface> gl;
			GLuint id_i;
			char* data_i;
			size_t size_i;

			int uboBindingPoint_i;
			int ssboBindingPoint_i;

			DataBuffer(const DataBuffer& old) = delete;
			DataBuffer(DataBuffer&& old) = delete;
			DataBuffer& operator=(const DataBuffer& old) = delete;
			DataBuffer& operator=(DataBuffer&& old) = delete;

		protected:
			DataBuffer(std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;

		public:
			GLenum memoryUsageHint;

			virtual ~DataBuffer();

			///@brief Getter for buffer id
			virtual GLuint id(){return id_i;}
			///@brief Getter for buffer size
			GLuint size(){return size_i;}

			///@brief Returns related binding point, attaches to next unused if not yet connected
			///@param target - target for which binding point should be returned, GL_UNIFORM_BUFFER or GL_SHADER_STORAGE_BUFFER are accepted
			virtual unsigned bindingPoint(GLenum target);

			///@brief Binds buffer to passed target
			void bind(GLenum target);

			///@brief Appends data from passed vector to temporary buffer
			template<typename T>void feed(std::vector<T> data){
				feed(data.data(), sizeof(T)*data.size());}
			///@brief Appends 'size' bytes from 'pDataptr' to temporary buffer
			void feed( void* pDataptr, size_t size);
			///@brief Copies 'size' bytes from 'pDataptr' to temporary buffer
			///at 'offset' from begining, extends buffer if necessary
			void feed( void* pDataptr, size_t size, unsigned long offset);

			///@brief Passes data from passed vector to OpenGL buffer
			template<typename T>void pass(std::vector<T> data){
				pass(data.data(), sizeof(T)*data.size());}
			///@brief Creates new OpenGL buffer storage with 'size' bytes of data from 'pDataptr'
			void pass(void* pDataptr, size_t size);
			///@brief Passes 'size' bytes from 'pDataptr' to OpenGL buffer with 'offset'
			void pass(void* pDataptr, size_t size, unsigned long offset);

			///@brief Creates new OpenGL buffer storage with data from temporary buffer
			void push();

			///@brief Clears temporary buffer
			void clear();
	};
}

#endif // INCLUDE_OGL_DATA_BUFFER_HPP_
