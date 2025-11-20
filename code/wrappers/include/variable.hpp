#ifndef INCLUDE_ENTRY_HPP_
#define INCLUDE_ENTRY_HPP_

#include "dataBuffer.hpp"

#include <memory>

namespace ogl{

	///@brief Base for wrapper class,
	///containing single OpenGL program input
	class Variable{
		friend class Program;
		private:
			Variable() = delete;
			Variable(const Variable& old) = delete;
			Variable(Variable&& old) = delete;
			Variable& operator=(const Variable& old) = delete;
			Variable& operator=(Variable&& old) = delete;

		protected:
			std::shared_ptr<GLInterface> gl;
			struct Params{
				GLuint address;
				GLint variableType;
				GLuint programId;
			}params;

		public:
			Variable(Params params, std::shared_ptr<GLInterface> interface)noexcept;
			virtual ~Variable(){};
	};

	///@brief Wrapper class containing uniform input
	class Uniform : public Variable{
		private:
			Uniform() = delete;
			Uniform(const Uniform& old) = delete;
			Uniform(Uniform&& old) = delete;
			Uniform& operator=(const Uniform& old) = delete;
			Uniform& operator=(Uniform&& old) = delete;

		public:
			Uniform(Params params, std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;
			~Uniform(){};

			///@brief Writes to contained variable
			void pass(void* pDataptr);
	};

	///@brief Base for buffer backed OpenGL program input
	class Buffered : public Variable{
		private:
			Buffered() = delete;
			Buffered(const Buffered& old) = delete;
			Buffered(Buffered&& old) = delete;
			Buffered& operator=(const Buffered& old) = delete;
			Buffered& operator=(Buffered&& old) = delete;

		protected:
			std::shared_ptr<DataBuffer> buffer;

		public:
			Buffered(Params params, std::shared_ptr<GLInterface> interface)noexcept;
			virtual ~Buffered(){};

			///@brief Connects contained variable with passed buffer
			virtual void attachBuffer(std::shared_ptr<DataBuffer> buffer) = 0;
	};

	///@brief Wrapper class containing attribute input
	class Attribute : public Buffered{
		private:

			Attribute() = delete;
			Attribute(const Attribute& old) = delete;
			Attribute(Attribute&& old) = delete;
			Attribute& operator=(const Attribute& old) = delete;
			Attribute& operator=(Attribute&& old) = delete;

		public:
			Attribute(Params params, std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;
			~Attribute(){};

			void attachBuffer(std::shared_ptr<DataBuffer> buffer)final;

			///@brief Defines instance divisor for contained variable
			void MakeAtributeInstanced(int divisor);
	};

	///@brief Wrapper class containing uniform block or shader storage block input
	class Buffer_Block : public Buffered{
		private:
			Buffer_Block() = delete;
			Buffer_Block(const Buffer_Block& old) = delete;
			Buffer_Block(Buffer_Block&& old) = delete;
			Buffer_Block& operator=(const Buffer_Block& old) = delete;
			Buffer_Block& operator=(Buffer_Block&& old) = delete;

		public:
			Buffer_Block(Params params, std::shared_ptr<GLInterface> interface = std::make_unique<GL>())noexcept;
			~Buffer_Block(){};

			void attachBuffer(std::shared_ptr<DataBuffer> buffer)final;
	};
}

#endif // INCLUDE_ENTRY_HPP_
