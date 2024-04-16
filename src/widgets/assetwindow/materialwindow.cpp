#include "pch.h"
#include "materialwindow.h"

MaterialWindow::MaterialWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MaterialWindowClass() )
{
	ui->setupUi( this );

	this->RefreshWindowName();
}

MaterialWindow::MaterialWindow( MaterialData* materialData, QWidget* parent ) : MaterialWindow( parent )
{
	if ( !materialData )
		return;

	this->materialData = materialData;

	connect( ui->resetButton, &QPushButton::clicked, this, &MaterialWindow::ResetMaterialData );
	connect( ui->saveButton, &QPushButton::clicked, this, &MaterialWindow::SaveMaterialData );

	this->ResetMaterialData();
}

MaterialWindow::~MaterialWindow() { delete ui; }

void MaterialWindow::closeEvent( QCloseEvent* event )
{
	emit this->OnWindowClose();
	QMainWindow::closeEvent( event );
}

void MaterialWindow::RefreshWindowName()
{
	if ( !this->materialData )
		return;

	this->setWindowTitle( QString( "Material Edition | %1" ).arg( this->materialData->Path ) );
}

void MaterialWindow::ResetMaterialData()
{
	if ( !this->materialData )
		return;

	ui->pathLineEdit->setText( this->materialData->Path );

	this->RefreshWindowName();
}

void MaterialWindow::SaveMaterialData()
{
	if ( !this->materialData )
		return;

	this->materialData->Path = ui->pathLineEdit->text();

	this->RefreshWindowName();
}
