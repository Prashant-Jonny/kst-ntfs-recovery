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

	QBuffer buffer;
	

public:
	bool goback(qint64 bytes);
	bool skip(qint64 bytes);
	int read(char *buffer, unsigned int len);
	qint64 getSize();

	bool seek(qint64 offset);


	bool isReady(void);
	
	DiskReader(const QString filename);
	~DiskReader();
	
	
};
#endif
