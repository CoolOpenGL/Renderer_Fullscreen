#ifdef __COOL_APP_OPENGL

#include "Renderer_Fullscreen.h"

#include <Cool/App/RenderState.h>

namespace Cool {

Renderer_Fullscreen::Renderer_Fullscreen() {
	RenderState::SubscribeToSizeChanges([this]() { onRenderAreaResized(); });
	GLDebug(glGenVertexArrays(1, &m_dummyVaoID));
}

Renderer_Fullscreen::~Renderer_Fullscreen() {
	GLDebug(glDeleteVertexArrays(1, &m_dummyVaoID));
}

void Renderer_Fullscreen::begin() {
	m_renderBuffer.bind();
}

void Renderer_Fullscreen::end() {
	m_renderBuffer.blitTo(
		RenderState::SwapYConvention(RenderState::InAppRenderArea().botLeft()),
		RenderState::SwapYConvention(RenderState::InAppRenderArea().topRight()),
		SCREEN_FRAMEBUFFER_ID,
		RenderState::preview_interpolation_mode()
	);
	m_renderBuffer.unbind();
}

void Renderer_Fullscreen::render() {
	// We use a smart trick to render fullscreen, as explained here : https://stackoverflow.com/a/59739538
	GLDebug(glBindVertexArray(m_dummyVaoID));
	GLDebug(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Renderer_Fullscreen::onRenderAreaResized() {
	const glm::ivec2& size = RenderState::Size().size();
	if (size.x != 0 && size.y != 0)
		m_renderBuffer.setSize(size);
}

} // namespace Cool

#endif