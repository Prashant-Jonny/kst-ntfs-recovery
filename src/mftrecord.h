#ifndef MFTRECORD_H
#define MFTRECORD_H
#include "common.h"
// 

#define MFT_RECORD_LEN 1024

/**
 * enum NTFS_RECORD_TYPES - cuted from ntfs-3g sources
 *
 * Magic identifiers present at the beginning of all ntfs record containing
 * records (like mft records for example).
 */
#ifndef const_cpu_to_le32
#define const_cpu_to_le32(x) (qint32(x))
#endif

// 
class               mftrecord
{
protected:
  char               *data;

public:
  void                update ();
  void                setData (char *value)
  {
    data = value;
  } char             *getData ()
  {
    return data;
  }
  int                 isPossibleValid ();

  mftrecord ();

};
#endif
