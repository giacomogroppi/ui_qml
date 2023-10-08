#include <QtTest>

#include "core/WList.h"
#include "Scheduler/Scheduler.h"
#include "utils/WCommonScript.h"

class test_Scheduler : public QObject
{
Q_OBJECT

    Scheduler *scheduler = nullptr;

private slots:
    void init();

    void cleanup();

    void test_timers();
    void test_timersConcurrency();
    void test_destructor();
};

void test_Scheduler::init ()
{
    W_ASSERT(scheduler == nullptr);
    scheduler = new Scheduler;
}

void test_Scheduler::cleanup()
{
    delete scheduler;
    scheduler = nullptr;
}

void test_Scheduler::test_timersConcurrency()
{
    constexpr auto max = 10000;
    QList<WTimer*> timers;
    bool callers[max];

    memset(callers, 0, sizeof(callers));

    for (int i = 0; i < max; i++) {
        auto func = [&callers, i]() {
            callers[i] = true;
        };

        auto timer = new WTimer(nullptr, func, (std::rand() % 1000 + 100), false);

        timer->setSingleShot(true);
        timers.append(timer);
        timer->start();
    }

    QThread::msleep(10000);

    for (int i = 0; i < max; i++) {
        if (callers[i] == true) {
            WDebug(true, "At:" << i);
        }
    }

    for (const auto& ref: callers)
        QCOMPARE(ref, true);

    delete scheduler;
    scheduler = nullptr;

    for (auto& timer : timers)
        delete timer;
}

void test_Scheduler::test_destructor()
{
    delete scheduler;

    for (int i = 0; i < 5000; i++) {
        scheduler = new Scheduler;

        for (int j = 0; j < 500; j++) {
            scheduler->addTaskGeneric(new WTaskFunction(nullptr, []{}, true));
        }

        delete scheduler;
    }

    scheduler = nullptr;
}

void test_Scheduler::test_timers()
{
    return;
    delete scheduler;

    for (int i = 0; i < 500; i++) {
        scheduler = new Scheduler;

        bool call = false;
        auto *timer = new WTimer(nullptr, [&call] { call = true; }, 50, false);

        timer->start();

        QCOMPARE(call, false);

        std::this_thread::sleep_for(std::chrono::milliseconds(70));

        QCOMPARE(call, true);
        QCOMPARE(timer->isActive(), false);

        delete scheduler;
        delete timer;
    }

    scheduler = nullptr;
}

QTEST_GUILESS_MAIN(test_Scheduler)

#include "test_Scheduler.moc"
