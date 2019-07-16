#include "AnimationEditorState.h"

#include <SpelSylt/UI/Base/UILayout.h>
#include <Spelsylt/UI/Button.h>
#include <SpelSylt/UI/Label.h>
#include <SpelSylt/UI/Panel.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>
#include <SpelSylt/Utility/Time/Time.h>
#include <SpelSylt/UI/UIUtilities.h>
#include <SpelSylt/Debugging/Logging/DebugLogger.h>

#include "AnimationEditorMessages.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Needed for opening file dialog
#pragma comment(lib, "comdlg32.lib")
#include <windows.h>
#include <filesystem>
#include <direct.h>

using namespace AnimationEditor;
using namespace UI;

AnimationEditorState::AnimationEditorState(unsigned width, unsigned int height, const std::string & aLayoutXML) :
	UIState(width, height, aLayoutXML)
{
	if (auto btn = myLayout->GetButton("play_btn")) {
		btn->SetCallback([this](Button& button) {
			isPlaying = !isPlaying;
		});
	}

	animCenter = myLayout->GetPanel("center");
}

void AnimationEditorState::OnInit(SGameContext & InGameContext)
{
	if (auto btn = myLayout->GetButton("speed_val_up")) {
		btn->SetCallback([&InGameContext](Button& button) {
			InGameContext.MessageQueue.DispatchEvent<IncrementSpeedMessage>(0.05f);
		});
	}
	if (auto btn = myLayout->GetButton("speed_val_down")) {
		btn->SetCallback([&InGameContext](Button& button) {
			InGameContext.MessageQueue.DispatchEvent<IncrementSpeedMessage>(-0.05f);
		});
	}
	if (auto btn = myLayout->GetButton("add_frame_btn")) {
		btn->SetCallback([&](Button& button) {
			openFileDialog();
		});
	}

	InGameContext.MessageQueue.Subscribe<IncrementSpeedMessage>([this](const auto& msg) {
		if (auto label = myLayout->GetLabel("speed_val")) {
			float currValue = std::stof(label->GetText());
			currValue += msg.Param;
			label->SetText(UIUtilities::FormatFloat(2, currValue));
			animation.setGlobalSpeed(currValue);
		}
	}, mySubs);
}

void AnimationEditorState::OnUpdate(SGameContext & InGameContext)
{
	if (isPlaying) {
		animation.tick(InGameContext.Time.GetDeltaTime());
	}

	if (animCenter) {
		animation.setPosition(animCenter->GetX(), animCenter->GetY());
	}
}

void AnimationEditorState::OnRender(sf::RenderTarget& target)
{
	target.draw(animation);
}

void AnimationEditor::AnimationEditorState::openFileDialog()
{
	char dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, dir);

	char filename[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = "Images\0*.png\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select an image.";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::filesystem::path p(filename);
		animation.addFrame(p.filename().string(), 0.25f);
		
		if (auto label = myLayout->GetLabel("clip_bg_text")) {
			label->SetText("");
		}
	}
	else
	{
		LOG_ERROR(Error, "You messed up, yo");
	}

	_chdir(dir);
}
