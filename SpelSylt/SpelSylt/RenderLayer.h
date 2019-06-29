#pragma once

//Layers in here should be ordered as they should be rendererd (First enumerated element will be drawn first and so on)
enum class ERenderLayer
{
	Background,
	Game,
	Foreground,
	UI,
	Count, //Do not use this!
};