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

#ifndef DISKREADER_H
#define DISKREADER_H

#include <QtCore>
#include <QList>
//#include "ntfs3g_layout.h"

class DiskReader: public QObject {
  // Associations
  // Attributes
  private:
    QMap<quint64,QByteArray> sectors;
    quint64 BytesPerCluster;
    quint64 BytesPerSector;
    quint64 HiddenSectors;
    quint8 SectorsPerCluster;
    quint32 FirstClusterOffsetInBytes;
    QFile *partition;
  // Operations
  public:
  QByteArray * operator [](quint64 index);
  
  qint64 getBytesPerSector() { return BytesPerSector; }
  qint64 getSectorsPerCluster() { return SectorsPerCluster; }
  qint64 getHiddenSectors() { return HiddenSectors; }
  
  DiskReader(QObject *parent);
  ~DiskReader();
    QByteArray * ReadSectors ( qint64 startOffset, quint64 count );
    bool seek_b ( quint64 absPos );
    QByteArray * ReadBytes ( quint64 startOffset, quint64 count );
    void initClustersInfo ( quint64 BytesPerSector,
                            quint64 SectorsPerCluster,
                            quint64 HiddenSectors );
    QByteArray * ReadClusters ( quint64 startOffset, quint64 count );
    bool InitFromMBR (  );
    bool Open(QString filename);
    void Close();
    QList <QByteArray *>  AllocatedMem;
    void freeAllocatedMem();
};

#endif
