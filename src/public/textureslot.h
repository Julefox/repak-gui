#pragma once

class TextureSlot
{
public:
	explicit TextureSlot( const QString& name, const QString& localizedName, const int id ) : name( name ), localizedName( localizedName ), textureId( id ) {}
	~TextureSlot();

	[[nodiscard]] const QString& GetName() const { return this->name; }

	[[nodiscard]] const QString& GetLocalizedName() const { return this->localizedName; }

	[[nodiscard]] int GetTextureId() const { return this->textureId; }

private:
	QString name;
	QString localizedName;
	int textureId;
};
