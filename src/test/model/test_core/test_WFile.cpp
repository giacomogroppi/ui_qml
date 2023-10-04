#include <QtTest>

#include "utils/WCommonScript.h"
#include "core/RectF.h"
#include <QRectF>
#include "core/ExactNumber/ExactNumber.h"
#include "core/WFile.h"
#include <QStandardPaths>

class test_WFile : public QObject
{
    Q_OBJECT

    static constexpr auto fileName = "writernote_test.txt";

private slots:
    void test();
};

void test_WFile::test()
{
    const auto l = std::pow(2, 20);
    const auto writable = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    const auto path = WPath(writable) / fileName;
    std::vector<int> vec;

    {
        WFile file (path, WFile::Write);
        QVERIFY(file.isValid());

        for (int i = 0; i < l; i ++) {
            file.write(i);
            vec.push_back(i);
        }
    }

    {
        WFile file (path, WFile::ReadOnly);
        QVERIFY(file.isValid());
        ReadableAbstract &readable = file;

        for (const int value: std::as_const(vec)) {
            int read;
            QCOMPARE(readable.read(read), 0);
            QCOMPARE(read, value);
        }
    }
}

QTEST_GUILESS_MAIN(test_WFile)

#include "test_WFile.moc"
