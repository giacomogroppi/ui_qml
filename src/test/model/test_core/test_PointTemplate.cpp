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
};

void test_PointTemplate::rotate_distance_1_45()
{
    PointTemplate<double> point {
            0, 1
    };
    PointTemplate<double> result {1, 0};
    QCOMPARE(point.rotate({0, 0}, 90), result);
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
