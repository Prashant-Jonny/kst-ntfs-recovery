/*
 * $Header$
 * На данный момент файл не несет в себе 
 * никакой полезной нагрузки, кроме тестов.
 */

#include "diskreader.h"
#include "mftfinder.h"
#include "ntfsbootrecord.h"
#include "clasterreader.h"

#include "common.h"

#define useGUI false

#define RECORDS_TO_READ 100000

int main (int argc, char **argv)
{

//  qint64              devsize = 0;
  mftFinder           mftf;
  NTFSBootRecord      ntfs_br;
  ClasterReader       cread;
  char               *diskData;
  quint64             diskDataLen;
  if (argc < 3)
    {
      /*
       * TODO: 
       */
      printf ("%s", "Usage: --not implemented--\n");
      return -1;

    }
  QFile               out (argv[2]);
  DiskReader          hdd (argv[1]);

  out.open (QIODevice::WriteOnly | QIODevice::Truncate);
  DBG << cread.init (&hdd);
  diskDataLen = cread.getBytesPerClaster () * RECORDS_TO_READ;
  diskData = (char *) new (char[diskDataLen]);
  printf ("diskData = 0x%x\n", &diskData);
  DBG << "diskDataLen" << diskDataLen;
  DBG << "diskData" << &diskData[0];
  DBG << cread.read (hdd.bs.bs.mft_location, RECORDS_TO_READ, diskData);
  out.write (diskData, diskDataLen);
  out.close ();

  delete              diskData;
  return -1;

}
