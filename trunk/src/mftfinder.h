/*
 * $Header$
 */
#ifndef MFTFINDER_H
#define MFTFINDER_H
#include "common.h"
#include "diskreader.h"
#include "mftrecord.h"
// 

// 
// #define MFT_RECORDS 4096

class               mftFinder
{
protected:
  DiskReader        * disk;

  char                recordData[MFT_RECORD_LEN];
  quint64             mftMirrorPos;

public:
                      bool readNext ();

  mftrecord           record;
  bool                TryViaMirror ();
  bool                TryViaMirror (qint64 startPos);
  void                setDisk (DiskReader * value)
  {
    disk = value;
  } quint64           getmftMirrorPos ()
  {
    return mftMirrorPos;
  }
  void                setmftMirrorPos (qint64 value)
  {
    mftMirrorPos = value;
  }
  DiskReader         *getDisk ()
  {
    return disk;
  }
  mftFinder (DiskReader * disk);
  mftFinder ();

};
#endif
