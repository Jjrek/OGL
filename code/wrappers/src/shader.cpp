#include "shader.hpp"
#include "log.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using ogl::Shader;

using std::istringstream;
using std::string;
using std::set;
using std::vector;

void extractFlags(set<string>& flags, const string line){
	istringstream lineStream(line);
	for(string line; std::getline(lineStream, line, ' ');){
		if(!line.empty()){
			flags.insert(line);
		}
	}
}

bool flagsMatchCurrentShader(set<string>& flags,
							 const set<string>& compileFlags){
	for(auto& flag : flags){
		if(	(flag[0] == '~' && !compileFlags.contains(flag.substr(1))) ||
			compileFlags.contains(flag))
		{
			return true;
		}
	}
	return false;
}

string removeInactiveBlocks( const string code,
							 const set<string>& compileFlags)noexcept{
	vector<set<string>> openedBlocks;
	istringstream codeStream(code);
	string processedCode, processedLine;
	int mismatchedBlocks = 0;

	for(string line; std::getline(codeStream, line);){
		//remove indentation
		processedLine = line.substr(line.find_first_not_of(" \t"));
		std::replace(processedLine.begin(), processedLine.end(), '\t', ' ');

		if(processedLine[0] == '@'){
			if(processedLine[1] == '!'){
				//remove tag
				processedLine = line.substr(2);
				set<string> closingFlags;
				extractFlags(closingFlags, processedLine);
				if(!flagsMatchCurrentShader(closingFlags, compileFlags)){
					--mismatchedBlocks;
				}
				if( mismatchedBlocks < 0 ||
					openedBlocks.back() != closingFlags){
					LOG(ogl::LogType::ERROR)<<"Mismatched blocks!\n";
					return "";
				}
				openedBlocks.pop_back();

			}else{
				//remove tag
				processedLine = line.substr(1);
				extractFlags(openedBlocks.emplace_back(), processedLine);
				if(!flagsMatchCurrentShader(openedBlocks.back(), compileFlags)){
					++mismatchedBlocks;
				}
			}
		}else{
			if(mismatchedBlocks == 0)processedCode += line+'\n';
		}
	}
	return processedCode;
}

string addLineNumbers(const char code[]){
	string codeWithLineNumbers;
	istringstream codeStream(code);
	int i = 1;
	for(string line; std::getline(codeStream, line);++i){
		codeWithLineNumbers +="||"+
						string(i<10?"  ":(i<100?" ":""))+std::to_string(i)+
						"|| "+line+"\n";
	}
	return codeWithLineNumbers;
}

Shader::Shader( const GLenum shaderType,
				const string rawCode,
				const set<string>& compileFlags,
				std::unique_ptr<GLInterface> interface)noexcept:gl(std::move(interface)){
	code = removeInactiveBlocks(rawCode, compileFlags);
	isValid = !code.empty();
	if(!isValid) return;

	type = shaderType;
	id = gl->glCreateShader(shaderType);
	gl->glShaderSource(id, code.c_str());
	gl->glCompileShader(id);
	GLint succes;
	gl->glGetShaderiv(id, GL_COMPILE_STATUS, &succes);
	if(!succes){
		isValid = false;
		GLint length;
		gl->glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		vector<char> info(length);
		gl->glGetShaderInfoLog(id, length, &length, info.data());

		gl->glGetShaderiv(id, GL_SHADER_SOURCE_LENGTH, &length);
		vector<char> source(length);
		gl->glGetShaderSource(id, length, &length, source.data());
		gl->glDeleteShader(id);
		LOG(LogType::ERROR)<<info.data()<<"\n\n"<<addLineNumbers(source.data());
	}
}

Shader::~Shader(){
	if(isValid)gl->glDeleteShader(id);
}
