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
 
#ifndef DISKREADERTEST_H
#define DISKREADERTEST_H

#include <QtTest/QtTest>
#include "diskreader.h"

//
class DiskReaderTest : public QObject
{
Q_OBJECT
public:
 DiskReader *hdd;
   
private slots:
     void initTestCase();
     
     void seek_test();
     void read_0_sector();
     void mem_allocate_free();
     void mbr_reader();
     void dr_test_2();

     void cleanupTestCase();

	
};
#endif
