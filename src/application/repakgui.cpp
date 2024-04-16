#include "pch.h"
#include "repakgui.h"

#include "../utils/utils.h"
#include "../widgets/itemwidget.h"
#include "../widgets/assetwindow/materialwindow.h"

RePakGui::RePakGui( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::RePakGuiClass() )
{
	ui->setupUi( this );
	ui->assetLayout->setAlignment( Qt::AlignTop );

	ui->gameTypeComboBox->clear();
	for ( const QString& gameType : Utils::GameTypes.keys() )
		ui->gameTypeComboBox->addItem( gameType );

	ui->gameTypeComboBox->setCurrentIndex( 0 );

	ui->assetComboBox->clear();
	for ( const QString& assetType : Utils::AssetTypes.keys() )
		ui->assetComboBox->addItem( assetType );

	ui->assetComboBox->setCurrentIndex( 0 );

	this->LoadRPakListFromDir();

	connect( ui->addRPakButton, &QPushButton::clicked, this, &RePakGui::AddRPak );
	connect( ui->removeRPakButton, &QPushButton::clicked, this, &RePakGui::RemoveCurrentRPak );

	connect( ui->addAssetButton, &QPushButton::clicked, this, &RePakGui::AddAsset );

	connect( ui->rpakListWidget, &QListWidget::currentItemChanged, this, &RePakGui::OnRPakSelected );

	connect( ui->resetRPakButton, &QPushButton::clicked, this, &RePakGui::ResetCurrentRPak );
	connect( ui->saveRPakButton, &QPushButton::clicked, this, &RePakGui::SaveCurrentRPak );
}

RePakGui::~RePakGui() { delete ui; }

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
		this->ClearRPakData();
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
		this->ClearRPakData();
		return;
	}

	this->ResetCurrentRPak();
}

void RePakGui::ResetCurrentRPak()
{
	if ( !this->currentRPakData )
	{
		this->ClearRPakData();
		return;
	}

	QLayoutItem* item;
	while ( ( item = ui->assetLayout->takeAt( 0 ) ) != nullptr )
	{
		if ( item->widget() )
			delete item->widget();
		delete item;
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

	for ( ModelData* modelData : this->currentRPakData->Models )
	{
		auto* modelWidget = new ItemWidget( modelData );
		connect( modelWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, modelData ]
		{
			auto& materials = this->currentRPakData->Models;
			if ( const auto it = std::find( materials.begin(), materials.end(), modelData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		// TODO: Connect ModelWindow
		ui->assetLayout->addWidget( modelWidget );
	}

	for ( UiImageData* uiImageData : this->currentRPakData->UiImages )
	{
		auto* uiImageWidget = new ItemWidget( uiImageData );
		connect( uiImageWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, uiImageData ]
		{
			auto& materials = this->currentRPakData->UiImages;
			if ( const auto it = std::find( materials.begin(), materials.end(), uiImageData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		// TODO: Connect UiImageWindow
		ui->assetLayout->addWidget( uiImageWidget );
	}

	for ( PatchData* patchData : this->currentRPakData->Patches )
	{
		auto* patchWidget = new ItemWidget( patchData );
		connect( patchWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, patchData ]
		{
			auto& materials = this->currentRPakData->Patches;
			if ( const auto it = std::find( materials.begin(), materials.end(), patchData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		// TODO: Connect PatchWindow
		ui->assetLayout->addWidget( patchWidget );
	}

	for ( DataTableData* dataTableData : this->currentRPakData->DataTables )
	{
		auto* dataTableWidget = new ItemWidget( dataTableData );
		connect( dataTableWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, dataTableData ]
		{
			auto& materials = this->currentRPakData->DataTables;
			if ( const auto it = std::find( materials.begin(), materials.end(), dataTableData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		// TODO: Connect DataTableWindow
		ui->assetLayout->addWidget( dataTableWidget );
	}

	for ( MaterialData* materialData : this->currentRPakData->Materials )
	{
		auto* materialWidget = new ItemWidget( materialData );
		connect( materialWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, materialData ]
		{
			auto& materials = this->currentRPakData->Materials;
			if ( const auto it = std::find( materials.begin(), materials.end(), materialData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		connect( materialWidget->GetEditButton(), &QPushButton::clicked, this, [ this, materialData ]
		{
			auto* materialWindow = new MaterialWindow( materialData, this );
			connect( materialWindow, &MaterialWindow::OnWindowClose, this, &RePakGui::ResetCurrentRPak );
			materialWindow->show();
		} );
		ui->assetLayout->addWidget( materialWidget );
	}

	for ( AnimationData* animationData : this->currentRPakData->Animations )
	{
		auto* animationWidget = new ItemWidget( animationData );
		connect( animationWidget->GetDeleteButton(), &QPushButton::clicked, this, [ this, animationData ]
		{
			auto& materials = this->currentRPakData->Animations;
			if ( const auto it = std::find( materials.begin(), materials.end(), animationData ); it != materials.end() )
			{
				materials.erase( it );  // Delete From List
				this->ResetCurrentRPak(); // Refresh Interface
			}
		} );
		// TODO: Connect AnimationWindow
		ui->assetLayout->addWidget( animationWidget );
	}
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
	emit ui->rpakListWidget->currentItemChanged( ui->rpakListWidget->currentItem(), nullptr );
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

void RePakGui::AddAsset()
{
	if ( !this->currentRPakData )
	{
		this->ClearRPakData();
		return;
	}

	const QString assetType        = ui->assetComboBox->currentText();
	const eAssetType enumAssetType = Utils::AssetTypes[ assetType ];

	if ( enumAssetType == eAssetType::MODEL )
		this->currentRPakData->Models.append( new ModelData() );

	if ( enumAssetType == eAssetType::UI_IMAGE )
		this->currentRPakData->UiImages.append( new UiImageData() );

	if ( enumAssetType == eAssetType::PATCH )
		this->currentRPakData->Patches.append( new PatchData() );

	if ( enumAssetType == eAssetType::DATATABLE )
		this->currentRPakData->DataTables.append( new DataTableData() );

	if ( enumAssetType == eAssetType::MATERIAL )
		this->currentRPakData->Materials.append( new MaterialData() );

	if ( enumAssetType == eAssetType::ANIMATION )
		this->currentRPakData->Animations.append( new AnimationData() );

	this->ResetCurrentRPak();
}

void RePakGui::ClearRPakData() const {}

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
