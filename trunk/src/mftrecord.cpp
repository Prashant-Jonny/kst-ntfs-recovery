#include "mftrecord.h"
// 

int mftrecord::isPossibleValid ()
{
  static char parten[] = "FILE";
  int pos = 0;
  pos = testFor (parten, 4, this->data, MFT_RECORD_LEN);
  DBG << "pos = " << pos;
  return (pos >= 0) ? pos : -1;

}

mftrecord::mftrecord ()
{
  // TODO
}

// 

void mftrecord::update ()
{
  // TODO
}
