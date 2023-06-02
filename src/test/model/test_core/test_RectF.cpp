#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/RectF.h"
#include <QRectF>

class test_RectF : public QObject
{
Q_OBJECT

private:
    template<typename Func1, typename Func2>
    static void compareResult ( double xTopLeft1, double yTopLeft1, double xBottomRight1, double yBottomRight1,
                                double xTopLeft2, double yTopLeft2, double xBottomRight2, double yBottomRight2,
                                Func1 func1, Func2 func2)
    {
        const QRectF qtRect1 = QRectF (xTopLeft1, yTopLeft1, xBottomRight1, yBottomRight1);
        const QRectF qtRect2 = QRectF (xTopLeft2, yTopLeft2, xBottomRight2, yBottomRight2);

        const RectF rect1 = RectF (xTopLeft1, yTopLeft1, xBottomRight1, yBottomRight1);
        const RectF rect2 = RectF (xTopLeft2, yTopLeft2, xBottomRight2, yBottomRight2);

        const QRectF qtResult = func1(qtRect1, qtRect2);
        const RectF result = func2(rect1, rect2);

        QCOMPARE(qtResult.topLeft().x(), result.topLeft().x());
        QCOMPARE(qtResult.topLeft().y(), result.topLeft().y());

        QCOMPARE(qtResult.bottomRight().x(), result.bottomRight().x());
        QCOMPARE(qtResult.bottomRight().y(), result.bottomRight().y());
    }

private slots:
    // intersects
    void test_intersects1();
    void test_intersects2();
    void test_intersects3();

    // intersected
    void test_intersected1();
    void test_intersectedEmpty();
    void test_intersectedTopRight();
};

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
    };;

    QCOMPARE(qtRect1.intersects(qtRect2), rect1.intersects(rect2));
    QCOMPARE(qtRect2.intersects(qtRect1), rect2.intersects(rect1));
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

void test_RectF::test_intersectedTopRight()
{
    compareResult(
        0, 100, 100, 200,
        100, 0, 200, 300,
        [](const QRectF &r1, const QRectF &r2) {
            return r1.intersected(r2);
        },
        [](const RectF &r1, const RectF &r2) {
            return r1.intersected(r2);
        }
    );
}

QTEST_MAIN(test_RectF)

#include "test_RectF.moc"
