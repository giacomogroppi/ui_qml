#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"
#include "core/WHeap.h"

class test_WHeap : public QObject
{
Q_OBJECT

private slots:
    void test_makeHeapHighToLow();
    void test_makeHeapLowToHigh();

    void testAddNewElementDescending();
    void testAddNewElementAscending();

    // TODO: rename
    void removeObjectNotPresent1();
    void removeObjectNotPresent2();
};

void test_WHeap::test_makeHeapLowToHigh()
{
    WVector<int> list = {5, 3, 6, 3, 56, 66};

    std::make_heap(list.rbegin(), list.rend(), [](const int v1, const int v2) {
        return v1 < v2;
    });

    auto result = WVector{66, 56, 6, 5, 3, 3};

    QCOMPARE(list.first(), 3);
}

void test_WHeap::test_makeHeapHighToLow()
{
    WVector<int> list = {5, 3, 6, 3, 56, 66};

    std::make_heap(list.begin(), list.end(), [](const int v1, const int v2) {
        return v1 < v2;
    });

    auto result = WVector{66, 56, 6, 5, 3, 3};

    QCOMPARE(list.first(), 66);
}

void test_WHeap::removeObjectNotPresent2()
{
    WHeap<int, true> heap;

    heap.add(4);
    heap.add(6);
    heap.add(3);

    QCOMPARE(heap.size(), 3);

    heap.removeIfPresent(2);

    QCOMPARE(heap.size(), 3);
}

void test_WHeap::removeObjectNotPresent1()
{
    WHeap<int, false> heap;

    heap.add(3);
    heap.add(6);

    heap.removeIfPresent(2);

    QCOMPARE(heap.size(), 2);
}

void test_WHeap::testAddNewElementDescending()
{
    WHeap<int, false> heap;

    heap.add(3);
    heap.add(6);

    QCOMPARE(heap.getFirst(), 6);
}

void test_WHeap::testAddNewElementAscending()
{
    WHeap<int, true> heap;

    heap.add(3);
    heap.add(6);
    heap.add(5);

    QCOMPARE(heap.getFirst(), 3);
}

QTEST_GUILESS_MAIN(test_WHeap)

#include "test_WHeap.moc"
