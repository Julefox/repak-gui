#pragma once

class AssetData
{
public:
	explicit AssetData( const QString& type = {} ) : Type( type ) {}
	virtual ~AssetData() = default;

	QString Type;
	QString Path;
};

class TextureData final : public AssetData
{
public:
	TextureData() : AssetData( "txtr" ) {}
};

class ModelData final : public AssetData
{
public:
	ModelData() : AssetData( "rmdl" ) {}
};

class UiImageData final : public AssetData
{
public:
	UiImageData() : AssetData( "uimg" ) {}
};

class PatchData final : public AssetData
{
public:
	PatchData() : AssetData( "Ptch" ) {}
};

class DataTableData final : public AssetData
{
public:
	DataTableData() : AssetData( "dtbl" ) {}
};

class MaterialData final : public AssetData
{
public:
	MaterialData() : AssetData( "matl" ) {}
};

class AnimationData final : public AssetData
{
public:
	AnimationData() : AssetData( "rseq" ) {}
};
