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
};

class WritableTest final: public WritableAbstract
{
    char *_data = nullptr;
    size_t size;
public:
    auto write (const void *data, size_t s)-> int
    {
        W_ASSERT(this->_data == nullptr);
        this->_data = (char *) malloc (s);
        WCommonScript::WMemcpy(_data, data, s);

        return 0;
    }

    ~WritableTest()
    {
        free(_data);
    }

    const char *data () const
    {
        return this->_data;
    }
};

void test_MemWriter::writeInteger()
{
    int tmp = 5;
    WritableTest writableTest;
    MemWritable writable;
    writable.write(&tmp, sizeof(tmp));

    writable.merge(writableTest);

    int valueRead;
    WCommonScript::WMemcpy(&valueRead, writableTest.data(), sizeof(int));
    QCOMPARE(tmp, valueRead);
}

void test_MemWriter::writeMultipleInteger()
{
    WritableTest writableTest;
    MemWritable writable;
    std::vector<int> values;

    for (int i = 0; i < 500; i++) {
        const auto res = writable.write(&i, sizeof(i));
        QCOMPARE(0, res);
        values.push_back(i);
    }

    writable.merge(writableTest);

    for (int i = 0; i < 500; i++) {
        int valueRead;
        WCommonScript::WMemcpy(&valueRead, writableTest.data() + sizeof(int) * i, sizeof(int));
        QCOMPARE(values[i], valueRead);
    }
}

QTEST_GUILESS_MAIN(test_MemWriter)

#include "test_MemWriter.moc"
