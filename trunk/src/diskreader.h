/* 
 * $Header$ 
 * */

#ifndef DISKREADER_H
#define DISKREADER_H
//
#include "common.h"
#include <QFile>
#include <QBuffer>
//
class DiskReader : public QObject
{
	Q_OBJECT
protected:
	QFile file;
	bool ready;
	qint64 BlockSize;
	QBuffer buffer;
	

public:
	bool goback(qint64 bytes);
	bool skip(qint64 bytes);
	int read(char *buffer, unsigned int len);
	qint64 getSize();
	void ReadBlock();
	bool seek(qint64 offset);
	bool setBlockSize(qint64 value); // { BlockSize = value; }
	bool getBlockSize() { return BlockSize; }

	bool isReady(void);
	
	DiskReader(const QString filename);
	~DiskReader();
	
	
};
#endif
