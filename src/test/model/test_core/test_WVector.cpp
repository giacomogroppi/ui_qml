#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"
#include "core/WVector.h"

class test_WVector : public QObject
{
Q_OBJECT

private slots:
    void removeIf();
};

void test_WVector::removeIf()
{
    WVector<int> tmp;

    tmp.append(4);
    tmp.append(3);
    tmp.append(2);

    tmp.removeOrder<true>(3, [](const int &v1, const int& v2) {
        return v1 > v2;
    });

    tmp.removeOrder(3, [](const int &v1, const int& v2) {
        return v1 > v2;
    });

    constexpr bool c = false;
    tmp.removeOrder<c>(3, [](const int& v1, const int& v2) -> bool { return v1 >= v2; });
}

QTEST_GUILESS_MAIN(test_WVector)

#include "test_WVector.moc"
