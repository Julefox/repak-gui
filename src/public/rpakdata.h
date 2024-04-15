#pragma once

#include "assetdata.h"

class RPakData
{
public:
	RPakData()  = default;
	~RPakData() = default;

	QString RPakName        = "unnamed";
	int RPakVersion         = 8; // 7 = Titanfall 2, 8 = Apex Legends
	int MapVersion          = 1;
	bool KeepDevOnly        = false;
	QString AssetDirectory  = ".\\assets\\";
	QString OutputDirectory = ".\\output\\";
	QString StarPakPath;

	// All AssetData
	QList < TextureData > Textures     = {};
	QList < ModelData > Models         = {};
	QList < UiImageData > UiImages     = {};
	QList < PatchData > Patches        = {};
	QList < DataTableData > DataTables = {};
	QList < MaterialData > Materials   = {};
	QList < AnimationData > Animations = {};
};
