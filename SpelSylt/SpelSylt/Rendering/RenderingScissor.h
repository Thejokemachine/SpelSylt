#pragma once

namespace SpelSylt
{
	class RenderingScissor
	{
	public:
		static void EnableScissor(bool aEnable = true);

		// (0,0) is bottom left and (windowWidth,windowHeight) is top right.
		static void SetRectangle(int x, int y, int width, int height);

		// (0,0) is bottom left and (windowWidth,windowHeight) is top right.
		static void SetRectangle(float x, float y, float width, float height);
	};
}