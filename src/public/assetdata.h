#pragma once
#include "../utils/utils.h"

class AssetData
{
public:
	explicit AssetData( const eAssetType assetType = eAssetType::UNTYPED ) : assetType( assetType ) {}
	virtual ~AssetData() = default;

	[[nodiscard]] virtual QVariant ToVariant() const
	{
		QVariantMap map;
		map[ "path" ] = Path;
		return map;
	}

	[[nodiscard]] static AssetData* FromVariant( const QVariant& variant )
	{
		auto* data      = new AssetData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}

	[[nodiscard]] QString GetType() const { return Utils::GetAssetTypeString( this->assetType ); }

	[[nodiscard]] eAssetType GetAssetType() const { return this->assetType; }

	QString Path;

private:
	eAssetType assetType = eAssetType::UNTYPED;
};

Q_DECLARE_METATYPE( AssetData )

class ModelData final : public AssetData
{
public:
	ModelData() : AssetData( eAssetType::MODEL ) {}

	[[nodiscard]] static ModelData* FromVariant( const QVariant& variant )
	{
		auto* data      = new ModelData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( ModelData )

class UiImageData final : public AssetData
{
public:
	UiImageData() : AssetData( eAssetType::UI_IMAGE ) {}

	[[nodiscard]] static UiImageData* FromVariant( const QVariant& variant )
	{
		auto* data      = new UiImageData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( UiImageData )

class PatchData final : public AssetData
{
public:
	PatchData() : AssetData( eAssetType::PATCH ) {}

	[[nodiscard]] static PatchData* FromVariant( const QVariant& variant )
	{
		auto* data      = new PatchData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( PatchData )

class DataTableData final : public AssetData
{
public:
	DataTableData() : AssetData( eAssetType::DATATABLE ) {}

	[[nodiscard]] static DataTableData* FromVariant( const QVariant& variant )
	{
		auto* data      = new DataTableData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( DataTableData )

class MaterialData final : public AssetData
{
public:
	MaterialData() : AssetData( eAssetType::MATERIAL ) {}

	[[nodiscard]] static MaterialData* FromVariant( const QVariant& variant )
	{
		auto* data      = new MaterialData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( MaterialData )

class AnimationData final : public AssetData
{
public:
	AnimationData() : AssetData( eAssetType::ANIMATION ) {}

	[[nodiscard]] static AnimationData* FromVariant( const QVariant& variant )
	{
		auto* data      = new AnimationData();
		QVariantMap map = variant.toMap();

		data->Path = map[ "path" ].toString();

		return data;
	}
};

Q_DECLARE_METATYPE( AnimationData )
