#include <QtTest>
#include <utility>

#include "core/WLine.h"

class test_WLine : public QObject
{
Q_OBJECT

private slots:
    // precision 0
    void test_intersect_precision_0();
    void test_intersect_precision_0_1();
    void test_intersect_precision_0_2();

    void test_intersect_precision_bigger_0();
    void test_intersect_precision_equals1_line_distance_1();
};

void test_WLine::test_intersect_precision_equals1_line_distance_1()
{
    WLine line1(PointF(0, 10), PointF(20, 20));
    WLine line2(PointF(10, 16), PointF(30, 35));

    QVERIFY(WLine::intersect(line1, line2, 1.));
}

void test_WLine::test_intersect_precision_0_2()
{
    WLine vert(100., 100., 100., 1000.);
    WLine tmp1(50., 50., 90., 150.);

    QVERIFY(
            !WLine::intersect(vert, tmp1, 0, nullptr)
    );
}

void test_WLine::test_intersect_precision_0_1()
{
    WLine vert(100., 100., 100., 1000.);
    WLine tmp1(50., 50., 110., 150.);

    W_ASSERT(
            WLine::intersect(vert, tmp1, 0, nullptr)
    );
}

void test_WLine::test_intersect_precision_bigger_0()
{
    QVERIFY(
            WLine::intersect(WLine(1, 140, 70, 47), WLine(45, 90, 100, 120), 10, nullptr)
    );
}

void test_WLine::test_intersect_precision_0()
{
    WLine line1(PointF(100., 100.), PointF(100., 200.));
    WLine line2(PointF(95., 90.), PointF(101., 175.));
    WLine line3(PointF(95., 110.), PointF(101., 110.));

    QVERIFY(WLine::intersect(line1, line2, 0.));
    QVERIFY(WLine::intersect(line1, line2, 0.));

    QVERIFY(WLine::intersect(line2, line1, 0.));
    QVERIFY(WLine::intersect(line3, line1, 0.));
}

QTEST_GUILESS_MAIN(test_WLine)

#include "test_WLine.moc"
