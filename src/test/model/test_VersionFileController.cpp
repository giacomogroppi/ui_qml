#include <QtTest>
#include <utility>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "FileContainer/MemWritable.h"
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTask.h"
#include "file/FileManager.h"
#include "currenttitle/document.h"

class test_VersionFileController : public QObject
{
Q_OBJECT

private slots:
    void test();
};

void test_VersionFileController::test()
{
    MemWritable writable;
    MemReadable readable;
    WByteArray result;
    VersionFileController versionController;

    QCOMPARE(VersionFileController::write(writable), 0);

    writable.merge([&](const void *d, size_t size) {
        result.append(static_cast<const char*>(d), size);
        return Error::makeOk();
    });

    readable.setData(result.constData(), result.size());

    auto r = VersionFileController::load(readable);

    QCOMPARE(r.first, 0);
    QCOMPARE(readable.getSeek(), readable.getMax());
    QCOMPARE(r.second, versionController);
}

QTEST_GUILESS_MAIN(test_VersionFileController)

#include "test_VersionFileController.moc"
