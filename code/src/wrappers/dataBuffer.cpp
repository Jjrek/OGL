#include "wrappers/dataBuffer.hpp"
#include "log.hpp"

#include <cstring>

namespace ogl {

	DataBuffer::DataBuffer(std::shared_ptr<GLInterface> interface)noexcept{
		gl = interface;
		gl->glCreateBuffers(1, &id_i);
		data_i = nullptr;
		size_i = 0;

		uboBindingPoint_i = -1;
		ssboBindingPoint_i = -1;
		memoryUsageHint = GL_STATIC_DRAW;
		LOG(LogType::CONSTRUC)<<"buffer id:"<<id_i<<"\n";
	}

	DataBuffer::~DataBuffer(){
		clear();
		gl->glDeleteBuffers(1, &id_i);
		LOG(LogType::DESTRUCT)<<"buffer id:"<<id_i<<"\n";
		id_i = 0;
	}

	unsigned DataBuffer::bindingPoint(GLenum target){
		static int nextUBOBindingPoint = 0;
		static int nextSSBOBindingPoint = 0;
		if(target == GL_UNIFORM_BUFFER){
			if(uboBindingPoint_i<0){
				uboBindingPoint_i = nextUBOBindingPoint++;
				gl->glBindBufferBase(target, uboBindingPoint_i, id_i);
			}
			return uboBindingPoint_i;
		}else if(target == GL_SHADER_STORAGE_BUFFER){
			if(ssboBindingPoint_i<0){
				ssboBindingPoint_i = nextSSBOBindingPoint++;
				gl->glBindBufferBase(target, ssboBindingPoint_i, id_i);
			}
			return ssboBindingPoint_i;
		}
		return 0;
	}

	void DataBuffer::bind(GLenum target){
		gl->glBindBuffer(target, id_i);
	}

	void DataBuffer::feed(const void* const pDataptr, size_t size){
		if(pDataptr == nullptr)return;

		char* newArray = new char[(DataBuffer::size_i+size)];

		memcpy(newArray, data_i, size_i);
		memcpy(newArray + size_i, pDataptr, size);
		size_i += size;

		delete[] data_i;
		data_i = newArray;
	}

	void DataBuffer::feed(const void* const pDataptr, size_t size, unsigned long offset){
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

	void DataBuffer::pass(const void* const pDataptr, size_t size )const{
		gl->glNamedBufferData(id_i, size, pDataptr, memoryUsageHint);
	}

	void DataBuffer::pass(const void* const pDataptr, size_t size, unsigned long offset)const{
		gl->glNamedBufferSubData(id_i, offset, size, pDataptr);
	}

	void DataBuffer::push()const{
		pass(data_i, size_i);
	}

	void DataBuffer::clear(){
		delete[] data_i;
		data_i = nullptr;
		size_i = 0;
	}

}
