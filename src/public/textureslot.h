#pragma once

class TextureSlot
{
public:
	TextureSlot() = default;
	explicit TextureSlot( const QString& name, const QString& localizedName, const int id ) : name( name ), localizedName( localizedName ), textureId( id ) {}
	~TextureSlot() = default;

	[[nodiscard]] const QString& GetName() const { return this->name; }

	[[nodiscard]] const QString& GetLocalizedName() const { return this->localizedName; }

	[[nodiscard]] int GetTextureId() const { return this->textureId; }

private:
	QString name;
	QString localizedName;
	int textureId;
};
