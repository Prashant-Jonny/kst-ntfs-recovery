/*
 * $Header$
 */
 
#include "mftfinder.h"

mftFinder::mftFinder(){
}
//
mftFinder::mftFinder( DiskReader *disk ) 
{
	this->setDisk(disk);
}

//

bool mftFinder::TryViaMirror() {
	qint64 dlen = this->disk->getSize();
	dlen = dlen >> 1;
	return this->TryViaMirror(dlen);	
	
}

bool mftFinder::TryViaMirror(qint64 startPos)
{
	int offsetFix;
/* get center of disk */		

	
	this->disk->seek(startPos);
	if (this->disk->read((char *)this->recordData, sizeof(this->recordData) )) {
		DBG "disk reading error";
		return false;		

	}
	
	this->record.setData(this->recordData);
	offsetFix = this->record.isPossibleValid();
	if ( offsetFix >0 ) {
			this->mftMirrorPos = startPos+offsetFix;
			
			this->disk->seek(this->mftMirrorPos);
			if (this->disk->read((char *)this->recordData, sizeof(this->recordData) )) {
				DBG "disk reading error";
				return false;		
			}
			this->record.setData(this->recordData);
			return true;
	}
		

	return false;	
}


bool mftFinder::readNext()
{
	if (this->disk->read((char *)this->recordData, sizeof(this->recordData) )) {
		DBG "disk reading error";
		return false;		
	}
	this->record.update();
	return true;
}

