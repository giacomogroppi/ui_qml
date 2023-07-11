#include <QtTest>
#include <utility>

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

    void test_sign_plus();

    // constructor
    void test_constructor_string();
};

class ValueTest {
public:
    WString num1, den1;
    WString num2, den2;
    WString numResult, denResult;
    ValueTest(WString num1, WString den1, WString num2, WString den2, WString numResult,
              WString denResult)
              : num1(std::move(num1))
              , den1(std::move(den1))
              , num2(std::move(num2))
              , den2(std::move(den2))
              , numResult(std::move(numResult))
              , denResult(std::move(denResult))
              {};
};

void test_ExactNumber::test_constructor_string()
{
    class ValueTestStringConstructor {
    public:
        WString value, numResult, denResult;
        ValueTestStringConstructor(WString value, WString numResult, WString denResult)
            : value(std::move(value))
            , numResult(std::move(numResult))
            , denResult(std::move(denResult)) {}
    };

    std::vector<ValueTestStringConstructor> tmp = {
            {".9", "9", "10"},
            {"123.", "123", "1"},
            {"2953.3413", "29533413", "10000"}
    };

    for (const auto &ref: std::as_const(tmp)) {
        QCOMPARE(ExactNumber(ref.value), ExactNumber(ref.numResult, ref.denResult));
    }
}

void test_ExactNumber::test_sign_plus()
{
    std::vector<ValueTest> tmp = {
            {"43",  "4", "-87", "2", "-131", "4"},
            {"-87", "2", "43",  "4", "-131", "4"},
            {"52",  "6", "9457", "8", "28579", "24"}
    };

    for (const auto &ref: std::as_const(tmp)) {
        ExactNumber exact1(ref.num1, ref.den1);
        ExactNumber exact2(ref.num2, ref.den2);
        const auto result = exact1 + exact2;
        QCOMPARE(ExactNumber(ref.numResult, ref.denResult), result);
    }
}

void test_ExactNumber::test_big_number()
{
    std::vector<ValueTest> tmp = {
            {"4824325", "4832", "490432", "5893", "73937604950", "889843"}
    };

    for (const auto &ref: std::as_const(tmp)) {
        ExactNumber exact1(ref.num1, ref.den1);
        ExactNumber exact2(ref.num2, ref.den2);
        const auto result = exact1 * exact2;
        QCOMPARE(ExactNumber(ref.numResult, ref.denResult), result);
    }
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
    exact *= ExactNumber((int) 4);
    exact /= ExactNumber((int) 3);
    exact *= ExactNumber((int) 3);
    exact *= ExactNumber((int) 3);

    QCOMPARE(ExactNumber(4, 1), exact);
}

void test_ExactNumber::test_sum_positive()
{
    constexpr int num1 = 3457983;
    constexpr int num2 = 243890;
    ExactNumber exact1(num1);
    ExactNumber exact2(num2);

    QCOMPARE(ExactNumber(num1 + num2), exact1 + exact2);
}

QTEST_GUILESS_MAIN(test_ExactNumber)

#include "test_ExactNumber.moc"
