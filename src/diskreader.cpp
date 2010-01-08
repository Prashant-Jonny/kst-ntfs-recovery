/*
 * $Header$ 
 * */

#include "diskreader.h"
// 
DiskReader::DiskReader (const QString filename)
{

  this->ready = false;
  this->size = 0;
  this->file.setFileName (filename);
  if (!this->file.exists ())
    {
      DBG << __FUNCTION__ << tr ("file not exists") << filename;
      return;
    }
  else
    {
      DBG << tr ("opening ") << filename;
    }

  if (!this->file.open (QIODevice::ReadOnly))
    {
      DBG << __FUNCTION__ << tr ("can't open file");
      return;
    }
  this->ready = true;
  this->getSize ();
  DBG << tr ("open ok");
}

DiskReader::~DiskReader ()
{


}

bool DiskReader::isReady ()
{
  return this->ready;
};

// 


bool DiskReader::seek (qint64 offset)
{
  bool
    isOk = false;


  isOk = this->file.seek (offset);
  DBG << __FUNCTION__ << isOk;
  return isOk;

}




qint64 DiskReader::calcSize ()
{
  quint64
    position = 0, step;

  if (!this->isReady ())
    {
      DBG << "device not ready";
      return 0;
    }

  position = this->file.size ();
  if (position != 0)
    return position;

  /*
   * If position unknown - try to calculate it. walk to end of file via
   * seek function 
   */

  int
    bits = 48;

  while (bits-- > 0)
    {
      step = (quint64) 1 << bits;
      while (this->file.seek (position + step))
	{
	  position += step;
	}
      /*
       * if (position !=0) { DBG << step << position; } 
       */
    }


  this->file.seek (0);
  return position;

}


int
DiskReader::read (char *buffer, unsigned int len)
{
  unsigned int actualRead = 0;
  if (!this->isReady ())
    return -1;
  actualRead = this->file.read (buffer, len);
  if (actualRead != len)
    return 1;
  return 0;

}


bool DiskReader::skip (qint64 bytes)
{
  qint64
    target = bytes;
  target += this->file.pos ();

  return (target == this->file.seek (target)) ? true : false;

}


bool DiskReader::goback (qint64 bytes)
{
  qint64
    target;
  target = this->file.pos ();
  if (target < bytes)
    return false;
  target -= bytes;

  return (target == this->file.seek (target)) ? true : false;
}
