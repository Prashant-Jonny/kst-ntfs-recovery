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
class DiskReader:public QObject
{
Q_OBJECT protected:
    QFile file;
  bool ready;

  QBuffer buffer;

protected:
    qint64 calcSize ();

public:
    qint64 getSize ()
  {
    if ((this->size == 0) && this->isReady ())
      {
	this->size = this->calcSize ();
      }
    return size;
  }
  qint64 size;
  bool goback (qint64 bytes);
  bool skip (qint64 bytes);
  int read (char *buffer, unsigned int len);


  bool seek (qint64 offset);


  bool isReady (void);

  DiskReader (const QString filename);
  ~DiskReader ();


};
#endif
