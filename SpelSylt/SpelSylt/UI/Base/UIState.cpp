#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/UI/Base/UIState.h"
#include "SpelSylt/Contexts/GameContext.h"
#include "SpelSylt/UI/Button.h"
#include "SpelSylt/Messaging/Messages/UIMessages.h"
#include "SpelSylt/Messaging/MessageQueue.h"

#include <SFML/Graphics/RenderTarget.hpp>

#ifdef _DEBUG
#include <SpelSylt/FileHandling/FileWatcher.h>
#endif

CFontBank UIState::FontBank;

UIState::UIState(unsigned int aWidth, unsigned int aHeight, const std::string& aLayoutXML) :
	CState(),
	myLayout(std::make_unique<UI::UILayout>((float)aWidth, (float)aHeight, FontBank, aLayoutXML))
{
	SetStateFlags(CState::DRAW_BELOW | CState::UPDATE_BELOW);

#ifdef _DEBUG
	myLayoutFile = aLayoutXML;
	SS::CFileWatcher::AddFile(aLayoutXML.c_str(), [this, aWidth, aHeight](){
		myShouldReload = true;
	});
#endif
}

void UIState::Init(SGameContext& InGameContext)
{
	InGameContext.MessageQueue.Subscribe<SResizedWindowMessage>([this](const SResizedWindowMessage& msg) {
		myLayout->Resize(msg.Param, msg.ParamTwo);
	}, mySubs);

	OnInit(InGameContext);
}

void UIState::Update(SGameContext & InGameContext)
{
	myLayout->Update(&InGameContext.Input);

#ifdef _DEBUG
	if (myShouldReload)
	{
		float width = myLayout->GetWidth();
		float height = myLayout->GetHeight();
		myLayout = nullptr;
		myLayout = std::make_unique<UI::UILayout>(width, height, FontBank, myLayoutFile);
		myShouldReload = false;
		LOG_VERBOSE(UI, "Reloaded UI");
	}
#endif

	OnUpdate(InGameContext);
}

void UIState::Render(sf::RenderTarget& InTarget)
{
	InTarget.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)InTarget.getSize().x, (float)InTarget.getSize().y)));
	myLayout->Render(InTarget);

	OnRender(InTarget);
}
