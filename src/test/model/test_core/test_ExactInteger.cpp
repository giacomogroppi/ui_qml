#include <QtTest>
#include <utility>

#include "utils/WCommonScript.h"
#include "core/ExactNumber/ExactInteger.h"

// TODO: move this class in the right path
class test_ExactInteger : public QObject
{
Q_OBJECT

private slots:
    // constructor
    void constructorTest0();

    void moltiply_by_2();

    // gcd
    void gcd_0();

    // %
    void test_remainder();
};

class Prod {
public:
    std::string first, second, result;

    Prod(std::string first, std::string second, std::string result)
            : first(std::move(first))
            , second(std::move(second))
            , result(std::move(result)) {}
};

void test_ExactInteger::test_remainder()
{
    std::vector<Prod> tmp = {
            {"890542", "784", "702"},
            {"57", "57", "0"}
    };

    for (const auto &ref: tmp) {
        ExactInteger exact(ref.first);
        ExactInteger other(ref.second);
        QCOMPARE(exact % other, ExactInteger(ref.result));
    }
};

void test_ExactInteger::gcd_0()
{
    std::vector<Prod> tmp = {
            {"16", "180", "4"}
    };

    for (const auto &ref: tmp) {
        ExactInteger exact(ref.first);
        ExactInteger other(ref.second);
        QCOMPARE(exact.gcd(other), ExactInteger(ref.result));
    }
}

void test_ExactInteger::moltiply_by_2() {
    std::vector<Prod> tmp;

    tmp.emplace_back("57", "1", "57");
    tmp.emplace_back("54279", "2", "108558");
    tmp.emplace_back("23", "5", "115");
    tmp.emplace_back("78974892376786", "5", "394874461883930");
    tmp.emplace_back(
            "78974892376861783678431098099271389648768736478320978327986137846784367878372017894263187362178382891",
            "7489237894732897498267854903912378437899842570824768943764327698245798456924",
            "591461756721245500173911976911928794961649213090634939005291617404474317115360318586700449478058184543984374394257284697876357852143955015201876018765857119001959351837442087284"
            );
    tmp.emplace_back(
            "789758394785432908902147875493289023417568432098241743579208427137054780354892704213789785438901284309743012784579184391184032789576841089",
            "7549382754387532809214809849231754789347503425885071247894231789432890458910808971234786542901721839747964231976402318709423780759824164982137",
            "5962188405725928022222105893988037389429211410587253569264852368330477738415242878856858280195841813048192760291692420692957765098841725964717871884802668876387187651977251069398340658918531058855980993962278806381241988093250864627460923986960873684294612710820026066904572627193"
            );

    for (const auto &ref: tmp) {
        ExactInteger number(ref.first);
        number *= ref.second;
        QCOMPARE(ExactInteger(ref.result), number);
    }
}

void test_ExactInteger::constructorTest0()
{
    ExactInteger exact(43212);

    QCOMPARE(ExactInteger("43212"), exact);
}

QTEST_GUILESS_MAIN(test_ExactInteger)

#include "test_ExactInteger.moc"
