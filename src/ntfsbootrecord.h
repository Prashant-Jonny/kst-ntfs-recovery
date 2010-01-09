/* 
 * $Header$ 
 */
#ifndef NTFSBOOTRECORD_H
#define NTFSBOOTRECORD_H
#include "common.h"

//

//
// "NTFS    " == 0x202020205346544E 
#define NTFS_OEM_ID 0x202020205346544E
#define NTFS_OEM_ID_SIZE 8
#define NTFS_END_OF_BOOTSECTOR_MAGIC 0xaa55
typedef struct ntfs_boot_sectd
{
  quint8              jump[3];	/* jump to boot code */
  quint64             oem_id;	/* NTFS_OEM_ID */

/* pbp - BIOS parameter block */
  quint16             bytes_per_sector;
  quint8              sectors_per_cluster;
  quint16             reserved_sectors;
  quint8              fats;
  quint16             root_entries;
  quint16             sectors;
  quint8              media_type;	/* 0xf8 = hard disk drive */
  quint16             sector_per_fat;
  quint16             sectors_per_track;
  quint16             heads;
  quint32             hidden_sectors;	/* offset to start partition */
  quint32             large_sectors;

  quint8              physical_drive;	/* 0x00 floppy, 0x80 hdd */
  quint8              current_head;
  quint8              extended_boot_signature;	/* 0x80 */
  quint8              reserved0;
  quint64             mft_location;
  quint64             mft_mirr_location;
  quint8              cluster_per_mft_record;
  quint8              reserved1[3];
  quint64             volume_serial_number;
  quint32             boot_sect_checksum;
  quint8              bootcode[426];
  quint16             end_of_bootsector_magic;
} __attribute__ ((__packed__)) ntfs_boot_sect;

class               NTFSBootRecord
{

protected:
  ntfs_boot_sect bs;

public:
  ntfs_boot_sect * getDataPrt ();
  bool                isValid ();
  void                setBs (void *value);
  void                getBs (void *buffer, quint64 buffersize);

                      NTFSBootRecord ();

};
#endif
