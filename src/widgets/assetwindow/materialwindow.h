#pragma once

#include <QMainWindow>
#include "ui_materialwindow.h"
#include "../../public/assetdata.h"

QT_BEGIN_NAMESPACE namespace Ui
{
	class MaterialWindowClass;
};

QT_END_NAMESPACE class MaterialWindow final : public QMainWindow
{
	Q_OBJECT public:
	explicit MaterialWindow( QWidget* parent = nullptr );
	explicit MaterialWindow( MaterialData* materialData, QWidget* parent = nullptr );
	~MaterialWindow() override;

protected:
	void closeEvent( QCloseEvent* event ) override;

signals:
	void OnWindowClose();

private:
	Ui::MaterialWindowClass* ui;

	MaterialData* materialData = nullptr;

	void RefreshWindowName();

	void ResetMaterialData();
	void SaveMaterialData();
};
