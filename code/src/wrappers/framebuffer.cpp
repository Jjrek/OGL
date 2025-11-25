#include "wrappers/framebuffer.hpp"

namespace ogl {

	Framebuffer::Framebuffer()noexcept{
		glGenFramebuffers(1, &id);
	}

	Framebuffer::~Framebuffer(){
		glDeleteFramebuffers(1, &id);
	}

	void Framebuffer::bind(){
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void Framebuffer::bindDefault(){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}
