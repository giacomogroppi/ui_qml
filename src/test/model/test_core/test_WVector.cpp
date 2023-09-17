#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"
#include "core/WVector.h"

class test_WVector : public QObject
{
Q_OBJECT

private slots:
    void removeIfAscendingElementNotPresent();
    void removeIfDescendingElementNotPresent();

    void removeIfAscendingElementPresentEnd();
    void removeIfDescendingElementPresentEnd();

    void removeIfAscendingElementPresentMiddle();
    void removeIfDescendingElementPresentMiddle();

    void removeIf_removeAllAscending();
    void removeIf_removeAllDescending();
};

template <class T>
const auto cmp = [](const T& t1, const T& t2 ) -> bool {
    return t1 >= t2;
};

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

QTEST_GUILESS_MAIN(test_WVector)

#include "test_WVector.moc"
