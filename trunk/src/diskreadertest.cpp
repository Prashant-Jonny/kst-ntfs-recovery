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
 
#include "diskreadertest.h"
#include <QByteArray>


void DiskReaderTest::initTestCase()
{
  hdd = new DiskReader(this);
  QVERIFY2 (hdd != NULL, "hdd init error occured.");  
  QVERIFY(hdd->Open("/dev/sdb1"));
}


void DiskReaderTest::cleanupTestCase(){ 
    
  }
void DiskReaderTest::seek_test() {
    QVERIFY ( hdd->seek_b(0) );
}
void DiskReaderTest::read_0_sector(){  
  #define BLOCK_SIZE_TST_x 512
    QByteArray *a=NULL;

    a = hdd->ReadBytes(0, BLOCK_SIZE_TST_x);
    QVERIFY (a->size()==BLOCK_SIZE_TST_x);
    hdd->freeAllocatedMem();
    
  #undef BLOCK_SIZE_TST_x   
}
   
void DiskReaderTest::mem_allocate_free(){  
  #define BLOCK_SIZE_TST_x 1024
  #define BLOCK_SIZE_TST_y 1024
    QByteArray *a=NULL;
    quint64 i=BLOCK_SIZE_TST_y;
    while (i--) {
        a = hdd->ReadBytes(0, BLOCK_SIZE_TST_x);
    }
    hdd->freeAllocatedMem();
    
  #undef BLOCK_SIZE_TST_y  
  #undef BLOCK_SIZE_TST_x   
}   
void DiskReaderTest::mbr_reader(){
    bool initOK =this->hdd->InitFromMBR();
    QVERIFY ( initOK == true );
    if (initOK) {
       QVERIFY ( hdd->getBytesPerSector() == 512 );
       QVERIFY ( hdd->getSectorsPerCluster() == 8 );
       QVERIFY ( hdd->getHiddenSectors() == 63 );
    }
   
}
void DiskReaderTest::dr_test_2(){
     
  }
