#ifndef TILETYPE_H
#define TILETYPE_H

#include "Globals.h"

enum TileType {
	None,
	Circle,
	Square,
	Diamond,
	Triangle,
	Paper,
	Scissor
};

static const char* TileType_to_String[] = {
	"none",
	"circle",
	"square",
	"diamond",
	"triangle",
	"paper",
	"scissor"
};

enum TileColor {
	Transparent,
	Red,
	Blue,
	Green,
	Yellow,
	Purple,
	Orange
};

static const char* TileColor_to_String[] = {
	"Transparent",
	"Red",
	"Blue",
	"Green",
	"Yellow",
	"Purple",
	"Orange"
};

inline std::unordered_map<TileColor, sf::Color> ColorTypeToColor = {
	{TileColor::Transparent, TransparentColor},
	{TileColor::Red, RedColor},
	{TileColor::Blue, BlueColor},
	{TileColor::Green, GreenColor},
	{TileColor::Yellow, YellowColor},
	{TileColor::Purple, PurpleColor},
	{TileColor::Orange, OrangeColor}
};

#endif