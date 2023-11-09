#include <QtTest>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "core/PointF.h"
#include "Scheduler/WTimer.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"

#define REPEATED_TEST(stuff, numberOfTimes) \
    cleanup();                                        \
    for (int _i = 0; _i < (numberOfTimes); _i++) { \
        init();                              \
        stuff;\
        cleanup();\
    }

class test_WTimer : public QObject
{
Q_OBJECT
private:
    Scheduler *scheduler = nullptr;

private slots:
    void init();

    void singleTimer();
    void secondTimerAddWithLessTime();

    void cleanup();
};

void test_WTimer::init()
{
    Allocators::init();

    if (scheduler == nullptr) {
        scheduler = new Scheduler();
    }
}

void test_WTimer::cleanup()
{
    delete scheduler;
    scheduler = nullptr;

    Allocators::exit();
}

void test_WTimer::singleTimer()
{
    REPEATED_TEST(
        WDebug(true, _i);
        std::atomic<bool> call = false;

        auto *timer = new WTimer(nullptr, [&]{
            call = true;
        }, 200, ~WTimer::Flag::onMainThread | WTimer::Flag::singleShot);

        timer->start();

        QThread::msleep(200 + 50);

        QCOMPARE(call, true);

        delete timer;
    , 500);

}

void test_WTimer::secondTimerAddWithLessTime()
{
    std::atomic<bool> call1, call2;

    call1 = false;
    call2 = false;

    auto *timer1 = new WTimer(nullptr, [&]{
        call1 = true;
    }, 2000, ~WTimer::Flag::onMainThread | WTimer::Flag::singleShot);

    auto *timer2 = new WTimer(nullptr, [&]{
        call2 = true;
    }, 200, ~WTimer::Flag::onMainThread);

    timer1->start();
    timer2->start();

    QThread::msleep(200 + 20);

    QCOMPARE(call2, true);
    QCOMPARE(call1, false);

    QThread::msleep(2000);

    QCOMPARE(call1, true);

    delete timer1;
    delete timer2;
}

QTEST_GUILESS_MAIN(test_WTimer)

#include "test_WTimer.moc"
