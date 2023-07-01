#include <QtTest>
#include <utility>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "FileContainer/MemWritable.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTask.h"

class test_MemReader : public QObject
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
    size_t size = 0;
public:
    auto write (const void *data, size_t s) -> int final
    {
        W_ASSERT(this->_data == nullptr);
        this->_data = (char *) malloc (s);
        this->size = s;
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

    size_t getSize() const
    {
        return this->size;
    }
};

void test_MemReader::writeInteger()
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

void test_MemReader::writeMultipleInteger()
{
    WritableTest writableTest;
    MemWritable writable;
    MemReadable readable;
    std::vector<int> values;

    for (int i = 0; i < 500; i++) {
        const auto res = writable.write(&i, sizeof(i));
        QCOMPARE(0, res);
        values.push_back(i);
    }

    QVERIFY(writable.merge(writableTest) == 0);
    readable.setData(writableTest.data(), writableTest.getSize());

    for (int &valueShouldRead: values) {
        int valueRead;
        const auto result = readable.read(&valueRead, sizeof(valueRead));
        QCOMPARE(0, result);

        QCOMPARE(valueShouldRead, valueRead);
    }
}

QTEST_GUILESS_MAIN(test_MemReader)

#include "test_MemReader.moc"
