/*
 * $Header$
 */
#ifndef CLASTERREADER_H
#define CLASTERREADER_H
#include "common.h"
#include "diskreader.h"
#include "ntfsbootrecord.h"
//

//
class               ClasterReader
{
  quint16             bytes_per_sector;
  quint16             sectors_per_claster;
  quint64             start_sector_offset;	/* start offset in sectors */
  quint64             start_bytes_offset;	/* start offset in bytes */
  quint64             total_count;
  quint64             bytes_per_claster;

  DiskReader         *disk;

public:
     
     
     
     
     
            bool read (quint64 startClaster, quint32 count, char *buffer);
  quint64             getBytesPerClaster ();
  bool                seek (quint64 position);

  bool                init (DiskReader * disk);
                      ClasterReader ();

};
#endif
