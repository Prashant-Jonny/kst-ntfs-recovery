
/* 
 * That is a part of kst-ntfs-recovery source code
 * (c) 2010 Eugeny Borisov
 *
 * Last changed by:   $Author$
 * Last changed date: $Date$
 * Revision:          $Rev$
 * URL:               $HeadURL$
 *
 */
#define PART_ERR_PRESENT (this->partition->error() != QFile::NoError)
#define PART_ERR_CHECK if ( PART_ERR_PRESENT ) return false;
  
#include "diskreader.h"
#include "ntfs3g_layout.h"

/*
 * Читает указанное количество секторов (count),
 * начиная со смещения startOffset от начала диска
 * 
 * Возвращает QByteArray, либо NULL при неудаче. 
 */
QByteArray * DiskReader::ReadSectors ( qint64 startOffset, quint64 count )
{
    PART_ERR_CHECK;
    throw("not implemented");
}
/*
 * Позиционирует указатель чтения на смещение absPos байтов,
 * относительно начала раздела.
 */
bool DiskReader::seek_b ( quint64 absPos )
{
   PART_ERR_CHECK;
   return this->partition->seek(absPos);
}

/*
 * Читает указанное количество секторов (count),
 * начиная со смещения startOffset относительно начала раздела
 * 
 * Возвращает QByteArray, либо NULL при неудаче. 
 */
QByteArray * DiskReader::ReadBytes ( quint64 startOffset, quint64 count )
{
  PART_ERR_CHECK;
  QByteArray *retval;
  quint64 bytesReaded=0;
  
  if ( (count == 0) || (this->seek_b(startOffset) == false))
    {
      return NULL;
    }
  
   retval = new QByteArray(count,NULL );
   if (retval == NULL) return false;
   bytesReaded = this->partition->read(retval->data(), count);
   
   if (bytesReaded != count) {
       delete retval;
       return NULL;
   }
   this->AllocatedMem.append(retval);
   return retval;
}

/*
 * Устанавливает внутренние переменные, 
 * которые влияют на работу функции this->ReadClasters 
 * BytesPerSector      Количество байтов на сектор
 * SectorsPerClaster   Количество секторов в кластере
 * HiddenSectors       Количество скрытых секторов -
 *                       по сути - смещение нулевого кластера в секторах 
 */

void DiskReader::initClustersInfo ( quint64 BytesPerSector,
                               quint64 SectorsPerCluster,
                               quint64 HiddenSectors )
{
this->BytesPerSector = BytesPerSector;
  this->SectorsPerCluster = SectorsPerCluster;
  this->HiddenSectors = HiddenSectors;
  
  this->FirstClusterOffsetInBytes = this->BytesPerSector 
                                    * this->HiddenSectors;
  this->BytesPerCluster = this->BytesPerSector*this->SectorsPerCluster;
}

/*
 * Читает указанное количество кластеров (count),
 * начиная со смещения startOffset 
 * от конца скрытых секторов this->HiddenSectors
 * Возвращает QByteArray, либо NULL при неудаче. 
 */
QByteArray * DiskReader::ReadClusters ( quint64 startOffset,
                                        quint64 count )
{
  PART_ERR_CHECK;
  if ( this->BytesPerSector==0 )
    {
      return NULL;
    }
    
   throw("not implemented");
}

///*
 //* Попытка инициализации, используя MBR
 //* Если удачна, то вызывает this->initClastersInfo() 
 //*/

bool DiskReader::InitFromMBR (  ){
  PART_ERR_CHECK;
  QByteArray *zeroSector;
  NTFS_BOOT_SECTOR *bs;
  
  zeroSector = this->ReadBytes(0,512);
  if (zeroSector == false)
    { 
      return false;
    }
   
  bs =  ( NTFS_BOOT_SECTOR * ) zeroSector->constData();
  
  if ( ( bs->end_of_sector_marker != magicEND_OF_BOOT_SECTOR ) 
     ||( bs->oem_id != magicNTFS ) )
    {
      this->freeAllocatedMem();
      return false;
    }
  
  this->initClustersInfo(bs->bpb.bytes_per_sector,
        bs->bpb.sectors_per_cluster,
        bs->bpb.hidden_sectors
        );
        
  

  return true;
}

/*
 * Открывает файл/раздел
 */
bool DiskReader::Open(QString filename)
{

  this->partition = new QFile(this);
  if (PART_ERR_PRESENT) 
    {
      return false;
    }
  
  this->partition->setFileName(filename);
  if (!this->partition->exists())
    {
      return false;
    }
  
  this->partition->open(QIODevice::ReadOnly);
  return (PART_ERR_PRESENT) ? false : true;

}

/*
 * закрывает файл/раздел и удаляет информацию о нем.
 */ 

void DiskReader::Close(){
  if (this->partition != NULL) 
    {
     this->partition->close();
     delete this->partition;
     this->partition=NULL;     
    }
    this->BytesPerCluster=0;
}



DiskReader::DiskReader(QObject *parent) : QObject(parent)
{
  this->partition=NULL;
  this->BytesPerCluster=0;

}
/*
 * Пробегается по списку известной выделенной памяти и освобождае её
 */
void DiskReader::freeAllocatedMem(){
  qint64 i=0, j=0;
  QByteArray *target;
  j= this->AllocatedMem.size();
  if (j==0) return;
   for (i = 0; i < j; ++i) {
     target = this->AllocatedMem.at(i);
     if (target != NULL) 
       {
        try {
          delete target;
        } catch(...) {
         qDebug() << "error when free ByteArray memory at pos" << i; 
        }
       }
    }
    
    this->AllocatedMem.clear();
}

DiskReader::~DiskReader(){
 if (this->partition != NULL) 
   {
     this->partition->close();
     delete this->partition;
   }
 this->freeAllocatedMem();
}
  #undef PART_ERR_PRESENT

/*
 * Возвращает кластер с указанным смещением
 */
QByteArray *DiskReader::operator[](quint64 index)
{
  return this->ReadClusters(index,1);
}

