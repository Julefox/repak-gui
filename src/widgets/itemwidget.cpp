#include "pch.h"
#include "itemwidget.h"

ItemWidget::ItemWidget( QWidget* parent ) : QWidget( parent ), ui( new Ui::ItemWidgetClass() ) { ui->setupUi( this ); }

ItemWidget::ItemWidget( const AssetData* assetData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !assetData )
		return;

	this->ui->itemLabel->setText( assetData->Path );
}

ItemWidget::ItemWidget( ModelData* modelData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( modelData ), parent )
{
	if ( !modelData )
		return;

	this->ui->itemTypeLabel->setText( "Model" );
}

ItemWidget::ItemWidget( UiImageData* uiImageData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( uiImageData ), parent )
{
	if ( !uiImageData )
		return;

	this->ui->itemTypeLabel->setText( "UI Image" );
}

ItemWidget::ItemWidget( PatchData* patchData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( patchData ), parent )
{
	if ( !patchData )
		return;

	this->ui->itemTypeLabel->setText( "Patch" );
}

ItemWidget::ItemWidget( DataTableData* dataTableData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( dataTableData ), parent )
{
	if ( !dataTableData )
		return;

	this->ui->itemTypeLabel->setText( "Datatable" );
}

ItemWidget::ItemWidget( MaterialData* materialData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( materialData ), parent )
{
	if ( !materialData )
		return;

	this->ui->itemTypeLabel->setText( "Material" );
}

ItemWidget::ItemWidget( AnimationData* animationData, QWidget* parent ) : ItemWidget( AssetData::FromInheritance( animationData ), parent )
{
	if ( !animationData )
		return;

	this->ui->itemTypeLabel->setText( "Animation" );
}

ItemWidget::~ItemWidget() { delete ui; }
