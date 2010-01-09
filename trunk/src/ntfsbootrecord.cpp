/* 
 * $Header$ 
 */
#include "ntfsbootrecord.h"
//
NTFSBootRecord::NTFSBootRecord ()
{
  //this->bs=NULL;
}

//

bool NTFSBootRecord::isValid ()
{
  DBG << this->bs.oem_id;
  if (this->bs.oem_id != NTFS_OEM_ID)
    return false;
  if (this->bs.end_of_bootsector_magic != NTFS_END_OF_BOOTSECTOR_MAGIC)
    return false;

  return true;

}

void NTFSBootRecord::setBs (void *value)
{

  kst_mem_cpy2 ((char *) value, (char *) &this->bs, sizeof (this->bs));
}

void NTFSBootRecord::getBs (void *buffer, quint64 buffersize)
{
  kst_mem_cpy ((char *) &this->bs, (char *) buffer, sizeof (this->bs),
	       buffersize);
}

ntfs_boot_sect     *NTFSBootRecord::getDataPrt ()
{
  return &this->bs;
}
