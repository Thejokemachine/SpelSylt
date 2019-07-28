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

		void Push(std::shared_ptr<CState> aNewState);
		bool Pop();
		void PopAll();
		void PopAndPush(std::shared_ptr<CState> aNewState);

		short Size();

	private:
		std::vector<std::shared_ptr<CState>> myStates;
		std::vector<std::shared_ptr<CState>> myStatesToPush;
	};
}

namespace SS = SpelSylt;