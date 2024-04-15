#pragma once

#include <QWidget>
#include "ui_itemwidget.h"

QT_BEGIN_NAMESPACE namespace Ui
{
	class ItemWidgetClass;
};

QT_END_NAMESPACE class ItemWidget final : public QWidget
{
	Q_OBJECT public:
	explicit ItemWidget( QWidget* parent = nullptr );
	~ItemWidget() override;

private:
	Ui::ItemWidgetClass* ui;
};
