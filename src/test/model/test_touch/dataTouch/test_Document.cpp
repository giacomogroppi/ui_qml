#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"

class test_Document : public QObject
{
Q_OBJECT

    UniquePtr<Scheduler> scheduler;

private slots:
    void init();
    void cleanup();

    void testLoad();
    void test200Pages();
};

void test_Document::init()
{
    Allocators::init();
    static bool first = true;
    if (first) {
        scheduler = std::make_unique<Scheduler>();
        Document::init();

        first = false;
    }
}

void test_Document::cleanup()
{
    Allocators::exit();
}

void test_Document::test200Pages()
{
    Document doc;

    for (int i = 0; i < 200; i++) {
        doc.newPage(n_style::square);

        for (int k = 0; k < 400; k++) {
            auto *stroke = new StrokeNormal();

            for (int j = 0; j < 500; j++) {
                stroke->append(PointF(i, j), pressure_t((double) k));
            }

            doc.appendStroke(SharedPtr<Stroke>(stroke));
        }
    }

    MemWritable writable;
    MemReadable readable;
    WByteArray data;

    {
        QCOMPARE(Document::write(writable, doc), 0);
        writable.merge([&](const void *d, size_t size) {
            data.append(static_cast<const char*>(d), size);
            return Error::makeOk();
        });
    }

    {
        readable.setData(data.constData(), data.size());
        auto [result, d] = Document::load(VersionFileController(), readable);
        QCOMPARE(result, 0);
        QCOMPARE(d, doc);
    }
}

void test_Document::testLoad()
{
    Document doc;
    StrokeNormal stroke;

    doc.newPage(n_style::square);

    for (int i = 0; i < 500; i++)
        stroke.append(PointF(500, 400), pressure_t(40.));

    for (int i = 0; i < 500; i++)
        doc.appendStroke(stroke.clone());

    const WPath tmp = WPath(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) / "writernote";

    (void) Directory::createDir(tmp);

    WByteArray raw;

    {
        MemWritable writable;

        QCOMPARE(Document::write(writable, doc), 0);
        writable.merge([&] (const void *d, size_t size) -> Error {
            raw.append(static_cast<const char *>(d), size);
            return Error::makeOk();
        });
    }

    {
        MemReadable readable (raw.constData(), raw.size());

        const auto [result, data] = Document::load(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(data, doc);
    }

}

QTEST_MAIN(test_Document)

#include "test_Document.moc"
