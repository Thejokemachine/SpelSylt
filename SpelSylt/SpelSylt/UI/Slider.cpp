#include "SpelSylt/SpelSyltPCH.h"
#include "Slider.h"

#include <XMLUtilities.h>
#include <Math/CommonMath.h>
#include "Base/UILayout.h"

UI::Slider::Slider(UILayout & aLayout, const Panel * aParent, tinyxml2::XMLElement & aElement) :
	UI::Panel(aLayout, aParent, aElement),
	myValue(0.f),
	myIsVertical(false)
{
	XMLUtilities::QueryAttribute(aElement, "default_value", myValue);
	XMLUtilities::QueryAttribute(aElement, "vertical", myIsVertical);

	myCursor = GetPanel("cursor");

	if (myCursor) {
		float y = -myCursor->GetHeight() * 0.5f;
		float x = -myCursor->GetWidth() * 0.5f;

		const float maxY = GetY() + GetHeight() - myCursor->GetHeight();
		const float maxX = GetX() + GetWidth() - myCursor->GetWidth();

		y = Math::Clamp(y, GetY(), maxY);
		x = Math::Clamp(x, GetX(), maxX);

		if (myIsVertical) {
			myCursor->SetBounds(-1.f, y, -1.f, -1.f);
			myValue = (y - GetY()) / (maxY - GetY());
		}
		else {
			myCursor->SetBounds(x, -1.f, -1.f, -1.f);
			myValue = (x - GetX()) / (maxX - GetX());
		}
	}
}

float UI::Slider::GetValue() const
{
	return myValue;
}

void UI::Slider::onUpdate(const float dt)
{
}

void UI::Slider::onHover()
{
	if (!myCursor)
		return;

	auto& input = myLayout.GetInputManager();
	if (input.IsKeyDown(EKeyCode::MouseLeft))
	{
		float y = input.GetMousePosFloat().y - myCursor->GetHeight() * 0.5f;
		float x = input.GetMousePosFloat().x - myCursor->GetWidth() * 0.5f;

		const float maxY = GetY() + GetHeight() - myCursor->GetHeight();
		const float maxX = GetX() + GetWidth() - myCursor->GetWidth();

		y = Math::Clamp(y, GetY(), maxY);
		x = Math::Clamp(x, GetX(), maxX);

		if (myIsVertical) {
			myCursor->SetBounds(-1.f, y, -1.f, -1.f);
			myValue = (y - GetY()) / (maxY - GetY());
		}
		else {
			myCursor->SetBounds(x, -1.f, -1.f, -1.f);
			myValue = (x - GetX()) / (maxX - GetX());
		}
	}
}

void UI::Slider::onLayout()
{
}
