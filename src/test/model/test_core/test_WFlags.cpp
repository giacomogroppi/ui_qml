#include <QtTest>

#include "core/WFlags.h"
#include "utils/WCommonScript.h"

class test_WFlags : public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testOr();
};

enum Flag {
    f1 = BIT(1),
    f2 = BIT(2),
    f3 = BIT(3),
    f4 = BIT(4),
    f5 = BIT(5),
    f6 = BIT(6),
    f7 = BIT(7),
    f8 = BIT(8),
    f9 = BIT(9),
    f10 = BIT(10),
    f11 = BIT(11),
    f12 = BIT(12)
};

void test_WFlags::testConstructor()
{
    WFlags<Flag> flag;
    flag = Flag::f1;

    QCOMPARE(flag, Flag::f1);

    flag = Flag::f8;
    const WFlags<Flag> r = flag & Flag::f1;
    QVERIFY(!(flag & Flag::f1));
    QVERIFY(flag & Flag::f8);
}

void test_WFlags::testOr()
{
    WFlags<Flag> flag;
    flag = WFlags<Flag>{Flag::f1} | WFlags<Flag>{Flag::f2};

    QVERIFY(flag & Flag::f1);
    QVERIFY(flag & Flag::f2);
}

QTEST_GUILESS_MAIN(test_WFlags)

#include "test_WFlags.moc"
