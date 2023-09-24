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

class test_FileManager : public QObject
{
Q_OBJECT

    static constexpr auto path = "/tmp/writernote";
    static constexpr auto nameTmp = "prova";

private slots:
    void init();
    void loadEmptyDirectory();
    void loadDirectoryWithFiles();

    void cleanup();
};

void createFile (std::filesystem::path path)
{
    FILE *fp = fopen (path.c_str(), "w");

    W_ASSERT(fp != nullptr);

    for (int i = 0; i < 50; i++)
        fprintf(fp, "%d", 6);

    fclose(fp);
}

void test_FileManager::cleanup()
{
    std::filesystem::remove_all(path);
}

void test_FileManager::loadDirectoryWithFiles()
{
    std::filesystem::create_directories(path);

    std::filesystem::create_directories(std::filesystem::path(path) / nameTmp);

    createFile(std::filesystem::path(path) / nameTmp / "testing.txt");

    FileManager manager (nullptr, path, true);

    QCOMPARE(manager.getDirectory().size(), 1);
    QCOMPARE(manager.getCurrentFiles().size(), 1);
}

void test_FileManager::loadEmptyDirectory()
{
    return;
    {
        FileManager manager(nullptr, path, true);
        QCOMPARE(manager.getDirectory().size(), 0);
        QCOMPARE(manager.getCurrentFiles().size(), 0);
    }
}

void test_FileManager::init()
{
    std::error_code error;
    std::filesystem::remove_all(path, error);
}

QTEST_GUILESS_MAIN(test_FileManager)

#include "test_FileManager.moc"
