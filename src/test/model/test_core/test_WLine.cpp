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
    void test_intersect_precision_equals05_line_distance_1();
    void test_intersect_precision_equals09_line_distance_1();

    void test_belongs();

    void test_growLeft();
};

void test_WLine::test_growLeft()
{
    WLineTemplate<ExactNumber> line (10, 10, 20, 20);
    QCOMPARE(line.growLeft(10).pt1(), PointTemplate<ExactNumber>(0, 0));
    QCOMPARE(line.growLeft(10).pt2(), PointTemplate<ExactNumber>(20, 20));
    QCOMPARE(line.growRight(5).pt2(), PointTemplate<ExactNumber>(25, 25));
    QCOMPARE(line.growRight(5).pt1(), PointTemplate<ExactNumber>(10, 10));
}

void test_WLine::test_belongs()
{
    class data {
    public:
        WLineTemplate<ExactNumber> line;
        PointTemplate<ExactNumber> point;
        ExactNumber precision;
        bool shouldBe;
    };
    std::vector<data> tmp = {
            {WLineTemplate<ExactNumber>{{0, 0}, {200, 200}}, {100, 100}, {0},           true},
            {WLineTemplate<ExactNumber>{{40, 16}, {60, 35}}, {15, 40},   {0},           false},
            {WLineTemplate<ExactNumber>{{40, 16}, {60, 35}}, {40, 15},   {1},           true},
            {WLineTemplate<ExactNumber>{{40, 16}, {60, 35}}, {61, 35},   {1},           true},
            {WLineTemplate<ExactNumber>{{40, 16}, {60, 35}}, {61, 35},   {"0.99999"},   false},
            {WLineTemplate<ExactNumber>{{45, 40}, {45+342, 40+342}}, {388, 383}, 1,     true},
            {WLineTemplate<ExactNumber>{{45, 40}, {45+342, 40+342}}, {45+342+1, 40+342}, 1,     true},
            {WLineTemplate<ExactNumber>{{45, 40}, {45+342, 40+342}}, {45+342-1, 40+342}, 1,     true},
            {WLineTemplate<ExactNumber>{{45, 40}, {45+342, 40+342}}, {378, 373}, {0},     true}
    };

    for (const auto &ref: tmp) {
        const auto point = ref.point;
        QCOMPARE(ref.line.belongs(ref.point, ref.precision), ref.shouldBe);
    }
}

void test_WLine::test_intersect_precision_equals09_line_distance_1()
{
    WLineTemplate<ExactNumber> line1(40, 20, 60, 30);
    WLineTemplate<ExactNumber> line2(50, 26, 70, 45);

    QCOMPARE(
             WLineTemplate<ExactNumber>::intersect(
                     line1,
                     line2,
                     ExactNumber(".9")
                ),
                false
            );
}

void test_WLine::test_intersect_precision_equals05_line_distance_1()
{
    WLineTemplate<ExactNumber> line1(
            PointTemplate<ExactNumber>{ExactNumber(30), ExactNumber(10)},
            PointTemplate<ExactNumber>{ExactNumber(50), ExactNumber(20)});
    WLineTemplate<ExactNumber> line2(
            PointTemplate<ExactNumber>{ExactNumber{40}, ExactNumber{16}},
            PointTemplate<ExactNumber>{ExactNumber{60}, ExactNumber{35}});

    QCOMPARE(false, WLineTemplate<ExactNumber>::intersect(line1, line2, ExactNumber{".6"}));
}

void test_WLine::test_intersect_precision_equals1_line_distance_1()
{
    WLineTemplate<ExactNumber> line1(
            30, 10,
            50, 20);
    WLineTemplate<ExactNumber> line2(
            40, 16,
            60, 35);

    QCOMPARE(WLineTemplate<ExactNumber>::intersect(line1, line2, 1), true);
}

void test_WLine::test_intersect_precision_0_2()
{
    WLineTemplate<ExactNumber> vert(
            ExactNumber(100), ExactNumber(100),
            ExactNumber(100), ExactNumber(1000));
    WLineTemplate<ExactNumber> tmp1(
            ExactNumber(50), ExactNumber(50),
            ExactNumber(90), ExactNumber(150));

    QCOMPARE(
            WLineTemplate<ExactNumber>::intersect(vert, tmp1, 0, nullptr),
            false
    );
}

void test_WLine::test_intersect_precision_0_1()
{
    WLineTemplate<ExactNumber> vert(
            ExactNumber(100), ExactNumber(100),
            ExactNumber(100), ExactNumber(1000));
    WLineTemplate<ExactNumber> tmp1(
            ExactNumber(50), ExactNumber(50),
            ExactNumber(110), ExactNumber(150));

    QCOMPARE(
            WLineTemplate<ExactNumber>::intersect(vert, tmp1, ExactNumber(0), nullptr),
            true
    );
}

void test_WLine::test_intersect_precision_bigger_0()
{
    /*QVERIFY(
            WLine::intersect(WLine(1, 140, 70, 47), WLine(45, 90, 100, 120), 10, nullptr)
    );*/
}

void test_WLine::test_intersect_precision_0()
{
    WLineTemplate<ExactNumber> line1(100, 100, 100, 200);
    WLineTemplate<ExactNumber> line2(95, 90, 101, 175);
    WLineTemplate<ExactNumber> line3(95, 110, 101, 110);

    QCOMPARE(WLineTemplate<ExactNumber>::intersect(line1, line2, ExactNumber(0)), true);
    QCOMPARE(WLineTemplate<ExactNumber>::intersect(line1, line2, ExactNumber(0)), true);

    QCOMPARE(WLineTemplate<ExactNumber>::intersect(line2, line1, ExactNumber(0)), true);
    QCOMPARE(WLineTemplate<ExactNumber>::intersect(line3, line1, ExactNumber(0)), true);
}

QTEST_GUILESS_MAIN(test_WLine)

#include "test_WLine.moc"
