#include "log.hpp"

#include <iostream>

namespace ogl{

	Log::Log()noexcept:nullstream(&nullbuffer){
		output = &std::cout;
		loggingFlags = LogType::ERROR;
	}

	std::ostream& Log::get(const LogType type){
		if(static_cast<bool>(loggingFlags & type) && output){
			if(static_cast<bool>(type&LogType::CONSTRUC))
				(*output)<<"HI! ";
			if(static_cast<bool>(type&LogType::DESTRUCT))
				(*output)<<"BYE! ";
			return *output;
		}else{
			return nullstream;
		}
	}

	std::ostream& LOG(const LogType type){
			return Log::Handle().get(type);
	}

}
