#pragma once
#include "Panel.h"

class Button : public Panel
{
	friend class UILayout;

public:

	using Panel::Panel;

	void SetCallback(std::function<void(Button& button)> aOnPressed);

private:

	std::function<void(Button& button)> myOnPressed;

};