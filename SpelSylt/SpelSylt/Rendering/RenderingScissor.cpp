#include "SpelSylt/SpelSyltPCH.h"
#include "RenderingScissor.h"
#include "OpenGL.h"

void SpelSylt::RenderingScissor::EnableScissor(bool aEnable)
{
	if (aEnable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void SpelSylt::RenderingScissor::SetRectangle(int x, int y, int width, int height)
{
	glScissor(x, y, width, height);
}

void SpelSylt::RenderingScissor::SetRectangle(float x, float y, float width, float height)
{
	SetRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height));
}
