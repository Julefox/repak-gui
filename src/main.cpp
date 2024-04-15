#include "pch.h"
#include "application/repakgui.h"
#include <QtWidgets/QApplication>
#include <Windows.h>

int main( int argc, char* argv[ ] )
{
	QApplication a( argc, argv );

#if defined( QT_DEBUG ) && defined( _WIN64 )
	AllocConsole();
	FILE* pConOut;
	int _ = freopen_s( &pConOut, "CONOUT$", "w", stdout );
	FILE* pConErr;
	_ = freopen_s( &pConErr, "CONOUT$", "w", stderr );
#endif

	qRegisterMetaType < RPakData >( "RPakData" );
	qRegisterMetaType < AssetData >( "AssetData" );
	qRegisterMetaType < TextureData >( "TextureData" );
	qRegisterMetaType < ModelData >( "ModelData" );
	qRegisterMetaType < UiImageData >( "UiImageData" );
	qRegisterMetaType < PatchData >( "PatchData" );
	qRegisterMetaType < DataTableData >( "DataTableData" );
	qRegisterMetaType < MaterialData >( "MaterialData" );
	qRegisterMetaType < AnimationData >( "AnimationData" );

	RePakGui w;
	w.show();

	return QApplication::exec();
}
