#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"
#include "core/WVector.h"
#include "Scheduler/Scheduler.h"
#include "touch/dataTouch/datastruct/utils_datastruct.h"
#include "core/ByteArray/WByteArray.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"

class test_WVector : public QObject
{
Q_OBJECT

private slots:
    void testAppendCopyConstructor();

    void removeIfAscendingElementNotPresent();
    void removeIfDescendingElementNotPresent();

    void removeIfAscendingElementPresentEnd();
    void removeIfDescendingElementPresentEnd();

    void removeIfAscendingElementPresentMiddle();
    void removeIfDescendingElementPresentMiddle();

    void removeIf_removeAllAscending();
    void removeIf_removeAllDescending();

    void saveMultiThread();

    // imported from WListFast
    void removeMultiple();
    void removeOne();
    void saveAndLoadsingleThreadZeroElement();
    void saveAndLoadSingleThread();
    void moveObjects();
    void operatorMove();
    void saveAndLoadSingleThreadCustomLambda();
    void testSaveSingleThread();
    void writeCallOnce();
    void testBuildSave();
    void append_2Argument();
    void test_copy();
    void operatorCopy();
    void appendObject();
    void appendMakeCopy();
    void iteratorTest1();
    void iteratorOperator();
    void copyListWithMoreItems();
    void copyListWithLessItem();
    void copy_not_empty();
};

void test_WVector::testAppendCopyConstructor ()
{
    WVector<int> arrayWriternote;
    std::vector<int> arrayStandard;
    const int size = std::pow(2, 20);

    for (int i = 0; i < size; i++) {
        int value = rand() % 2000000;
        arrayWriternote.append(value);
        arrayStandard.push_back(value);
    }

    QCOMPARE(arrayWriternote.size(), arrayStandard.size());

    for (int i = 0; i < size; i++) {
        QCOMPARE(arrayWriternote[i], arrayStandard[i]);
    }
}

template <class T>
const auto cmp = [](const T& t1, const T& t2 ) -> bool {
    return t1 >= t2;
};

void test_WVector::saveMultiThread()
{
    for (int i = 0; i < 100; i++) {
        MemWritable writable;
        WByteArray data;

        Scheduler sched;
        WVector<pressure_t> list;

        list.append(pressure_t(32.))
                .append(pressure_t(57.))
                .append(pressure_t(45.))
                .append(pressure_t(9.));

        const auto result = WVector<pressure_t>::writeMultiThread(
                writable,
                list,
                Scheduler::startNewTask
        );

        writable.merge([&](const void *d, size_t size) {
            data.append(static_cast<const char*>(d), size);
            return 0;
        });

        QCOMPARE(0, result);

        {
            VersionFileController versionController{};
            MemReadable readable;

            readable.setData(data.constData(), data.size());

            auto [res, listRead] = WVector<pressure_t>::loadMultiThread(
                    versionController,
                    readable,
                    Scheduler::startNewTask
            );

            QCOMPARE(0, res);
            QCOMPARE(list, listRead);
        }
    }
}

void test_WVector::removeIf_removeAllDescending()
{
    WVector<int> tmp = {
            1, 1, 1, 1, 1, 1, 1
    };

    tmp.removeOrderHighToLow(1, cmp<int>);

    const WVector<int> result = {};

    QCOMPARE(tmp, result);
}

void test_WVector::removeIf_removeAllAscending()
{
    return;
    WVector<int> tmp = {
        1, 1, 1, 1, 1, 1, 1
    };
    tmp.removeOrderLowToHigh(1, cmp<int>);

    const WVector<int> result = {};

    QCOMPARE(tmp, result);
}

void test_WVector::removeIfAscendingElementPresentMiddle()
{
    WVector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    tmp.removeOrderLowToHigh(5, cmp<int>);

    const WVector<int> result = {
            1, 2, 3, 4, 6, 7, 8, 9
    };

    QCOMPARE(tmp, result);
}

void test_WVector::removeIfDescendingElementPresentMiddle()
{
    WVector<int> tmp = {
            9, 8, 6, 5, 4, 3, 2, 1
    };
    tmp.removeOrderHighToLow(4, cmp<int>);

    const WVector<int> result = {
            9, 8, 6, 5, 3, 2, 1
    };

    QCOMPARE(tmp, result);
}

void test_WVector::removeIfAscendingElementPresentEnd()
{
    WVector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    tmp.removeOrderLowToHigh(7, cmp<int>);

    const auto result = WVector<int> {
            1, 2, 3, 4, 5, 6, 8, 9
    };
    QCOMPARE (tmp, result);
}

void test_WVector::removeIfDescendingElementPresentEnd()
{
    return;
    WVector<int> tmp = {
            7, 4, 3, 2, 1, 1, 1, 1
    };

    WVector<int> result = {
            7, 4, 3, 2
    };

    tmp.removeOrderHighToLow(1, cmp<int>);

    QCOMPARE(tmp, result);
}

