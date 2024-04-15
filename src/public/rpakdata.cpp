#include "pch.h"
#include "rpakdata.h"

QVariant RPakData::ToVariant() const
{
	QVariantMap map;
	map[ "rpak-name" ]        = this->RPakName;
	map[ "rpak-version" ]     = this->RPakVersion;
	map[ "keep-dev-only" ]    = this->KeepDevOnly;
	map[ "asset-directory" ]  = this->AssetDirectory;
	map[ "output-directory" ] = this->OutputDirectory;
	map[ "starpak-path" ]     = this->StarPakPath;

	QVariantList list;

	for ( const TextureData* entry : this->Textures )
		list.append( entry->ToVariant() );

	map[ "textures" ] = list;
	list.clear();

	for ( const ModelData* entry : this->Models )
		list.append( entry->ToVariant() );

	map[ "models" ] = list;
	list.clear();

	for ( const UiImageData* entry : this->UiImages )
		list.append( entry->ToVariant() );

	map[ "ui-images" ] = list;
	list.clear();

	for ( const PatchData* entry : this->Patches )
		list.append( entry->ToVariant() );

	map[ "patches" ] = list;
	list.clear();

	for ( const DataTableData* entry : this->DataTables )
		list.append( entry->ToVariant() );

	map[ "datatables" ] = list;
	list.clear();

	for ( const MaterialData* entry : this->Materials )
		list.append( entry->ToVariant() );

	map[ "materials" ] = list;
	list.clear();

	for ( const AnimationData* entry : this->Animations )
		list.append( entry->ToVariant() );

	map[ "animations" ] = list;

	return map;
}

RPakData* RPakData::FromVariant( const QVariant& variant )
{
	auto* data      = new RPakData();
	QVariantMap map = variant.toMap();

	data->RPakName        = map[ "rpak-name" ].toString();
	data->RPakVersion     = map[ "rpak-version" ].toInt();
	data->KeepDevOnly     = map[ "keep-dev-only" ].toBool();
	data->AssetDirectory  = map[ "asset-directory" ].toString();
	data->OutputDirectory = map[ "output-directory" ].toString();
	data->StarPakPath     = map[ "starpak-path" ].toString();

	QVariantList list = map[ "textures" ].toList();

	for ( const QVariant& entry : list )
		data->Textures.append( TextureData::FromVariant( entry ) );

	list = map[ "models" ].toList();

	for ( const QVariant& entry : list )
		data->Models.append( ModelData::FromVariant( entry ) );

	list = map[ "ui-images" ].toList();

	for ( const QVariant& entry : list )
		data->UiImages.append( UiImageData::FromVariant( entry ) );

	list = map[ "patches" ].toList();

	for ( const QVariant& entry : list )
		data->Patches.append( PatchData::FromVariant( entry ) );

	list = map[ "datatables" ].toList();

	for ( const QVariant& entry : list )
		data->DataTables.append( DataTableData::FromVariant( entry ) );

	list = map[ "materials" ].toList();

	for ( const QVariant& entry : list )
		data->Materials.append( MaterialData::FromVariant( entry ) );

	list = map[ "animations" ].toList();

	for ( const QVariant& entry : list )
		data->Animations.append( AnimationData::FromVariant( entry ) );

	return data;
}
