#include <QtTest>

#include "core/WList.h"
#include "Scheduler/Scheduler.h"
#include "utils/WCommonScript.h"

class test_Scheduler : public QObject
{
Q_OBJECT

private slots:
    void test_timers();
};

void test_Scheduler::test_timers()
{
    Scheduler scheduler;
    bool call = false;
    WTimer *timer = new WTimer(nullptr, [&call] { call = true; }, 100);
    scheduler.addTimer(timer);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    QCOMPARE(call, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(125));

    QCOMPARE(call, true);
    QCOMPARE(timer->isActive(), false);

    delete timer;
}

QTEST_GUILESS_MAIN(test_Scheduler)

#include "test_Scheduler.moc"
