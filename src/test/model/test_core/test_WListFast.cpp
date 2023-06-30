#include <QtTest>
#include <utility>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "FileContainer/MemWritable.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTask.h"

class test_WListFast : public QObject
{
Q_OBJECT

private slots:
    // operator copy
    void test_copy ();
    void copy_not_empty();

    void append_2Argument();
    void operatorCopy();
    void appendObject();
    void appendMakeCopy();

    // iterator
    void iteratorTest1();
    void iteratorOperator();

    // test save
    void testBuildSave();
};

void test_WListFast::testBuildSave()
{
    for (int i = 0; i < 10000; i++) {
        Scheduler sched;
        WListFast<pressure_t> list;
        MemWritable writable;

        list.append(pressure_t(32.));
        list.append(pressure_t(57.));
        list.append(pressure_t(45.));
        list.append(pressure_t(9.));

        const auto result = WListFast<pressure_t>::writeMultiThread(
                writable,
                list,
                [&sched](std::function<void()> function) -> WTask * {
                    WTask *task = new WTaskFunction(nullptr, std::move(function));

                    task->setDestroyLater(false);

                    sched.addTaskGeneric(task);
                    return task;
                }
        );

        QCOMPARE(0, result);
    }
}

void test_WListFast::append_2Argument()
{
    WListFast<int> c;
    c.append(4);

    QCOMPARE_EQ(4, c.first());
    QCOMPARE_EQ(4, c.last());

    QCOMPARE_EQ(1, c.size());
    QCOMPARE_EQ(4, c.takeFirst());

    QCOMPARE_EQ(0, c.size());
}

void test_WListFast::test_copy()
{
    WListFast<int> c;

    c.append(4);
    c.append(6);

    WListFast<int> c2(c);

    QCOMPARE_EQ(2, c.size());
    QCOMPARE_EQ(2, c2.size());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

void test_WListFast::operatorCopy()
{
    WListFast<int> c;

    c.append(4);
    c.append(6);

    WListFast<int> c2 = c;

    QCOMPARE_EQ(c2.size(), c.size());

    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

void test_WListFast::appendObject()
{
    WListFast<Stroke *> c;
    Stroke *tmp = new StrokeNormal();

    c.append(tmp);

    QCOMPARE(tmp, c.at(0));
    QCOMPARE_EQ(1, c.size());
}

void test_WListFast::appendMakeCopy()
{
    WListFast<StrokeNormal> c;
    StrokeNormal tmp = {};

    c.append(tmp);

    QCOMPARE(tmp, c.at(0));
    QCOMPARE_EQ(1, c.size());
}

void test_WListFast::iteratorTest1()
{
    WListFast<Stroke*> list;
    QList<Stroke*> qtList;

    for (int i = 0; i < 400; i++) {
        auto *s = new StrokeNormal();
        list.append(s);
        qtList.append(s);
    }

    int i = 0;
    for (const auto *ref: list) {
        QCOMPARE(ref, qtList.at(i));
        i++;
    }
}

void test_WListFast::iteratorOperator()
{
    WListFast<Stroke*> list;
    QList<Stroke*> qtList;

    for (int i = 0; i < 400; i++) {
        auto *s = new StrokeNormal();
        list.append(s);
        qtList.append(s);
    }

    for (int i = 0; i < 400; i++) {
        QCOMPARE(*(list.begin() + i), *(qtList.begin() + i));
    }
}

void test_WListFast::copy_not_empty()
{
    WListFast<StrokeNormal> stroke;
    StrokeNormal strokeNormal;

    stroke.append(std::move(strokeNormal));

    QVERIFY(strokeNormal.isEmpty());
    QCOMPARE(1, stroke.size());
}

QTEST_GUILESS_MAIN(test_WListFast)

#include "test_WListFast.moc"
