#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>

class test_Document : public QObject
{
Q_OBJECT

private slots:
    void testLoad();
};

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

    WByteArray data;

    {
        MemWritable writable;

        QCOMPARE(Document::write(writable, doc), 0);
        writable.merge([&] (const void *d, size_t size) -> int {
            data.append(static_cast<const char *>(d), size);
            return 0;
        });
    }

    {
        MemReadable readable (data.constData(), data.size());

        const auto [result, data] = Document::load(VersionFileController(), readable);

        QVERIFY(result == 0);
        QCOMPARE(data, doc);
    }

}

QTEST_MAIN(test_Document)

#include "test_Document.moc"
