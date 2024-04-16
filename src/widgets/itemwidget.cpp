#include "pch.h"
#include "itemwidget.h"

ItemWidget::ItemWidget( QWidget* parent ) : QWidget( parent ), ui( new Ui::ItemWidgetClass() ) { ui->setupUi( this ); }

ItemWidget::ItemWidget( ModelData* modelData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !modelData )
		return;

	this->ui->itemLabel->setText( QString( "Model - %1" ).arg( modelData->Path ) );
	this->assetData = modelData;
}

ItemWidget::ItemWidget( UiImageData* uiImageData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !uiImageData )
		return;

	this->ui->itemLabel->setText( QString( "UI Image - %1" ).arg( uiImageData->Path ) );
	this->assetData = uiImageData;
}

ItemWidget::ItemWidget( PatchData* patchData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !patchData )
		return;

	this->ui->itemLabel->setText( QString( "Patch - %1" ).arg( patchData->Path ) );
	this->assetData = patchData;
}

ItemWidget::ItemWidget( DataTableData* dataTableData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !dataTableData )
		return;

	this->ui->itemLabel->setText( QString( "Datatable - %1" ).arg( dataTableData->Path ) );
	this->assetData = dataTableData;
}

ItemWidget::ItemWidget( MaterialData* materialData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !materialData )
		return;

	this->ui->itemLabel->setText( QString( "Material - %1" ).arg( materialData->Path ) );
	this->assetData = materialData;
}

ItemWidget::ItemWidget( AnimationData* animationData, QWidget* parent ) : ItemWidget( parent )
{
	if ( !animationData )
		return;

	this->ui->itemLabel->setText( QString( "Animation - %1" ).arg( animationData->Path ) );
	this->assetData = animationData;
}

ItemWidget::~ItemWidget() { delete ui; }
