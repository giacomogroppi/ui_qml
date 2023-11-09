#include <QtTest>

#include "core/WList.h"
#include "Scheduler/Scheduler.h"
#include "utils/WCommonScript.h"
#include "core/WListFast.h"
#include "touch/dataTouch/datastruct/utils_datastruct.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"

class test_WTask : public QObject
{
Q_OBJECT

    static constexpr auto numberOfTests = 1;
    Scheduler *scheduler = nullptr;

private slots:
    void init();

    void cleanup();

    void speedConstrutor();
};

void test_WTask::init()
{
    Allocators::init();
}

void test_WTask::cleanup()
{
    Allocators::exit();
}

void test_WTask::speedConstrutor()
{
    constexpr auto numberOfThreads = 8;
    constexpr auto value = 40'000;
    WList<WTaskDataPrivate*> get[numberOfThreads];
    WList<WTaskDataPrivate*> put[numberOfThreads];
    WList<int> results;

    WVector<std::thread*> threads;

    for (int i = 0 ; i < numberOfThreads; i++) {
        for (int j = 0; j < value; j++)
            get[i].append(new WTaskDataPrivate());
    }

    for (int i = 0; i < 8; i++) {
        const auto method = [&, i] () {
            auto now = std::chrono::system_clock::now();
            for ( ;get[i].size() != 0; ) {
                WTaskAllocator::put(get[i].takeFirst());
            }

            int delta = (std::chrono::system_clock::now() - now).count();
            results.append(delta);
        };

        threads.append(new std::thread(method));
    }

    threads.forAll(&std::thread::join);
    threads.forAll([] (auto *thread) {
        delete thread;
    });

    int sum = 0;
    for (auto &ref: results)
        sum += ref;
    WDebug(true, "Sum: " << sum);
}


QTEST_GUILESS_MAIN(test_WTask)

#include "test_WTask.moc"
