#include <QtTest>
#include <memory>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"
#include <QStandardPaths>

class test_Page : public QObject
{
Q_OBJECT

    UniquePtr<Scheduler> scheduler;

private slots:
    void init();
    void cleanup();

    void testLoadWithNoStroke();
    void testLoadWith1Stroke();
    void testLoadWith200Stroke();
};

void test_Page::init()
{
    static bool first = true;

    Allocators::init();

    if (first == true) {
        Document::init();
        first = false;

        scheduler = std::make_unique<Scheduler>();
    }
}

void test_Page::cleanup()
{
    Allocators::exit();
}

void test_Page::testLoadWithNoStroke()
{
    Page doc(1, n_style::square);
    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::Write);
        //QVERIFY(file.isValid());
        QCOMPARE(Page::write(writable, doc), 0);
        writable.merge([&] (const void *d, size_t size) -> Error {
            data.append(static_cast<const char *>(d), size);
            return Error::makeOk();
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::ReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, d] = Page::load(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(d, doc);
    }
}

void test_Page::testLoadWith1Stroke()
{
    Page doc(1, n_style::square);
    StrokeNormal stroke;

    for (int i = 0; i < 300; i++)
        stroke.append(PointF(500, 400), pressure_t(40.));

    for (int i = 0; i < 1; i++)
        doc.append(stroke.clone());

    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::Write);
        //QVERIFY(file.isValid());
        QCOMPARE(Page::write(writable, doc), 0);
        writable.merge([&] (const void *d, size_t size) {
            data.append(static_cast<const char *>(d), size);
            return Error::makeOk();
        });
        WDebug(true, "prova" << data.size() << writable.getCurrentSize());
    }

    {
        MemReadable readable (data.constData(), data.size());

        const auto [result, page] = Page::load(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(readable.getSeek(), readable.getMax());
        QCOMPARE(page, doc);
    }
}

void test_Page::testLoadWith200Stroke()
{
    Page doc(1, n_style::square);
    StrokeNormal stroke;

    for (int i = 0; i < 500; i++)
        stroke.append(PointF(500, 400), pressure_t(40.));

    for (int i = 0; i < 200; i++)
        doc.append(stroke.clone());

    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray data;

    {
        MemWritable writable;
        //WFile file (tmp / "prova.txt", WFile::Write);
        //QVERIFY(file.isValid());
        QCOMPARE(Page::write(writable, doc), 0);
        writable.merge([&] (const void *d, size_t size) {
            data.append(static_cast<const char *>(d), size);
            return Error::makeOk();
        });
    }

    {
        MemReadable readable (data.constData(), data.size());
        //WFile file (tmp / "prova.txt", WFile::ReadOnly);
        //QVERIFY(file.isValid());
        const auto [result, data] = Page::load(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(data, doc);
    }
}

QTEST_GUILESS_MAIN(test_Page)

#include "test_Page.moc"
