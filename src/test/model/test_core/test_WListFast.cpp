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
    void copyListWithLessItem();
    void copyListWithMoreItems();

    void append_2Argument();
    void operatorCopy();
    void appendObject();
    void appendMakeCopy();

    // iterator
    void iteratorTest1();
    void iteratorOperator();

    // save and load single thread
    void testSaveSingleThread();

    // test save multithread
    void testBuildSave();
    void writeCallOnce();

    // save & load single thread with custom lambda
    void saveAndLoadsingleThreadZeroElement();
    void saveAndLoadSingleThreadCustomLambda();
    void saveAndLoadSingleThread();

    // mid
    void midWithListEmpty();
    void midFrom0();
    void midToSize();
    void midCheckCreateNewObject();

    // operator move
    void operatorMove();
    void moveObjects();

    // remove
    void removeOne();
    void removeMultiple();
};

void test_WListFast::removeMultiple()
{
    WListFast<WByteArray> list ({
        WByteArray("tmp1"),
        WByteArray("banana"),
        WByteArray("prova"),
        WByteArray("tmp2"),
        WByteArray("tmp3"),
        WByteArray("tmp4"),
        WByteArray("tmp5"),
        WByteArray("tmp6"),
    });

    auto shouldBe = WListFast<WByteArray> ({
        WByteArray("tmp1"),
        WByteArray("tmp3"),
        WByteArray("tmp4"),
        WByteArray("tmp5"),
        WByteArray("tmp6"),
    });

    list.remove(1, 4);
    QCOMPARE(list.size(), 5);
    QCOMPARE(list, shouldBe);
}

void test_WListFast::removeOne()
{
    WListFast<WByteArray> list ({
        WByteArray("tmp1"),
        WByteArray("banana"),
        WByteArray("prova")
    });

    list.removeAt(0);
    QCOMPARE(list.size(), 2);
}

class WritableTest final: public WritableAbstract {
public:
    char *result = nullptr;
    size_t s = 0;

    auto write (const void *data, size_t size) -> int final
    {
        W_ASSERT(result == nullptr);
        result = (char *) malloc (size);
        WCommonScript::WMemcpy(result, data, size);
        s = size;
        return 0;
    }

    ~WritableTest() {
        free (result);
    }
};

void test_WListFast::saveAndLoadsingleThreadZeroElement()
{
    WListFast<pressure_t> list;
    MemWritable writable;
    MemReadable readable;
    WByteArray result;

    QCOMPARE(WListFast<pressure_t>::write(writable, list), 0);

    writable.merge([&](const void *d, size_t size) {
        result.append(static_cast<const char*>(d), size);
        return 0;
    });

    readable.setData(result.constData(), result.size());

    const auto [r, d] = WListFast<pressure_t>::load(VersionFileController(), readable);

    QCOMPARE(readable.getSeek(), readable.getMax());
    QCOMPARE(r, 0);
    QCOMPARE(d, list);
}

void test_WListFast::saveAndLoadSingleThread()
{
    WListFast<pressure_t> list;
    MemWritable writable;
    MemReadable readable;
    WByteArray result;

    for (int i = 0; i < 10000; i++)
        list.append(static_cast<double>(i));

    QCOMPARE(WListFast<pressure_t>::write(writable, list), 0);

    writable.merge([&](const void *d, size_t size) {
        result.append(static_cast<const char*>(d), size);
        return 0;
    });

    readable.setData(result.constData(), result.size());

    const auto [r, d] = WListFast<pressure_t>::load(VersionFileController(), readable);

    QCOMPARE(readable.getSeek(), readable.getMax());
    QCOMPARE(r, 0);
    QCOMPARE(d, list);
}

void test_WListFast::moveObjects()
{
    WListFast<WByteArray> list ({
        WByteArray("tmp1"),
        WByteArray("banana"),
        WByteArray("prova")
    });

    list.move(0, 1);

    QCOMPARE(list.size(), 3);
    QCOMPARE(list.first(), WByteArray("banana"));
    QCOMPARE(list[1], WByteArray("tmp1"));
}

void test_WListFast::operatorMove()
{
    WListFast<WByteArray> list ({
        WByteArray("Tmp1"),
        WByteArray("Tmp2"),
        WByteArray("Tmp3"),
        WByteArray("Tmp4"),
        WByteArray("Tmp5"),
        WByteArray("Tmp6")
    });

    WListFast<WByteArray> result = {"Tmp7", "Tmp8", "Tmp9"};

    result = std::move(list);

    QCOMPARE(WListFast<WByteArray>(), list);
    QCOMPARE(WListFast<WByteArray> ({
        WByteArray("Tmp1"),
        WByteArray("Tmp2"),
        WByteArray("Tmp3"),
        WByteArray("Tmp4"),
        WByteArray("Tmp5"),
        WByteArray("Tmp6")
    }), result);
}

void test_WListFast::midCheckCreateNewObject()
{
    WListFast<WByteArray> resultMid;

    {
        WListFast<WByteArray> list;
        list.append(WByteArray("Tmp0"))
            .append(WByteArray("Tmp1"))
            .append(WByteArray("Tmp2"))
            .append(WByteArray("Tmp3"))
            .append(WByteArray("Tmp4"))
            .append(WByteArray("Tmp5"));

        resultMid = list.mid(1, 4);

        QCOMPARE(WListFast<WByteArray>({
            WByteArray("Tmp1"),
            WByteArray("Tmp2"),
            WByteArray("Tmp3")
        }), resultMid);
    }

    QCOMPARE(WListFast<WByteArray>({
        WByteArray("Tmp1"),
        WByteArray("Tmp2"),
        WByteArray("Tmp3")
    }), resultMid);
}

