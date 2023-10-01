#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>

class test_StrokeNormal : public QObject
{
Q_OBJECT

private slots:
    void testLoadWithNoStroke();
    void testLoadWith200Points();
};

void test_StrokeNormal::testLoadWithNoStroke()
{
    StrokeNormal stroke;
    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::WFileWrite);
        //QVERIFY(file.isValid());
        QCOMPARE(Stroke::write(writable, stroke), 0);
        writable.merge([&] (const void *d, size_t size) -> int {
            data.append(static_cast<const char *>(d), size);
            return 0;
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::WFileReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, data] = Stroke::loadPtr(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(*data, stroke);

        delete data;
    }
}

void test_StrokeNormal::testLoadWith200Points()
{
    StrokeNormal stroke;

    for (int i = 0;  i < 200; i++) {
        stroke.append(PointF{50, 50}, 20.0);
    }

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::WFileWrite);
        //QVERIFY(file.isValid());
        QCOMPARE(Stroke::write(writable, stroke), 0);
        writable.merge([&] (const void *d, size_t size) -> int {
            data.append(static_cast<const char *>(d), size);
            return 0;
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::WFileReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, data] = Stroke::loadPtr(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(*data, stroke);

        delete data;
    }
}

QTEST_GUILESS_MAIN(test_StrokeNormal)

#include "test_StrokeNormal.moc"
