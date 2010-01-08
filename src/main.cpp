/* 
 * $Header$
 */

#include "knr_dialogimpl.h"
#include "diskreader.h"
#include "mftfinder.h"

#include "common.h"

#define useGUI false

//
int main(int argc, char ** argv)
{
//	QApplication app( argc, argv, useGUI );


qint64 devsize=0;
mftFinder mftf;


	if (argc < 3) {
		/* TODO: */
		printf("%s", "Usage: --not implemented--\n");
		return -1;
		
	}
	QFile out(argv[2]);	
	DiskReader hdd(argv[1]);
	out.open(QIODevice::WriteOnly|QIODevice::Truncate);
	//app.arguments(0);
	//hdd.setFileName("/dev/sdb1");
	if (!hdd.isReady() ) {
		printf("%s", "hdd device not ready\n");
	
	}
devsize = hdd.getSize();
	DBG << "sizeof device is" << devsize; 


	mftf.setDisk(&hdd);
	DBG << mftf.TryViaMirror();
	// if ( mftf.record.isPossibleValid() == 0) {
		out.write(mftf.record.getData(), MFT_RECORD_LEN);
int i;
for (i=0; i<20;i++){
	if ( mftf.readNext() == false) break;
   out.write(mftf.record.getData(), MFT_RECORD_LEN);
}
	
	//}
	
	/* 
	if ( hdd.read(mftRecord, sizeof(mftRecord)) ) {
		DBG << "can't read data";		
	} else {
		DBG << "block readed";
	}
	*/
	/*
	if (useGUI) {
			DialogImpl win;
			win.show(); 
			app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
			return app.exec();
	} else {
		
		
	} */

}
