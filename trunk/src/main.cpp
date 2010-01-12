#include <QCoreApplication>
#include "diskreader.h"
#include "diskreadertest.h"

#include <QtTest/QtTest>

//

int main(int argc, char ** argv)
{
	QCoreApplication app( argc, argv );
	DiskReader *hdd;
  DiskReaderTest t1;
  qDebug() << sizeof(QChar);
  QTest::qExec(&t1);

  app.exit();
  return 0;
}
