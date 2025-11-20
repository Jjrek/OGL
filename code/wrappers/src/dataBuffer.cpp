#include "dataBuffer.hpp"

#include <cstring>

namespace ogl {

	DataBuffer::DataBuffer(std::shared_ptr<GLInterface> interface)noexcept{
		gl = interface;
		gl->glCreateBuffers(1, &id_i);
		data_i = nullptr;
		size_i = 0;

		bindingPoint_i = -1;
		memoryUsageHint = GL_STATIC_DRAW;
	}

	DataBuffer::~DataBuffer(){
		clear();
		gl->glDeleteBuffers(1, &id_i);
		id_i = 0;
	}

	unsigned DataBuffer::bindingPoint(){
		static int nextBindingPoint = 0;
		if(bindingPoint_i<0) bindingPoint_i = nextBindingPoint++;
		return bindingPoint_i;
	}

	void DataBuffer::feed( void* pDataptr, size_t size){
		if(pDataptr == nullptr)return;

		char* newArray = new char[(DataBuffer::size_i+size)];

		memcpy(newArray, data_i, size_i);
		memcpy(newArray + size_i, pDataptr, size);
		size_i += size;

		delete[] data_i;
		data_i = newArray;
	}

	void DataBuffer::feed( void* pDataptr, size_t size, unsigned long offset){
		if(pDataptr == nullptr)return;

		if(offset+size > size_i){
			char* newArray = new char[(offset+size)];

			if(offset > size_i){
				memcpy(newArray, data_i, size_i);
			}else{
				memcpy(newArray, data_i, offset);
			}

			memcpy(newArray + offset, pDataptr, size);
			size_i = offset + size;

			delete[] data_i;
			data_i = newArray;
		}else{
			memcpy(data_i+offset, pDataptr, size);
		}
	}

	void DataBuffer::pass(void* pDataptr, size_t size){
		gl->glNamedBufferData(id_i, size, pDataptr, memoryUsageHint);
	}

	void DataBuffer::pass(void* pDataptr, size_t size, unsigned long offset){
		gl->glNamedBufferSubData(id_i, offset, size, pDataptr);
	}

	void DataBuffer::push(){
		pass(data_i, size_i);
	}

	void DataBuffer::clear(){
		delete[] data_i;
		data_i = nullptr;
		size_i = 0;
	}

}
