#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_repakgui.h"

QT_BEGIN_NAMESPACE namespace Ui
{
	class RePakGuiClass;
};

QT_END_NAMESPACE class RePakGui final : public QMainWindow
{
	Q_OBJECT public:
	explicit RePakGui( QWidget* parent = nullptr );
	~RePakGui() override;

private:
	Ui::RePakGuiClass* ui;
};