void test_WVector::removeIfAscendingElementNotPresent()
{
    WVector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    tmp.removeOrderLowToHigh(10, cmp<int>);

    const auto result = WVector<int> {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    QCOMPARE (tmp, result);
}

void test_WVector::removeIfDescendingElementNotPresent()
{
    WVector<int> tmp = {
        7, 4, 3, 2, 1, 1, 1, 1
    };

    const auto result(tmp);

    tmp.removeOrderHighToLow(10, cmp<int>);

    QCOMPARE(tmp, result);
}


void test_WVector::removeMultiple()
{
    WVector<WByteArray> list ({
                                        WByteArray("tmp1"),
                                        WByteArray("banana"),
                                        WByteArray("prova"),
                                        WByteArray("tmp2"),
                                        WByteArray("tmp3"),
                                        WByteArray("tmp4"),
                                        WByteArray("tmp5"),
                                        WByteArray("tmp6"),
                                });

    auto shouldBe = WVector<WByteArray> ({
                                                   WByteArray("tmp1"),
                                                   WByteArray("tmp3"),
                                                   WByteArray("tmp4"),
                                                   WByteArray("tmp5"),
                                                   WByteArray("tmp6"),
                                           });

    list.removeAll(1, 4);
    QCOMPARE(list.size(), 5);
    QCOMPARE(list, shouldBe);
}

void test_WVector::removeOne()
{
    WVector<WByteArray> list ({
                                        WByteArray("tmp1"),
                                        WByteArray("banana"),
                                        WByteArray("prova")
                                });

    list.removeAt(0);
    QCOMPARE(list.size(), 2);
}

void test_WVector::saveAndLoadsingleThreadZeroElement()
{
    WVector<pressure_t> list;
    MemWritable writable;
    MemReadable readable;
    WByteArray result;

    QCOMPARE(WVector<pressure_t>::write(writable, list), 0);

    writable.merge([&](const void *d, size_t size) {
        result.append(static_cast<const char*>(d), size);
        return 0;
    });

    readable.setData(result.constData(), result.size());

    const auto [r, d] = WVector<pressure_t>::load(VersionFileController(), readable);

    QCOMPARE(readable.getSeek(), readable.getMax());
    QCOMPARE(r, 0);
    QCOMPARE(d, list);
}

void test_WVector::saveAndLoadSingleThread()
{
    WVector<pressure_t> list;
    MemWritable writable;
    MemReadable readable;
    WByteArray result;

    for (int i = 0; i < 10000; i++)
        list.append(static_cast<double>(i));

    QCOMPARE(WVector<pressure_t>::write(writable, list), 0);

    writable.merge([&](const void *d, size_t size) {
        result.append(static_cast<const char*>(d), size);
        return 0;
    });

    readable.setData(result.constData(), result.size());

    const auto [r, d] = WVector<pressure_t>::load(VersionFileController(), readable);

    QCOMPARE(readable.getSeek(), readable.getMax());
    QCOMPARE(r, 0);
    QCOMPARE(d, list);
}

void test_WVector::moveObjects()
{
    WVector<WByteArray> list ({
                                        WByteArray("tmp1"),
                                        WByteArray("banana"),
                                        WByteArray("prova")
                                });

    list.move(0, 1);

    QCOMPARE(list.size(), 3);
    QCOMPARE(list.first(), WByteArray("banana"));
    QCOMPARE(list[1], WByteArray("tmp1"));
}

void test_WVector::operatorMove()
{
    WVector<WByteArray> list ({
                                        WByteArray("Tmp1"),
                                        WByteArray("Tmp2"),
                                        WByteArray("Tmp3"),
                                        WByteArray("Tmp4"),
                                        WByteArray("Tmp5"),
                                        WByteArray("Tmp6")
                                });

    WVector<WByteArray> result = {"Tmp7", "Tmp8", "Tmp9"};

    result = std::move(list);

    QCOMPARE(WVector<WByteArray>(), list);
    QCOMPARE(WVector<WByteArray> ({
                                            WByteArray("Tmp1"),
                                            WByteArray("Tmp2"),
                                            WByteArray("Tmp3"),
                                            WByteArray("Tmp4"),
                                            WByteArray("Tmp5"),
                                            WByteArray("Tmp6")
                                    }), result);
}

void test_WVector::saveAndLoadSingleThreadCustomLambda()
{
    WByteArray data;
    WVector<Unsigned> tmp;
    MemWritable writable;

    tmp.append(Unsigned(5u))
        .append(Unsigned(3u))
        .append(Unsigned(54u))
        .append(Unsigned(34u));

    const auto result = WVector<Unsigned>::write(writable, tmp);

    QVERIFY(result == 0);

    writable.merge([&](const void *d, size_t size) {
        data.append(static_cast<const char*>(d), size);
        return 0;
    });

    MemReadable readable;
    readable.setData(data.constData(), data.size());

    auto [resLoad, listLoad] = WVector<Unsigned>::load(
            VersionFileController(),
            readable
    );

    QVERIFY(resLoad == 0);
    QCOMPARE(tmp, listLoad);
}

void test_WVector::testSaveSingleThread()
{
    for (int i = 0; i < 100; i++) {
        WByteArray data;
        MemWritable writable;

        Scheduler sched;
        WVector<pressure_t> list;

        list.append(pressure_t(32.))
                .append(pressure_t(57.))
                .append(pressure_t(45.))
                .append(pressure_t(9.));

        const auto result = WVector<pressure_t>::write(
                writable,
                list
        );

        writable.merge([&](const void* d, size_t s) {
            data.append(static_cast<const char*>(d), s);
            return 0;
        });

        QCOMPARE(0, result);

        {
            MemReadable readable;

            readable.setData(data.constData(), data.size());

            auto [res, listRead] = WVector<pressure_t>::load(
                    VersionFileController(),
                    readable
            );

            QCOMPARE(0, res);
            QCOMPARE(list, listRead);
        }
    }
}

void test_WVector::writeCallOnce()
{
    for (int i = 0; i < 100; i++) {
        MemWritable writable;
        WByteArray data;

        Scheduler sched;
        WVector<pressure_t> list;

        list.append(pressure_t(32.))
                .append(pressure_t(57.))
                .append(pressure_t(45.))
                .append(pressure_t(9.));

        const auto result = WVector<pressure_t>::writeMultiThread(
                writable,
                list,
                Scheduler::startNewTask
        );

        writable.merge([&](const void *d, size_t size) {
            data.append(static_cast<const char*>(d), size);
            return 0;
        });

        QCOMPARE(0, result);

        {
            VersionFileController versionController{};
            MemReadable readable;

            readable.setData(data.constData(), data.size());

            auto [res, listRead] = WVector<pressure_t>::loadMultiThread(
                    versionController,
                    readable,
                    Scheduler::startNewTask
            );

            QCOMPARE(0, res);
            QCOMPARE(list, listRead);
        }
    }
}

void test_WVector::testBuildSave()
{
    for (int i = 0; i < 100; i++) {
        Scheduler sched;
        WVector<pressure_t> list;
        MemWritable writable;

        list.append(pressure_t(32.))
                .append(pressure_t(57.))
                .append(pressure_t(45.))
                .append(pressure_t(9.));

        const auto result = WVector<pressure_t>::writeMultiThread(
                writable,
                list,
                Scheduler::startNewTask
        );

        QCOMPARE(0, result);
    }
}

void test_WVector::append_2Argument()
{
    WVector<int> c;
    c.append(4);

    QCOMPARE_EQ(4, c.first());
    QCOMPARE_EQ(4, c.last());

    QCOMPARE_EQ(1, c.size());
    QCOMPARE_EQ(4, c.takeFirst());

    QCOMPARE_EQ(0, c.size());
}

void test_WVector::test_copy()
{
    WVector<int> c;

    c.append(4)
            .append(6);

    WVector<int> c2(c);

    QCOMPARE_EQ(2, c.size());
    QCOMPARE_EQ(2, c2.size());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

void test_WVector::operatorCopy()
{
    WVector<int> c;

    c.append(4);
    c.append(6);

    WVector<int> c2 = c;

    QCOMPARE_EQ(c2.size(), c.size());

    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

void test_WVector::appendObject()
{
    WVector<Stroke *> c;
    Stroke *tmp = new StrokeNormal();

    c.append(tmp);

    QCOMPARE(tmp, c.at(0));
    QCOMPARE_EQ(1, c.size());

    delete tmp;
}

void test_WVector::appendMakeCopy()
{
    WVector<StrokeNormal> c;
    StrokeNormal tmp = {};

    c.append(tmp);

    QCOMPARE(tmp, c.at(0));
    QCOMPARE_EQ(1, c.size());
}

void test_WVector::iteratorTest1()
{
    WVector<Stroke*> list;
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

void test_WVector::iteratorOperator()
{
    WVector<Stroke*> list;
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

void test_WVector::copyListWithMoreItems()
{
    WVector<long> list1;
    WVector<long> copiedList;

    for (long i = 0; i < (0x2 << 12); i++)
        list1.append(i);

    for (long i = 0; i < (0x2 << 16); i++)
        copiedList.append(i + (0x2 << 12));

    list1 = copiedList;

    QCOMPARE(list1.size(), copiedList.size());
    copiedList.clear();

    QCOMPARE(list1.size(), std::pow(2, 16));
}

void test_WVector::copyListWithLessItem()
{
    WVector<long> list1;
    WVector<long> copiedList;

    for (long i = 0; i < (0x2 << 12); i++)
        list1.append(i);

    for (long i = 0; i < (0x2 << 8); i++)
        copiedList.append(i + (0x2 << 12));

    list1 = copiedList;

    QCOMPARE(list1.size(), copiedList.size());
    copiedList.clear();

    QCOMPARE(list1.size(), std::pow(2, 8));
}

void test_WVector::copy_not_empty()
{
    WVector<StrokeNormal> stroke;
    StrokeNormal strokeNormal;

    stroke.append(std::move(strokeNormal));

    QVERIFY(strokeNormal.isEmpty());
    QCOMPARE(1, stroke.size());
}


QTEST_GUILESS_MAIN(test_WVector)

#include "test_WVector.moc"
