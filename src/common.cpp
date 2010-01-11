/*
 * $Header$
 */
#include "common.h"
int testFor (char *data, int data_len, char *buffer, int buffer_len)
{
  int                 pos = 0;
  int                 data_pos = 0;
  // printf("data = 0x%x, data_len=%d, buffer=0x%x, buffer_len=%d\n", (
  // unsigned int )data, data_len, (unsigned int) buffer, buffer_len);

  for (pos = 0; pos < (buffer_len - data_len);)
    {
      /*
       * printf("."); 
       */
      if (buffer[pos] == data[0])
	{
	  // printf("%c",data[0]);
	  data_pos = 0;
	  while (data_pos < data_len)
	    {

	      /*
	       * printf("%c %c %d\n", buffer[pos], data[data_pos],
	       * data_pos); 
	       */
	      if (buffer[++pos] != data[++data_pos])
		{
		  goto notMatched;
		}
	      printf ("%c", data[data_pos - 1]);

	    }
	  printf ("%c", data[data_pos]);
	  // printf("founded!\n");
	  return (pos - data_len);
	}
    notMatched:pos++;
    }
  return -1;
}

void kst_mem_cpy2 (char *src, char *dst, quint64 size)
{
  kst_mem_cpy (src, dst, size, size);
}

void kst_mem_cpy (char *src, char *dst, quint64 src_size, quint64 dst_size)
{
  quint64             len;
//      quint64 i=0;
  if (src == NULL || dst == NULL)
    return;
  len = (src_size > dst_size) ? dst_size : src_size;
//      i=len % sizeof(quint64);

  while (--len)
    {
      dst[len] = src[len];
    }

}

void hexdump (char *data, quint64 len)
{
  quint64             i = 0;
  quint8              a;
  quint64             pos = 0;
  printf ("0x%8x: ", pos);
  for (i = 0; i <= len;)
    {
      a = data[i++];
      pos++;

      if (i % 0x100 == 0)
	{
	  printf ("%2x\n\n0x%8x: ", a, pos);
	  continue;
	}

      if (i % 16 == 0)
	{

	  printf ("%2x\n0x%8x: ", a, pos);

	  continue;
	}
      if (i % 8 == 0)
	{
	  printf ("%2x  ||  ", a);
	  continue;
	}
      if (i % 4 == 0)
	{
	  printf ("%2x  |  ", a, pos & 0xFF);
	  continue;
	}
      printf ("%2x ", a);
    }

}

#ifdef kstNEW_DELETE
void               *operator    new[] (size_t size)
{
  return malloc (size);
}

void               *operator    new (size_t size)
{
  return malloc (size);
}

void operator         delete[] (void *ptr)
{
  free (ptr);
}

void operator         delete[] (void *ptr, size_t)
{
  free (ptr);
}

void operator    delete (void *ptr)
{
  free (ptr);
}

void operator    delete (void *ptr, size_t)
{
  free (ptr);
}
#endif