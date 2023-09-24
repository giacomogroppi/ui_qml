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
#include "file/Directory.h"

class test_Directory : public QObject
{
Q_OBJECT

    static constexpr auto path = "/tmp/writernote";
    static constexpr auto nameTmp = "testing";

private slots:
    void init();

    void loadFileInFolderEmpty();
    void loadFileInFolderWith2Items();

    void cleanup();

    auto getPath(WString name) -> std::filesystem::path
    {
        return std::filesystem::path(path) / name.toStdString();
    }

    auto createFile(std::filesystem::path path) -> void
    {
        FILE *fp = fopen (path.c_str(), "w");
        W_ASSERT(fp);
        fprintf(fp, "%d", 6);
        fclose(fp);
    }

private:
    std::error_code error;
};

void test_Directory::loadFileInFolderEmpty()
{
    std::filesystem::create_directories(getPath(path));
    std::filesystem::create_directories(getPath(path) / nameTmp);

    Directory directory (getPath(path) / nameTmp);

    const auto list = directory.getFiles();

    QCOMPARE(list.size(), 0);
}

void test_Directory::loadFileInFolderWith2Items()
{
    std::filesystem::create_directories(getPath(path) / nameTmp, error);
    createFile((getPath(path) / nameTmp / "prova_file.txt").c_str());
    createFile((getPath(path) / nameTmp / "prova_file2.txt").c_str());

    Directory dir(getPath(path) / nameTmp);

    QCOMPARE(dir.getFiles().size(), 2);
}

void test_Directory::init()
{
    std::filesystem::remove_all(path);
    std::filesystem::create_directories(path);
}

void test_Directory::cleanup()
{
    std::filesystem::remove_all(path);
    std::filesystem::remove_all(nameTmp);
}

QTEST_GUILESS_MAIN(test_Directory)

#include "test_Directory.moc"
