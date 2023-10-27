#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/PointTemplate.h"
#include <QRectF>
#include "core/ExactNumber/ExactNumber.h"

class test_PointTemplate : public QObject
{
Q_OBJECT

private slots:
    void rotate_distance_0();
    void rotate_distance_1_45();
    void rotate_distance_1_m_45();

    // distance 1 with cir = (1, 0) point (0, 0) 90°
    void test1();
};

void test_PointTemplate::test1()
{
    PointTemplate<double> point  {0, 0};
    PointTemplate<double> result {0, 1};
    const auto actual = point.rotate({1, 0}, 90);
    QVERIFY(WUtils::is_near(actual.x(), result.x(), 0.));
    QVERIFY(WUtils::is_near(actual.y(), result.y(), 0.));
}

void test_PointTemplate::rotate_distance_1_45()
{
    PointTemplate<double> point  {0, 1};
    PointTemplate<double> result {-1, 0};
    const auto actual = point.rotate({0, 0}, 90);
    QVERIFY(WUtils::is_near(actual.x(), result.x(), 0.));
    QVERIFY(WUtils::is_near(actual.y(), result.y(), WUtils::Power(10, -15)));
}

void test_PointTemplate::rotate_distance_1_m_45()
{
    PointTemplate<double> point { 0, 1 };
    PointTemplate<double> result { 1, 0 };
    const auto actual = point.rotate({0, 0}, -90);
    QVERIFY(WUtils::is_near(actual.x(), result.x(), 0.));
    QVERIFY(WUtils::is_near(actual.y(), result.y(), WUtils::Power(10, -15)));
}

void test_PointTemplate::rotate_distance_0()
{
    PointTemplate<double> point {
        0, 0
    };
    PointTemplate<double> result {0, 0};
    QCOMPARE(point.rotate({0, 0}, 45), result);
}

QTEST_GUILESS_MAIN(test_PointTemplate)

#include "test_PointTemplate.moc"
