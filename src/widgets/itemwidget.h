#pragma once

#include <QWidget>
#include "ui_itemwidget.h"
#include "../public/assetdata.h"

QT_BEGIN_NAMESPACE namespace Ui
{
	class ItemWidgetClass;
};

QT_END_NAMESPACE class ItemWidget final : public QWidget
{
	Q_OBJECT public:
	explicit ItemWidget( QWidget* parent = nullptr );
	explicit ItemWidget( const AssetData* assetData, QWidget* parent = nullptr );

	explicit ItemWidget( ModelData* modelData, QWidget* parent = nullptr );
	explicit ItemWidget( UiImageData* uiImageData, QWidget* parent = nullptr );
	explicit ItemWidget( PatchData* patchData, QWidget* parent = nullptr );
	explicit ItemWidget( DataTableData* dataTableData, QWidget* parent = nullptr );
	explicit ItemWidget( MaterialData* materialData, QWidget* parent = nullptr );
	explicit ItemWidget( AnimationData* animationData, QWidget* parent = nullptr );

	~ItemWidget() override;

	[[nodiscard]] QPushButton* GetEditButton() const { return ui->editButton; }
	[[nodiscard]] QPushButton* GetDeleteButton() const { return ui->deleteButton; }

private:
	Ui::ItemWidgetClass* ui;
};
