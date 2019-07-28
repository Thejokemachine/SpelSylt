#pragma once

#include <memory>

namespace sf
{
	class RenderTarget;
}

namespace SpelSylt
{
	class CStateStack;
	struct SGameContext;
	struct SRenderingContext;

	class CState
	{
		friend CStateStack;

	public:

		enum StateFlags : int {
			NONE = 0,
			UPDATE_BELOW = 1,
			DRAW_BELOW = 2,
		};

		CState();
		virtual ~CState();

		void SetOwner(CStateStack* aOwner);
		void SetStateFlags(StateFlags aStateFlags);
		void SetStateFlags(int aStateFlags);

		StateFlags GetStateFlags() const { return myStateFlags; }
		CStateStack* GetStateStack() const { return myOwner; }

		virtual void Init(SGameContext& InGameContext) = 0;
		virtual void Update(SGameContext& InGameContext) = 0;
		virtual void Render(sf::RenderTarget& InTarget) = 0;

	protected:
		bool Pop();
		void PopAll();
		void PopAndPushNew(std::shared_ptr<CState> aNewState);

		void Push(std::shared_ptr<CState> aNewState);

	private:
		CStateStack* myOwner;
		StateFlags myStateFlags;
		bool myShouldPop = false;
		CState* myPendingState = nullptr;
	};
}

namespace SS = SpelSylt;