#pragma once

namespace Utils
{
	inline QString CreateFolder( const QString& path, const bool addCurrentDir = true )
	{
		QString folder = path;
		if ( addCurrentDir )
			folder = QApplication::applicationDirPath() + "/" + folder;

		if ( const QDir dir; !dir.exists( folder ) )
			const bool _ = dir.mkpath( folder );

		return folder;
	}

	inline QMap < QString, int > GameTypes = { { "Titanfall 2", 7 }, { "Apex Legends", 8 } };

	inline QMap < QString, eAssetType > AssetTypes = {
		{ "Textures", eAssetType::TEXTURE }, { "Models", eAssetType::MODEL }, { "UI Images", eAssetType::UI_IMAGE }, { "Patches", eAssetType::PATCH }, { "Data Tables", eAssetType::DATATABLE },
		{ "Materials", eAssetType::MATERIAL }, { "Animations", eAssetType::ANIMATION }
	};
}
