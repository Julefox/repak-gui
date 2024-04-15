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
	connect( ui->removeRPakButton, &QPushButton::clicked, this, &RePakGui::RemoveCurrentRPak );

	connect( ui->rpakListWidget, &QListWidget::currentItemChanged, this, &RePakGui::OnRPakSelected );

	connect( ui->resetRPakButton, &QPushButton::clicked, this, &RePakGui::ResetCurrentRPak );
	connect( ui->saveRPakButton, &QPushButton::clicked, this, &RePakGui::SaveCurrentRPak );
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

void RePakGui::OnRPakSelected( const QListWidgetItem* item )
{
	if ( !item )
	{
		this->ClearRPakSettings();
		return;
	}

	const QString rpakName = item->text();

	for ( auto* rpakData : this->rpakList )
	{
		if ( rpakData->RPakName != rpakName )
			continue;

		this->currentRPakData = rpakData;
		break;
	}

	if ( !this->currentRPakData )
	{
		this->ClearRPakSettings();
		return;
	}

	this->ResetCurrentRPak();
}

void RePakGui::ResetCurrentRPak() const
{
	if ( !this->currentRPakData )
	{
		this->ClearRPakSettings();
		return;
	}

	for ( const QString& gameType : Utils::GameTypes.keys() )
	{
		if ( Utils::GameTypes[ gameType ] == this->currentRPakData->RPakVersion )
		{
			for ( int i = 0; i < ui->gameTypeComboBox->count(); i++ )
			{
				if ( ui->gameTypeComboBox->itemText( i ) != gameType )
					continue;

				ui->gameTypeComboBox->setCurrentIndex( i );
				break;
			}
			break;
		}
	}

	ui->keepDevOnlyCheckBox->setChecked( this->currentRPakData->KeepDevOnly );
}

void RePakGui::SaveCurrentRPak() const
{
	if ( !this->currentRPakData )
		return;

	this->currentRPakData->RPakVersion = Utils::GameTypes[ ui->gameTypeComboBox->currentText() ];
	this->currentRPakData->KeepDevOnly = ui->keepDevOnlyCheckBox->isChecked();
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

	ui->rpakNameLineEdit->clear();

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

void RePakGui::RemoveCurrentRPak()
{
	if ( !this->currentRPakData )
		return;

	if ( QMessageBox::question( this, "Remove RPak", "Are you sure you want to remove this RPak?" ) != QMessageBox::Yes )
		return;

	this->rpakList.removeOne( this->currentRPakData );
	delete this->currentRPakData;
	this->LoadRPakList();
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
