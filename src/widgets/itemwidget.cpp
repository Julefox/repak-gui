#include "pch.h"
#include "itemwidget.h"

ItemWidget::ItemWidget( QWidget* parent ) : QWidget( parent ), ui( new Ui::ItemWidgetClass() )
{
	ui->setupUi( this );
}

ItemWidget::~ItemWidget()
{
	delete ui;
}
