#ifndef MFTRECORD_H
#define MFTRECORD_H
#include "common.h"
// 

#define MFT_RECORD_LEN 1024
// 
class mftrecord
{
protected:
  char *data;

public:
  void update ();
  void dump ();
  void setData (char *value)
  {
    data = value;
  } char *getData ()
  {
    return data;
  }
  int isPossibleValid ();

  mftrecord ();

};
#endif