void test_WListFast::midToSize()
{
    WListFast<int> list;

    list.append(5)
            .append(3)
            .append(6)
            .append(4)
            .append(8)
            .append(21);

    QCOMPARE(WListFast<int>({4, 8, 21}), list.mid(3, 6));
}

void test_WListFast::midFrom0()
{
    WListFast<int> list;

    list.append(5)
        .append(3)
        .append(6)
        .append(4)
        .append(8)
        .append(21);

    QCOMPARE(WListFast<int>({5, 3, 6}), list.mid(0, 3));
}

void test_WListFast::midWithListEmpty()
{
    WListFast<int> list;
    QCOMPARE(WListFast<int>(), list.mid(0, 0));
}

void test_WListFast::saveAndLoadSingleThreadCustomLambda()
{
    WListFast<size_t> tmp;
    MemWritable writable;
    WritableTest writableTest;

    tmp
        .append(5)
        .append(3)
        .append(54)
        .append(34);

    const auto result = WListFast<size_t>::write(writable, tmp, [](WritableAbstract &writable, size_t d) -> int {
        if (writable.write(&d, sizeof(size_t)) < 0)
            return -1;
        return 0;
    });

    QVERIFY(result == 0);

    writable.merge(writableTest);
    MemReadable readable;
    readable.setData(writableTest.result, writableTest.s);

    auto [resLoad, listLoad] = WListFast<size_t>::load(
            VersionFileController(),
            readable,
            []( const VersionFileController &,
                ReadableAbstract &readable
               ) -> WPair<int, size_t>
                {
                    size_t result;
                    if (readable.read(&result, sizeof(result)) < 0)
                        return {-1, 0};
                    return {0, result};
                }
    );

    QVERIFY(resLoad == 0);
    QCOMPARE(tmp, listLoad);
}

void test_WListFast::testSaveSingleThread()
{
    for (int i = 0; i < 100; i++) {
        WritableTest writableFinal;
        MemWritable writable;

        Scheduler sched;
        WListFast<pressure_t> list;

        list.append(pressure_t(32.))
            .append(pressure_t(57.))
            .append(pressure_t(45.))
            .append(pressure_t(9.));

        const auto result = WListFast<pressure_t>::write(
                writable,
                list
        );

        writable.merge(writableFinal);

        QCOMPARE(0, result);

        {
            MemReadable readable;

            readable.setData(writableFinal.result, writableFinal.s);

            auto [res, listRead] = WListFast<pressure_t>::load(
                    VersionFileController(),
                    readable
            );

            QCOMPARE(0, res);
            QCOMPARE(list, listRead);
        }
    }
}

void test_WListFast::writeCallOnce()
{
    for (int i = 0; i < 100; i++) {
        WritableTest writableFinal;
        MemWritable writable;

        Scheduler sched;
        WListFast<pressure_t> list;

        list.append(pressure_t(32.))
            .append(pressure_t(57.))
            .append(pressure_t(45.))
            .append(pressure_t(9.));

        const auto result = WListFast<pressure_t>::writeMultiThread(
                writable,
                list,
                Scheduler::startNewTask
        );

        writable.merge(writableFinal);

        QCOMPARE(0, result);

        {
            VersionFileController versionController{};
            MemReadable readable;

            readable.setData(writableFinal.result, writableFinal.s);

            auto [res, listRead] = WListFast<pressure_t>::loadMultiThread(
                    versionController,
                    readable,
                    Scheduler::startNewTask
            );

            QCOMPARE(0, res);
            QCOMPARE(list, listRead);
        }
    }
}

void test_WListFast::testBuildSave()
{
    for (int i = 0; i < 100; i++) {
        Scheduler sched;
        WListFast<pressure_t> list;
        MemWritable writable;

        list.append(pressure_t(32.))
            .append(pressure_t(57.))
            .append(pressure_t(45.))
            .append(pressure_t(9.));

        const auto result = WListFast<pressure_t>::writeMultiThread(
                writable,
                list,
                Scheduler::startNewTask
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

    c.append(4)
        .append(6);

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

    delete tmp;
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

    for (auto *ref: list) {
        delete ref;
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

    for (auto *ref: list)
        delete ref;
}

void test_WListFast::copyListWithMoreItems()
{
    WListFast<long> list1;
    WListFast<long> copiedList;

    constexpr auto max = (2ul << 14);
    constexpr auto min = (2ul << 12);

    for (long i = 0; i < min; i++)
        list1.append(i);

    for (long i = 0; i < max; i++)
        copiedList.append(i + min);

    list1 = copiedList;

    QCOMPARE(list1.size(), copiedList.size());
    copiedList.clear();

    QCOMPARE(list1.size(), max);
}

void test_WListFast::copyListWithLessItem()
{
    WListFast<long> list1;
    WListFast<long> copiedList;

    constexpr auto max = (2ul << 14);
    constexpr auto min = (2ul << 12);

    for (long i = 0; i < max; i++)
        list1.append(i);

    for (long i = 0; i < min; i++)
        copiedList.append(i + (0x2 << 20));

    list1 = copiedList;

    QCOMPARE(list1.size(), copiedList.size());
    copiedList.clear();

    QCOMPARE(list1.size(), min);
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
