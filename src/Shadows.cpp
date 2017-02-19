#include "Shadows.h"
#include <iostream>


namespace basicgraphics {
	namespace shadows {
		// Hold id of the framebuffer for light POV rendering
		GLuint fboId;

		// Z values will be rendered to this texture when using fboId framebuffer
		GLuint depthTextureId;
		void anAttempt() {
			// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
			//GLuint FramebufferName = 0;
			glGenFramebuffers(1, &fboId);
			glBindFramebuffer(GL_FRAMEBUFFER, fboId);

			// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
			//GLuint depthTexture;
			glGenTextures(1, &depthTextureId);
			glBindTexture(GL_TEXTURE_2D, depthTextureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1920/4, 1080/4, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0); // altered
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTextureId, 0);

			glDrawBuffer(GL_NONE); // No color buffer is drawn to.

								   // Always check that our framebuffer is ok
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				throw "framebuffer error";
		}
	}
}
