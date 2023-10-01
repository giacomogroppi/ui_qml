#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>

class test_SharedPtr : public QObject
{
Q_OBJECT

private slots:
    void testLoad();
};

void test_SharedPtr::testLoad()
{
    SharedPtr<Stroke> tmp;

}

QTEST_GUILESS_MAIN(test_SharedPtr)

#include "test_SharedPtr.moc"
