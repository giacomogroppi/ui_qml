#include <QtTest>
#include <utility>

#include "currenttitle/document.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "sheet/style_struct.h"
#include "file/Directory.h"
#include <QStandardPaths>
#include "touch/rubber/Rubber.h"
#include "Scheduler/WTaskAllocator.h"
#include "core/Allocators.h"

class test_Rubber : public QObject
{
Q_OBJECT

    UniquePtr<Scheduler> sched;

private slots:
    void init();
    void cleanup();

    void test();
};

void test_Rubber::init()
{
    static bool first = true;

    Allocators::init();

    if (first) {
        this->sched = std::make_unique<Scheduler>();
        Document::init();
        first = false;
    }
}

void test_Rubber::cleanup()
{
    Allocators::exit();
}

void test_Rubber::test()
{
    Rubber *rubber = new Rubber(nullptr);
    Document doc;

    rubber->setRubberTotal();
    doc.newPage(n_style::square);

    {
        SharedPtr<Stroke> stroke = SharedPtr<Stroke>(new StrokeNormal);

        for (int i = 0; i < 500; i++) {
            stroke->append(PointF(i, i), pressure_t(5.0));
        }
        doc.appendStroke(std::move(stroke));
    }

    {

    }

}

QTEST_GUILESS_MAIN(test_Rubber)

#include "test_Rubber.moc"
