/* 
 * $Header$
 */
#include <QApplication>
#include <QString>
#include <QIODevice>

#include "knr_dialogimpl.h"
#include "diskreader.h"

#include "common.h"

#define useGUI false

//
int main(int argc, char ** argv)
{
//	QApplication app( argc, argv, useGUI );

char mftRecord[1024];
qint64 devsize=0;
	if (argc < 3) {
		/* TODO: */
		printf("%s", "Usage: --not implemented--\n");
		return -1;
		
	}
	DiskReader hdd(argv[1]);
	//app.arguments(0);
	//hdd.setFileName("/dev/sdb1");
	if (!hdd.isReady() ) {
		printf("%s", "hdd device not ready\n");
	
	}
devsize = hdd.getSize();
	DBG << "sizeof device is" << devsize; 


	
	
	if ( hdd.read(mftRecord, sizeof(mftRecord)) ) {
		DBG << "can't read data";		
	} else {
		DBG << "block readed";
	}
	
	/*
	if (useGUI) {
			DialogImpl win;
			win.show(); 
			app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
			return app.exec();
	} else {
		
		
	} */

}
