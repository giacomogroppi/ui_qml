#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/ExactNumber/ExactInteger.h"

// TODO: move this class in the right path
class test_ExactInteger : public QObject
{
Q_OBJECT

private slots:
    // constructor
    void constructorTest0();

    void add_90_number();
};

void test_ExactInteger::constructorTest0()
{
    ExactInteger exact(43212);

    QCOMPARE(exact.digitAt(0), 4);
    QCOMPARE(exact.digitAt(1), 3);
    QCOMPARE(exact.digitAt(2), 2);
    QCOMPARE(exact.digitAt(3), 1);
    QCOMPARE(exact.digitAt(4), 2);

}


void test_ExactInteger::add_90_number()
{
    ExactInteger integer;
    std::vector<int> digits = {
            5, 6, 3, 7, 8, 6, 8, 3, 2, 1, 7, 6, 5,
            4, 5, 3, 5, 6, 4, 7, 3, 6, 8, 9, 3, 6,
            7, 4, 3, 3, 3, 5, 7, 9, 2, 5, 6, 3, 1
    };

    for (int c: digits)
        integer.addDigit(c);

    for (int i = 0; i < digits.size(); i++) {
        int shouldBe = digits[i];
        int is = integer.digitAt(i);
        QCOMPARE(shouldBe, is);
    }
}

QTEST_GUILESS_MAIN(test_ExactInteger)

#include "test_ExactInteger.moc"
