#include <QtTest>

#include "core/WList.h"
#include "Scheduler/Scheduler.h"
#include "utils/WCommonScript.h"
#include "core/WListFast.h"
#include "touch/dataTouch/datastruct/utils_datastruct.h"

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

    void test_deadlocks1();
    void test_deadlocks2();
    void test_deadlocks3();
};

void test_Scheduler::test_deadlocks3()
{
    WListFast<WListFast<pressure_t>> tmp;
    class WritableTest: public WritableAbstract {
    public:
        int write(const void* d, size_t size) { return 0; }
    };

    WritableTest writable;

    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        tmp.append(WListFast<pressure_t>(512));
    }

    for (auto& l: tmp) {
        for (int i = 0; i < 512; i++) {
            l.append(pressure_t((double) i));
        }
    }

    auto result = WListFast<WListFast<pressure_t>>::writeMultiThread(writable, tmp, Scheduler::startNewTask);
    QCOMPARE(result, 0);
}

void test_Scheduler::test_deadlocks2()
{
    MemWritable writable;
    WListFast<Scheduler::Ptr<WTask>> list;

    for (int i = 0; i < 40; i++) {
        auto task = Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, []{
            WListFast<Scheduler::Ptr<WTask>> tmp;

            for (int j = 0; j < 40; j++) {
                tmp.append(Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, []{
                        //QThread::msleep(2);
                }, false)));
            }

            for (auto& r: tmp)
                Scheduler::addTaskGeneric(r);

            for (auto& r: tmp) {
                r->join();
                r.release();
            }
        }, false));

        list.append(task);
    }

    for (auto &t: list)
        Scheduler::addTaskGeneric(t);

    for (auto& t: list) {
        t->join();
        t.release();
    }
}

void test_Scheduler::test_deadlocks1()
{
    MemWritable writable;
    using type = WListFast<WListFast<WListFast<pressure_t>>>;
    WListFast<type> values;

    for (int i = 0; i < 32; i++)
        values.append(WListFast<WListFast<WListFast<pressure_t>>>());

    for (auto& list: values) {
        for (int i = 0; i < 32; i++)
            list.append(WListFast<WListFast<pressure_t>>());
    }

    for (auto& list1: values) {
        for (auto& list: list1) {
            for (int i = 0; i < 32; i++)
                list.append(WListFast<pressure_t>());
        }
    }

    for (auto& list2: values) {
        for (auto& list1: list2) {
            for (auto& list: list1) {
                for (int i = 0; i < 32; i++)
                    list.append(pressure_t((double)i));
            }
        }
    }

    auto result = WListFast<type>::writeMultiThread(writable, values, Scheduler::startNewTask);

    QCOMPARE(result, 0);
}

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
    constexpr auto max = 1000;
    QList<WTimer*> timers;
    bool callers[max];

    memset(callers, 0, sizeof(callers));

    for (int i = 0; i < max; i++) {
        auto func = [&callers, i]() {
            callers[i] = true;
        };

        auto timer = new WTimer(nullptr, func, (std::rand() % 100 + 100), false);

        timer->setSingleShot(true);
        timers.append(timer);
        timer->start();
    }

    QThread::sleep(2);

    for (int i = 0; i < max; i++) {
        if (!callers[i]) {
            WDebug(true, "At different:" << i);
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
            Scheduler::addTaskGeneric(Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, []{}, true)));
        }

        delete scheduler;
    }

    scheduler = nullptr;
}

void test_Scheduler::test_timers()
{
    delete scheduler;

    for (int i = 0; i < 500; i++) {
        scheduler = new Scheduler;

        bool call = false;
        auto *timer = new WTimer(nullptr, [&call] {
            call = true;
        }, 40, false);

        timer->setSingleShot(true);
        timer->start();

        QCOMPARE(call, false);

        QThread::msleep(50);

        QCOMPARE(call, true);
        QCOMPARE(timer->isActive(), false);

        delete scheduler;
        delete timer;
    }

    scheduler = nullptr;
}

QTEST_GUILESS_MAIN(test_Scheduler)

#include "test_Scheduler.moc"
