#pragma once

#include "assetdata.h"

class RPakData
{
public:
	RPakData()  = default;
	~RPakData() = default;

	QString RPakName;
	int RPakVersion         = 8; // 7 = Titanfall 2, 8 = Apex Legends
	bool KeepDevOnly        = false;
	QString AssetDirectory  = ".\\assets\\";
	QString OutputDirectory = ".\\output\\";
	QString StarPakPath;

	// All AssetData
	QList < TextureData* > Textures     = {};
	QList < ModelData* > Models         = {};
	QList < UiImageData* > UiImages     = {};
	QList < PatchData* > Patches        = {};
	QList < DataTableData* > DataTables = {};
	QList < MaterialData* > Materials   = {};
	QList < AnimationData* > Animations = {};

	[[nodiscard]] QVariant ToVariant() const;
	static RPakData* FromVariant( const QVariant& variant );
};

Q_DECLARE_METATYPE( RPakData )
