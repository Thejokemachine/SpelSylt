#pragma once
#include <vector>

namespace sf
{
	class Window;
}

namespace SpelSylt
{
	class CState;
	struct SGameContext;
	struct SRenderingContext;


	class CStateStack
	{
	public:
		CStateStack();
		~CStateStack();

		void Update(SGameContext& InGameContext);
		void Render(sf::RenderTarget& InTarget);

		void Push(CState* aNewState, SGameContext& InGameContext);
		bool Pop();
		void PopAll();

		short Size();

	private:
		std::vector<CState*> myStates;
	};
}

namespace SS = SpelSylt;