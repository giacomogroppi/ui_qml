#include <QtTest>
#include "utils/WCommonScript.h"

class test_WCommonScript : public QObject
{
    Q_OBJECT

private slots:
    void testOrderWithOrderList();
    void testOrderWithNotOrderList();
    void testOrderWithEmptyList();
};

void test_WCommonScript::testOrderWithOrderList()
{
    QList<int> list = {
        5, 6, 6, 6, 7
    };

    QCOMPARE(WCommonScript::is_order_list(list), 1);
}

void test_WCommonScript::testOrderWithNotOrderList()
{
    QList<int> list = {
        5, 6, 6, 5, 7
    };

    QCOMPARE(WCommonScript::is_order_list(list), 0);
}

void test_WCommonScript::testOrderWithEmptyList()
{
    QList<int> list = {
    };

    QCOMPARE(WCommonScript::is_order_list(list), 1);
}



QTEST_MAIN(test_WCommonScript)

#include "test_WCommonScript.moc"
