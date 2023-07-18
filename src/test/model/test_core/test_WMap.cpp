#include <QtTest>
#include <utility>

#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "FileContainer/MemWritable.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTask.h"
#include "core/WMap.h"

class test_WMap : public QObject
{
Q_OBJECT

private slots:
    void append();
    void replace();
};

void test_WMap::replace()
{
    WMap<WString, WByteArray, WStringHash> tmp;
    tmp.set("Prova", {"Raw"});
    tmp.set("Prova", {"tmp"});
    QCOMPARE(tmp.get("Prova"), "tmp");
}

void test_WMap::append()
{
    WMap<WString, WByteArray, WStringHash> tmp;
    tmp.set("Prova", WByteArray("raw"));

    QCOMPARE(tmp.get("Prova"), WByteArray("raw"));
    QCOMPARE(tmp.isPresent("Prova"), true);
    QCOMPARE(tmp.isPresent("prova"), false);
}

QTEST_GUILESS_MAIN(test_WMap)

#include "test_WMap.moc"
