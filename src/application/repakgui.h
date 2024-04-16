#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_repakgui.h"
#include "../public/rpakdata.h"

QT_BEGIN_NAMESPACE namespace Ui
{
	class RePakGuiClass;
};

QT_END_NAMESPACE class RePakGui final : public QMainWindow
{
	Q_OBJECT public:
	explicit RePakGui( QWidget* parent = nullptr );
	~RePakGui() override;

protected:
	void closeEvent( QCloseEvent* event ) override;

private:
	Ui::RePakGuiClass* ui;

	RPakData* currentRPakData = nullptr;
	QList < RPakData* > rpakList;

	void LoadRPakList( const QString& rpakToSelect = {} );
	void LoadRPakListFromDir();

	void OnRPakSelected( const QListWidgetItem* item );
	void ResetCurrentRPak();
	void SaveCurrentRPak() const;

	void AddRPak();
	void RemoveCurrentRPak();

	void AddAsset();

	void ClearRPakData() const;
	void SaveRPakData() const;
};
