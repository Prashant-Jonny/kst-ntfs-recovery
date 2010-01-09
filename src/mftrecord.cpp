#include "mftrecord.h"
// 

int
mftrecord::isPossibleValid ()
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

void
mftrecord::dump ()
{
  int i = 1024, j = 0, k = 0;

  for (i = 0; i < 1024; i++)
    {
      for (k = 0; k < 2; k++)
	{
	  for (j = 0; j < 8; j++)
	    {
	      // printf("%x ", this->data[i++] & 0xFF) ; 
	      printf ("%c", this->data[i++]);
	    }
	  // printf("\t");
	}
      // printf("\n");
    }

}


void
mftrecord::update ()
{
  // TODO
}
