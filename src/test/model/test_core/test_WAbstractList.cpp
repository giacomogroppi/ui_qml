#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"
#include "core/WAbstractList.h"
#include "core/WVector.h"

class test_WAbstractList: public QObject
{
Q_OBJECT

private slots:
    void test_binary_search_single_item();
    void test_binary_search_right();

    void test_no_item();
    void test_all_item();

    void testReverse();

    void test_MidConst();
};

void test_WAbstractList::test_MidConst()
{
    WVector<int> test;
    int ref = 0;

    for (int i = 0; i < 400; i++)
        test.append(i);

    test.refMidConst(0, 32).forAll([&ref](int i) {
        QCOMPARE(i, ref);
        ref++;
    });
}

void test_WAbstractList::testReverse()
{
    WVector<int> tmp;

    for (int i = 0; i < 500; i++)
        tmp.append(i);

    int i = 499;

    for (const auto ref: WAbstractList::Reverse(tmp))
        QCOMPARE(ref, i--);

}

void test_WAbstractList::test_all_item()
{
    WVector<int> tmp = {1, 1, 1, 1, 1, 1, 1};
    const auto i = WAbstractList::binary_search<
                WVector<int>::iterator,
                int,
                false>
            (
                    tmp.begin(),
                    tmp.end(),
                    1
            );
    QCOMPARE(tmp.begin() - tmp.begin(), 0);
    QCOMPARE(i - tmp.begin(), 0);
    QCOMPARE(std::distance(i, tmp.begin()), 0);
    QCOMPARE(i, tmp.begin());
}

void test_WAbstractList::test_no_item()
{
    std::vector<int> tmp = {
            1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
    };

    const auto i = WAbstractList::binary_search<std::vector<int>::iterator, int, true>(tmp.begin(), tmp.end(), 5);

    QVERIFY(i == tmp.end());
}

void test_WAbstractList::test_binary_search_single_item()
{
    std::vector<int> tmp = {1};
    const auto i = WAbstractList::binary_search<std::vector<int>::iterator, int, true>(tmp.begin(), tmp.end(), 1);

    QVERIFY(i != tmp.end());

    QCOMPARE(*i, 1);
    QCOMPARE(i, tmp.begin() + 0);
}

void test_WAbstractList::test_binary_search_right()
{
    std::vector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
    };

    const auto i = WAbstractList::binary_search<std::vector<int>::iterator, int, true>(tmp.begin(), tmp.end(), 5);

    QVERIFY(i != tmp.end());
    QCOMPARE(*i, 5);
    QCOMPARE(i, tmp.begin() + 4);
}

QTEST_GUILESS_MAIN(test_WAbstractList)

#include "test_WAbstractList.moc"
