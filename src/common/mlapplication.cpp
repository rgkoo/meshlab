#include "mlapplication.h"
#include "mlexception.h"

#include <QTextCodec>
MeshLabApplication::MeshLabApplication( int &argc, char *argv[] )
:QApplication(argc,argv)
{
	/*
	QTextCodec *codec = QTextCodec::codecForName("GBK");//…Ë÷√÷–Œƒ
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	*/
}

MeshLabApplication::~MeshLabApplication()
{

}

bool MeshLabApplication::notify( QObject * rec, QEvent * ev )
{
	try
	{
		return QApplication::notify(rec,ev);
	}
	catch (MeshLabException& e)
	{    
		qCritical("%s",e.what());
	}
  return false;
}
