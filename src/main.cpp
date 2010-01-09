/*
 * $Header$
 * На данный момент файл не несет в себе 
 * никакой полезной нагрузки, кроме тестов.
 */


#include "diskreader.h"
#include "mftfinder.h"
#include "ntfsbootrecord.h"

#include "common.h"

#define useGUI false

int
main (int argc, char **argv)
{

  qint64 devsize = 0;
  mftFinder mftf;
  NTFSBootRecord ntfs_br;

  if (argc < 3)
    {
      /*
       * TODO: 
       */
      printf ("%s", "Usage: --not implemented--\n");
      return -1;

    }
  QFile out (argv[2]);
  DiskReader hdd (argv[1]);
  DBG << hdd.bs.isValid ();
  out.open (QIODevice::WriteOnly | QIODevice::Truncate);

  if (!hdd.isReady ())
    {
      printf ("%s", "hdd device not ready\n");

    }
  devsize = hdd.getSize ();
  DBG << "sizeof device is" << devsize;


  mftf.setDisk (&hdd);
  DBG << mftf.TryViaMirror ();

  out.write (mftf.record.getData (), MFT_RECORD_LEN);
  int i;
  for (i = 0; i < 20; i++)
    {
      if (mftf.readNext () == false)
	break;
      out.write (mftf.record.getData (), MFT_RECORD_LEN);
    }



}
