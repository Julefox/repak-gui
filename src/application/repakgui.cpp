#include "pch.h"
#include "repakgui.h"

#include "../utils/utils.h"

RePakGui::RePakGui( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::RePakGuiClass() )
{
	ui->setupUi( this );

	for ( const QString& gameType : Utils::GameTypes.keys() )
		ui->gameTypeComboBox->addItem( gameType );

	this->LoadRPakListFromDir();

	connect( ui->addRPakButton, &QPushButton::clicked, this, &RePakGui::AddRPak );
}

RePakGui::~RePakGui()
{
	delete ui;
}

void RePakGui::closeEvent( QCloseEvent* event )
{
	this->SaveRPakData();
	event->accept();
}

void RePakGui::LoadRPakListFromDir()
{
	ui->rpakListWidget->clear();
	this->rpakList.clear();

	const QDir dir( Utils::CreateFolder( "paks" ), { "*.ini" } );

	const QFileInfoList list = dir.entryInfoList();
	for ( int i = 0; i < list.size(); i++ )
	{
		QFileInfo fileInfo = list.at( i );

		QSettings settings( fileInfo.absoluteFilePath(), QSettings::IniFormat );

		auto* rpakData = RPakData::FromVariant( settings.value( "rpak-data" ) );
		this->rpakList.append( rpakData );

		ui->rpakListWidget->addItem( rpakData->RPakName );
	}
}

void RePakGui::LoadRPakList( const QString& rpakToSelect )
{
	ui->rpakListWidget->blockSignals( true );
	ui->rpakListWidget->clear();

	this->currentRPakData = nullptr;

	if ( this->rpakList.empty() )
		return;

	this->currentRPakData = this->rpakList.at( 0 );

	for ( auto* rpakData : this->rpakList )
	{
		if ( rpakData->RPakName == rpakToSelect )
		{
			ui->rpakListWidget->addItem( rpakData->RPakName );
			this->currentRPakData = rpakData;
			ui->rpakListWidget->setCurrentRow( ui->rpakListWidget->count() - 1 );
			continue;
		}

		ui->rpakListWidget->addItem( rpakData->RPakName );
	}
	ui->rpakListWidget->blockSignals( false );
	emit ui->rpakListWidget->currentRowChanged( ui->rpakListWidget->currentRow() );
}

void RePakGui::AddRPak()
{
	const QString rpakName = ui->rpakNameLineEdit->text();

	if ( rpakName.isEmpty() )
		return;

	for ( const auto* rpakData : this->rpakList )
	{
		if ( rpakData->RPakName != rpakName )
			continue;

		QMessageBox::warning( this, "Error", "RPak with this name already exists!" );
		return;
	}

	auto* rpakData     = new RPakData();
	rpakData->RPakName = rpakName;
	this->rpakList.append( rpakData );

	this->LoadRPakList( rpakName );
}

void RePakGui::ClearRPakSettings() const {}

void RePakGui::SaveRPakData() const
{
	const QDir dir( Utils::CreateFolder( "paks" ), { "*.ini" } );

	const QFileInfoList list = dir.entryInfoList();
	for ( int i = 0; i < list.size(); i++ )
	{
		QFileInfo fileInfo = list.at( i );
		QFile file( fileInfo.absoluteFilePath() );
		file.remove();
	}

	for ( const auto* rpakData : this->rpakList )
	{
		QSettings settings( dir.absolutePath() + "/" + rpakData->RPakName + ".ini", QSettings::IniFormat );
		settings.setValue( "rpak-data", rpakData->ToVariant() );
	}
}
