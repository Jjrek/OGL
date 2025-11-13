#include <gtest/gtest.h>

#include "log.hpp"

#include <string>
#include <sstream>

using ogl::LogType;

using std::string;

class logging : public testing::Test{
	protected:
		std::stringstream stream;

		void SetUp()override{
			ogl::Log::Handle().setOutputStream(&stream);
		}
		void TearDown()override{
			ogl::Log::Handle().setOutputStream(&std::cout);
		}

		string streamContents(){
			return stream.str();
		}
};

TEST_F(logging, write_when_matching_type){
	ogl::Log::Handle().setLoggingFlags(LogType::ERROR);
	string message = "Test of matching error output. \n";

	LOG(LogType::ERROR)<<message;
	EXPECT_EQ(message, streamContents());
}

TEST_F(logging, ignore_when_not_matching_type){
	ogl::Log::Handle().setLoggingFlags(LogType::ERROR);

	LOG(LogType::INFO)<<"Test of mismatched info output. \n";
	EXPECT_EQ(streamContents().empty(), true);
}

TEST_F(logging, passing_or_of_flags){
	//NOLINTNEXTLINE
	ogl::Log::Handle().setLoggingFlags(LogType::ERROR | LogType::INFO);

	string message = "Test of matching error output. \n";
	LOG(LogType::ERROR)<<message;
	EXPECT_EQ(message, streamContents());

	string message2 = "Test of matching info output. \n";
	LOG(LogType::INFO)<<message2;
	EXPECT_EQ(message+message2, streamContents());
}

TEST_F(logging, failing_or_of_flags){
	//NOLINTNEXTLINE
	ogl::Log::Handle().setLoggingFlags(LogType::ERROR | LogType::INFO);

	string message = "Test of failing warning output. \n";
	LOG(LogType::WRN)<<message;
	EXPECT_EQ(streamContents().empty(), true);
}

