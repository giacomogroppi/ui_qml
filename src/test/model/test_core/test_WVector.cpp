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

    void removeIfAscendingElementPresent();
    void removeIfDescendingElementPresent();
};

void test_WVector::removeIfAscendingElementPresent()
{
    WVector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    return;
    tmp.removeOrderAscending(7, [](const int& v1, const int& v2) -> bool {
        return v1 >= v2;
    });

    const auto result = WVector<int> {
            1, 2, 3, 4, 5, 6, 8, 9
    };
    QCOMPARE (tmp, result);
}

void test_WVector::removeIfDescendingElementPresent()
{
    WVector<int> tmp = {
            7, 4, 3, 2, 1, 1, 1, 1
    };

    WVector<int> result = {
            7, 4, 3, 2
    };

    tmp.removeOrderDescending(1, [](const int& v1, const int& v2) -> bool {
        return v1 >= v2;
    });

    QCOMPARE(tmp, result);
}

void test_WVector::removeIfAscendingElementNotPresent()
{
    WVector<int> tmp = {
            1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    tmp.removeOrderAscending(10, [](const int& v1, const int& v2) -> bool {
         return v1 >= v2;
    });

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

    tmp.removeOrderDescending(10, [](const int& v1, const int& v2) -> bool {
        return v1 >= v2;
    });

    QCOMPARE(tmp, result);
}

QTEST_GUILESS_MAIN(test_WVector)

#include "test_WVector.moc"
