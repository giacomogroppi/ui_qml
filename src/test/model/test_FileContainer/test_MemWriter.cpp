#include <QtTest>
#include <utility>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "FileContainer/MemWritable.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTask.h"

class test_MemWriter : public QObject
{
Q_OBJECT

private slots:
    // operator copy
    void writeInteger();
    void writeMultipleInteger();

    void writeTwoZone();
    void writeBig();
};

class WritableTest final: public WritableAbstract
{
private:
    WByteArray result;
    size_t s = 0;
public:
    auto write (const void *data, size_t size)-> int final
    {
        result.append(static_cast<const char*>(data), size);
        this->s += size;
        return 0;
    }

    ~WritableTest() = default;

    [[nodiscard]] const char *data () const
    {
        return this->result.constData();
    }
};

void test_MemWriter::writeBig()
{
    for (int k = 0; k < 100; k++) {
        WByteArray tmp, result;
        MemWritable writable;

        for (int i = 0; i < 50000; i++) {
            const auto r = random() % 10000;
            void *mem = malloc(r);

            writable.write(mem, r);
            tmp.append(static_cast<char*>(mem), r);

            free(mem);
        }

        writable.merge([&](const void *d, size_t size) {
            result.append(static_cast<const char*>(d), size);
            return 0;
        });

        QCOMPARE(result.size(), tmp.size());
        QCOMPARE(result, tmp);
    }
}

void test_MemWriter::writeTwoZone()
{
    for (int k = 0; k < 1000; k++) {
        MemWritable writable;
        WByteArray original;
        WByteArray merged;
        const auto s = 4096;
        void *d = malloc (s * 10u);

        writable.write(d, 3000);
        original.append(static_cast<char*>(d), 3000u);

        writable.write(d, s - 3000 + 200);
        original.append(static_cast<char*>(d), s - 3000 + 200);

        writable.merge([&](const void *d, size_t size) {
            merged.append(static_cast<const char*>(d), size);
            return 0;
        });

        QCOMPARE(merged.size(), original.size());
        QCOMPARE(merged, original);

        free(d);
    }
}

void test_MemWriter::writeInteger()
{
    for (int k = 0; k < 1000; k++) {
        int tmp = 5;
        WritableTest writableTest;
        MemWritable writable;
        writable.write(&tmp, sizeof(tmp));

        writable.merge(writableTest);

        int valueRead;
        WCommonScript::WMemcpy(&valueRead, writableTest.data(), sizeof(int));
        QCOMPARE(tmp, valueRead);
    }
}

void test_MemWriter::writeMultipleInteger()
{
    for (int k = 0; k < 1000; k++) {
        WritableTest writableTest;
        MemWritable writable;
        std::vector<int> values;

        for (int i = 0; i < 500; i++) {
            const auto res = writable.write(&i, sizeof(i));
            QCOMPARE(0, res);
            QCOMPARE(writable.getCurrentSize(), sizeof(int) * (i + 1));
            values.push_back(i);
        }

        writable.merge(writableTest);

        for (int i = 0; i < 500; i++) {
            int valueRead;
            WCommonScript::WMemcpy(&valueRead, writableTest.data() + sizeof(int) * i, sizeof(int));
            QCOMPARE(values[i], valueRead);
        }
    }
}

QTEST_GUILESS_MAIN(test_MemWriter)

#include "test_MemWriter.moc"
