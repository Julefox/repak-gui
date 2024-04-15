#include "pch.h"
#include "repakgui.h"

RePakGui::RePakGui( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::RePakGuiClass() )
{
	ui->setupUi( this );
}

RePakGui::~RePakGui()
{
	delete ui;
}
