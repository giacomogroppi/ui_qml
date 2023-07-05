#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/ExactNumber/ExactNumber.h"

// TODO: move this class in the right path
class test_ExactNumber : public QObject
{
Q_OBJECT

private slots:
    // intersects
    void test_sum_positive();
    void test_periodic();
    void test_some_long_float();

    void test_with_cicle();
    void test_big_number();
};

void test_ExactNumber::test_big_number()
{
    constexpr auto num1 = 4824325;
    constexpr auto num2 = 4832;

    constexpr auto num3 = 490432;
    constexpr auto num4 = 5893;

    ExactNumber exact1 (num1, num2);
    ExactNumber exact2 (num3, num4);

    const auto result = exact1 * exact2;
    QCOMPARE(ExactNumber(268704259776, 28474976), result);
}

void test_ExactNumber::test_with_cicle()
{
    using namespace std;
    constexpr auto e = 10;

    vector<pair<int, int>> listDiv;
    vector<pair<int, int>> listProd;

    listDiv.reserve(e);
    listProd.reserve(e);

    ExactNumber result (std::rand() % 1000, std::rand() % 1000);
    const auto initial = result;

    for (int i = 0; i < e; i++) {
        const auto v1 = std::rand() % 4652+1;
        const auto v2 = std::rand() % 8545+1;

        if (std::rand() % 2 == 1) {
            result *= ExactNumber(v1, v2);
            listProd.emplace_back(v1, v2);
        } else {
            result /= ExactNumber(v1, v2);
            listDiv.emplace_back(pair(v1, v2));
        }
    }

    for (int i = 0; i < e; i++) {
        if (i < listDiv.size())
            result *= ExactNumber(listDiv[i].first, listDiv[i].second);

        if (i < listProd.size())
            result /= ExactNumber(listProd[i].first, listProd[i].second);
    }

    QCOMPARE(initial, result);
}

void test_ExactNumber::test_some_long_float()
{
    ExactNumber exact (54212345, 7698243);
    exact *= ExactNumber(432, 908);
    exact *= ExactNumber(234789, 123789);
    exact *= ExactNumber(908, 432);
    exact *= ExactNumber(123789, 234789);
    QCOMPARE(exact, ExactNumber(54212345, 7698243));
}

void test_ExactNumber::test_periodic()
{
    ExactNumber exact(1, 3);
    exact *= ExactNumber((long) 4);
    exact /= ExactNumber((long) 3);
    exact *= ExactNumber((long) 3);
    exact *= ExactNumber((long) 3);

    QCOMPARE(4, exact);
}

void test_ExactNumber::test_sum_positive()
{
    constexpr long num1 = 3457983;
    constexpr long num2 = 243890;
    ExactNumber exact1(num1);
    ExactNumber exact2(num2);

    QCOMPARE(num1 + num2, exact1 + exact2);
}

QTEST_GUILESS_MAIN(test_ExactNumber)

#include "test_ExactNumber.moc"
