#include <QtTest>

#include "core/WList.h"
#include "Scheduler/Scheduler.h"
#include "utils/WCommonScript.h"
#include "core/WListFast.h"
#include "touch/dataTouch/datastruct/utils_datastruct.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"

class test_Scheduler : public QObject
{
Q_OBJECT

    static constexpr auto numberOfTests = 1;
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
    using namespace std;
    WListFast<WVector<pressure_t>> tmp;
    class WritableTest: public WritableAbstract {
    public:
        Error write(const void*, size_t) final { return Error::makeOk(); }
    };

    WritableTest writable;

    for (decltype(thread::hardware_concurrency()) i = 0; i < thread::hardware_concurrency(); i++) {
        tmp.append(WVector<pressure_t>(512));
    }

    for (auto& l: tmp) {
        for (int i = 0; i < 512; i++) {
            l.append(pressure_t((double) i));
        }
    }

    auto result = WListFast<WVector<pressure_t>>::writeMultiThread(writable, tmp, Scheduler::startNewTask);
    QCOMPARE(result, 0);
}

void test_Scheduler::test_deadlocks2()
{
    MemWritable writable;
    WListFast<Scheduler::Ptr<WTask>> list;

    for (int i = 0; i < 40; i++) {
        auto task = Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, WTask::NotDeleteLater, [] {
            WListFast<Scheduler::Ptr<WTask>> tmp;

            for (int j = 0; j < 40; j++) {
                tmp.append(Scheduler::Ptr<WTaskFunction>::make(nullptr, WTask::NotDeleteLater, std::bind(&QThread::msleep, 2)));
            }

            tmp.forAll(&Scheduler::addTaskGeneric);

            for (auto& r: tmp) {
                r->join();
                r.release();
            }
        }));

        list.append(std::move(task));
    }

    list.forAll(&Scheduler::addTaskGeneric);

    for (auto& t: list) {
        t->join();
        t.release();
    }
}

void test_Scheduler::test_deadlocks1()
{
    MemWritable writable;
    using type = WListFast<WListFast<WVector<pressure_t>>>;
    WListFast<type> values;

    for (int i = 0; i < 32; i++)
        values.append(WListFast<WListFast<WVector<pressure_t>>>());

    for (auto& list: values) {
        for (int i = 0; i < 32; i++)
            list.append(WListFast<WVector<pressure_t>>());
    }

    for (auto& list1: values) {
        for (auto& list: list1) {
            for (int i = 0; i < 32; i++)
                list.append(WVector<pressure_t>());
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
    Allocators::init();

    W_ASSERT(scheduler == nullptr);
    scheduler = new Scheduler;
}

void test_Scheduler::cleanup()
{
    delete scheduler;
    scheduler = nullptr;

    Allocators::exit();
}

void test_Scheduler::test_timersConcurrency()
{
    constexpr auto max = 1000;
    QList<WTimer*> timers;
    std::atomic_bool callers[max];

    for (auto& ref: callers) ref = false;

    for (int i = 0; i < max; i++) {
        auto func = [&callers, i]() {
            callers[i] = true;
        };

        auto timer = new WTimer(nullptr, func, (std::rand() % 100 + 100), (~WTimer::Flag::onMainThread) | (WTimer::Flag::singleShot));

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

    for (auto& timer : timers) {
        WDebug(true, "Before delete" << timer);
        delete timer;
    }
}

void test_Scheduler::test_destructor()
{
    delete scheduler;

    for (int i = 0; i < 5000; i++) {
        scheduler = new Scheduler;

        for (int j = 0; j < 500; j++) {
            Scheduler::addTaskGeneric(Scheduler::Ptr<WTask>(new WTaskFunction(nullptr, WTask::NotDeleteLater, []{})));
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
        }, 40, (~WTimer::Flag::onMainThread) | WTimer::Flag::singleShot);

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
