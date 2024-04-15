#include "pch.h"
#include "application/repakgui.h"
#include <QtWidgets/QApplication>

int main( int argc, char* argv[ ] )
{
	QApplication a( argc, argv );
	RePakGui w;
	w.show();
	return QApplication::exec();
}
