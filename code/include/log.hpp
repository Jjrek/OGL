#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

#include <iostream>

namespace ogl{
	enum class LogType : unsigned short
		{	NONE	= 0,
			INFO	= 1<<0,
			ERROR	= 1<<1,
			WRN		= 1<<2,
			SHADER	= 1<<3,
			CONSTRUC= 1<<4,
			DESTRUCT= 1<<5,
			ALL		= 255};
	inline LogType operator|(LogType lType, LogType rType){
		using Type = std::underlying_type<LogType>::type;
		return LogType(static_cast<Type>(lType) | static_cast<Type>(rType));
	}
	inline LogType operator&(LogType lType, LogType rType){
		using Type = std::underlying_type<LogType>::type;
		return LogType(static_cast<Type>(lType) & static_cast<Type>(rType));
	}

	/**
	@brief Class providing logging utility,
	 by default outputs only ERROR type logs to standard output
	*/
	class Log{
		private:
			std::ostream* output;
			class NullBuffer : public std::streambuf{
				public:
				  int overflow(int c) { return c; }
			}nullbuffer;
			std::ostream nullstream;
			LogType loggingFlags;

			Log()noexcept;
			Log(const Log& old) = delete;
			Log(Log&& old) = delete;
			Log& operator=(const Log& old) = delete;
			Log& operator=(Log&& old) = delete;

		public:
			~Log(){};

			///@brief Handle to singleton object.
			static Log& Handle(){ static Log myInstance; return myInstance; };

			/**@brief Output retrieve function, returns cout by default.
			 If passed type is not enabled, returns dummy stream ignoring all data.
			*/
			std::ostream& get(const LogType);
			///@brief Method defining which log types will be written to output.
			void setLoggingFlags(const LogType type){ loggingFlags = type; };
			///@brief Method defining logging output stream.
			void setOutputStream(std::ostream* stream){ output = stream; };
	};

	///@brief Helper function returning result of Log::Handle().get(type) .
	std::ostream& LOG(const LogType);

}
#endif // INCLUDE_LOG_HPP_
