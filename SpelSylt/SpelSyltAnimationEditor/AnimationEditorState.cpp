#include "AnimationEditorState.h"

#include <SpelSylt/UI/Base/UILayout.h>
#include <Spelsylt/UI/Button.h>
#include <SpelSylt/UI/Label.h>
#include <SpelSylt/UI/Panel.h>
#include <SpelSylt/UI/List.h>
#include <SpelSylt/UI/Slider.h>
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
using namespace SpelSylt;

AnimationEditorState::AnimationEditorState(unsigned width, unsigned int height, const std::string & aLayoutXML) :
	UIState(width, height, aLayoutXML)
{
}

void AnimationEditorState::OnInit(SGameContext & InGameContext)
{
	frameList = myLayout->GetList("frame_list");

	if (auto btn = myLayout->GetButton("play_btn")) {
		btn->SetCallback([this](Button& button) {
			isPlaying = !isPlaying;
		});
	}

	slider = myLayout->GetSlider("playrate_slider");

	animCenter = myLayout->GetPanel("center");

	if (auto p = myLayout->GetPanel("clip_image")) {
		animation.setMaxSize(p->GetWidth(), p->GetHeight());
	}

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
			std::string filePath = openFileDialog();
			if (!filePath.empty())
			{
				std::filesystem::path p(filePath);
				animation.addFrame(p.string(), 0.25f);

				if (auto label = myLayout->GetLabel("clip_bg_text")) {
					label->SetText("");
				}
				if (frameList)
				{
					auto item = frameList->AddItem("frame");
					item->GetPanel("image")->SetImage(p.string(), true);
				}
			}
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
#include <iostream>
void AnimationEditorState::OnUpdate(SGameContext & InGameContext)
{
	if (isPlaying) {
		animation.tick(InGameContext.Time.GetDeltaTime());
	}

	if (animCenter) {
		animation.setPosition(animCenter->GetX(), animCenter->GetY());
	}

	if (slider) {
		animation.setGlobalSpeed(1.f/60.f + 1.f/5.f * (1.f-slider->GetValue()));
	}
}

void AnimationEditorState::OnRender(sf::RenderTarget& target)
{
	target.draw(animation);
}

std::string AnimationEditor::AnimationEditorState::openFileDialog()
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

	std::string path = "";

	if (GetOpenFileNameA(&ofn))
	{
		path = filename;
	}
	else
	{
		LOG_ERROR(Error, "You messed up, yo");
	}

	_chdir(dir);

	return filename;
}
