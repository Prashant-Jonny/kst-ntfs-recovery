/*
 * $Header$
 */ 
#include "clasterreader.h"
//
ClasterReader::ClasterReader ()
{
  // TODO
}

//

bool ClasterReader::init (DiskReader * disk)
{
  quint64 diskSizeTest;
  this->disk = disk;

  if (!this->disk->isReady () || disk->bs.isValid ())
    {
      return false;
    }

  bytes_per_sector = disk->bs.bs.bytes_per_sector;
  sectors_per_claster = disk->bs.bs.sectors_per_cluster;
  start_sector_offset = disk->bs.bs.hidden_sectors;
  start_bytes_offset = bytes_per_sector * start_sector_offset;
  total_count = disk->bs.bs.number_of_sectors / sectors_per_claster;
  bytes_per_claster = sectors_per_claster * bytes_per_sector;
  diskSizeTest = this->disk->getSize ();
  if (total_count * bytes_per_claster > diskSizeTest)
    {
      return false;
    }

  return true;
}

bool ClasterReader::seek (quint64 position)
{
//  quint64 absPos=start_bytes_offset;
  quint64 absPos = 0;
  if (position >= total_count)
    return false;
  absPos += position * bytes_per_claster;
  return this->disk->seek (absPos);
}

quint64 ClasterReader::getBytesPerClaster ()
{
  return this->bytes_per_claster;
}

bool ClasterReader::read (quint64 startClaster, quint32 count,
			  char *buffer)
{
  quint32 readed;
  this->seek (startClaster);
  /* TODO fix possible overflow */
  readed = this->disk->read (buffer, count * bytes_per_claster);
  return (readed == 0) ? true : false;
}
