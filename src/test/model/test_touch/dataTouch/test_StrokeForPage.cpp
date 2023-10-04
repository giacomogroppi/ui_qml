#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>

class test_StrokeForPage : public QObject
{
Q_OBJECT

private slots:
    void testLoadWithNoPoints();
    void testLoadWith200Points();
};

void test_StrokeForPage::testLoadWithNoPoints()
{
    StrokeForPage stroke;
    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::Write);
        //QVERIFY(file.isValid());
        QCOMPARE(StrokeForPage::write(writable, stroke), 0);
        writable.merge([&] (const void *d, size_t size) -> int {
            data.append(static_cast<const char *>(d), size);
            return 0;
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::ReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, strokeLoaded] = StrokeForPage::load(VersionFileController(), readable);

        QCOMPARE(readable.getSeek(), readable.getMax());
        QVERIFY(result == 0);
        QCOMPARE(strokeLoaded, stroke);
    }
}

void test_StrokeForPage::testLoadWith200Points()
{
    return;
    StrokeForPage stroke;

    for (int i = 0;  i < 200; i++) {
        stroke.append(PointF{50, 50}, 20.0);
    }

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::Write);
        //QVERIFY(file.isValid());
        QCOMPARE(StrokeForPage::write(writable, stroke), 0);
        writable.merge([&] (const void *d, size_t size) -> int {
            data.append(static_cast<const char *>(d), size);
            return 0;
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::ReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, resultLoad] = StrokeForPage::load(VersionFileController(), readable);

        QCOMPARE(readable.getSeek(), readable.getMax());
        QVERIFY(result == 0);
        QCOMPARE(resultLoad, stroke);
    }
}

QTEST_GUILESS_MAIN(test_StrokeForPage)

#include "test_StrokeForPage.moc"
