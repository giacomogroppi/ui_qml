#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/RectF.h"
#include <QRectF>
#include "core/ExactNumber/ExactNumber.h"

class test_RectF : public QObject
{
Q_OBJECT

private:

private slots:
    // intersects
    void test_intersects1();
    void test_intersects2();
    void test_intersects3();

    // contains
    void test_contains();

    // intersected
    void test_intersected1();
    void test_intersectedEmpty();
};

void test_RectF::test_contains()
{
    class Values {
    public:
        PointTemplate<ExactNumber> topLeft;
        PointTemplate<ExactNumber> bottomRight;
        PointTemplate<ExactNumber> point;
        ExactNumber precision;
        bool shouldBeIn;
        Values (
                PointTemplate<ExactNumber> topLeft,
                PointTemplate<ExactNumber> bottomRight,
                PointTemplate<ExactNumber> point,
                ExactNumber precision,
                bool shouldBeIn)
            : topLeft(std::move(topLeft))
            , bottomRight(std::move(bottomRight))
            , point(std::move(point))
            , precision(std::move(precision))
            , shouldBeIn(shouldBeIn) {};
    };

    std::vector<Values> tmp = {
            {
                {ExactNumber(0), ExactNumber(0)},
                {ExactNumber(100), ExactNumber(100)},
                {ExactNumber(10), ExactNumber(0)},
                ExactNumber(0), true}
    };

    for (const auto &ref: tmp) {
        RectTemplate<ExactNumber> rect (ref.topLeft, ref.bottomRight);
        QCOMPARE(ref.shouldBeIn, rect.contains(ref.point));
    }
}

void test_RectF::test_intersects1()
{
    const double topLeft1 = 0.;
    const double topLeft2 = 50.;

    const double bottomRight1 = 200;
    const double bottomRight2 = 100;

    QRectF qtRect1 {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };
    QRectF qtRect2 {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    RectF rect1 = {
            topLeft1, topLeft1,
            bottomRight1, bottomRight1
    };

    RectF rect2 = {
            topLeft2, topLeft2,
            bottomRight2, bottomRight2
    };;

    QCOMPARE(qtRect1.intersects(qtRect2), rect1.intersects(rect2));
}

void test_RectF::test_intersects2()
{
    const double topLeft1 = 0.;
    const double bottomRight1 = 200;

    const double topLeft2 = 100;
    const double bottomRight2 = 300;

    QRectF qtRect1 {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };
    QRectF qtRect2 {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    RectF rect1 = {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };

    RectF rect2 = {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    QCOMPARE(qtRect1.intersects(qtRect2), rect1.intersects(rect2));
    QCOMPARE(qtRect2.intersects(qtRect1), rect2.intersects(rect1));
}

void test_RectF::test_intersects3()
{
    const double topLeft1 = 0.;
    const double bottomRight1 = 200;

    const double topLeft2 = 200;
    const double bottomRight2 = 300;

    QRectF qtRect1 {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };
    QRectF qtRect2 {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    RectF rect1 = {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };

    RectF rect2 = {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    QCOMPARE(rect1.intersects(rect2), qtRect1.intersects(qtRect2));
    QCOMPARE(rect2.intersects(rect1), qtRect2.intersects(qtRect1));
}

void test_RectF::test_intersected1()
{
    const double topLeft1 = 0.;
    const double bottomRight1 = 200;

    const double topLeft2 = 150;
    const double bottomRight2 = 300;

    QRectF qtRect1 {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };
    QRectF qtRect2 {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    RectF rect1 = {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };

    RectF rect2 = {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    const auto qtRes1 = qtRect1.intersected(qtRect2);
    const auto res1   = rect1.intersected(rect2);

    QCOMPARE(qtRes1.topLeft().x(), res1.topLeft().x());
    QCOMPARE(qtRes1.topLeft().y(), res1.topLeft().y());
}

void test_RectF::test_intersectedEmpty()
{
    const double topLeft1 = 0.;
    const double bottomRight1 = 200;

    const double topLeft2 = 201;
    const double bottomRight2 = 300;

    RectF rect1 = {
        topLeft1, topLeft1,
        bottomRight1, bottomRight1
    };

    RectF rect2 = {
        topLeft2, topLeft2,
        bottomRight2, bottomRight2
    };

    QVERIFY(rect1.intersected(rect2).isNull());
}


QTEST_GUILESS_MAIN(test_RectF)

#include "test_RectF.moc"
