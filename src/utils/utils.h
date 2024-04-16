#pragma once
#include "../public/textureslot.h"

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
		{ "Textures", eAssetType::TEXTURE },
		{ "Models", eAssetType::MODEL },
		{ "UI Images", eAssetType::UI_IMAGE },
		{ "Patches", eAssetType::PATCH },
		{ "Datatables", eAssetType::DATATABLE },
		{ "Materials", eAssetType::MATERIAL },
		{ "Animations", eAssetType::ANIMATION }
	};

	inline QList TextureSlots = {
		TextureSlot( "_albedoTexture", "Albedo", 0 ),
		TextureSlot( "_normalTexture", "Normal", 1 ),
		TextureSlot( "_glossTexture", "Gloss", 2 ),
		TextureSlot( "_specTexture", "Spec", 3 ),
		TextureSlot( "_emissiveTexture", "Emissive", 4 ),
		TextureSlot( "_aoTexture", "AO", 5 ),
		TextureSlot( "_cavityTexture", "Cavity", 6 ),
		TextureSlot( "_opacityMultiplyTexture", "Opacity Multiply", 7 ),
		TextureSlot( "_detailTexture", "Detail", 8 ),
		TextureSlot( "_detailNormalTexture", "Detail Normal", 9 ),
		TextureSlot( "_emissiveMultiplyTexture", "Emissive Multiply", 10 ),
		TextureSlot( "_uvDistortionTexture", "UV Distortion", 11 ),
		TextureSlot( "_uvDistortion2Texture", "UV Distortion 2", 12 ),
		TextureSlot( "_scatterThicknessTexture", "Scatter Thickness", 13 ),
		TextureSlot( "_transmittanceTintTexture", "Transmittance Tint", 14 ),
		TextureSlot( "_anisoSpecDirTexture", "Aniso Spec Dir", 15 ),
		TextureSlot( "_layerBlendTexture", "Layer Blend", 16 ),
		TextureSlot( "", "", 17 ), // Unused
		TextureSlot( "", "", 18 ), // Unused
		TextureSlot( "", "", 19 ), // Unused
		TextureSlot( "", "", 20 ), // Unused
		TextureSlot( "", "", 21 ), // Unused
		TextureSlot( "_albedo2Texture", "Albedo 2", 22 ),
		TextureSlot( "_normal2Texture", "Normal 2", 23 ),
		TextureSlot( "_gloss2Texture", "Gloss 2", 24 ),
		TextureSlot( "_spec2Texture", "Spec 2", 25 ),
		TextureSlot( "_emissive2Texture", "Emissive 2", 26 ),
		TextureSlot( "_emissiveMultiply2Texture", "Emissive Multiply 2", 27 ),
		TextureSlot( "_ao2Texture", "AO 2", 28 ),
		TextureSlot( "_cavity2Texture", "Cavity 2", 29 ),
		TextureSlot( "_opacityMultiply2Texture", "Opacity Multiply 2", 30 ),
		TextureSlot( "_detail2Texture", "Detail 2", 31 ),
		TextureSlot( "_detailNormal2Texture", "Detail Normal 2", 32 ),
		TextureSlot( "_scatterThickness2Texture", "Scatter Thickness 2", 33 ),
		TextureSlot( "_transmittanceTint2Texture", "Transmittance Tint 2", 34 )
	};

	inline QList < QString > GetLocalizedTextureSlotNames()
	{
		QList < QString > names;
		for ( const auto& slot : TextureSlots )
			names.push_back( slot.GetLocalizedName() );

		return names;
	}
}
