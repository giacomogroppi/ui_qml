#include <QtTest>

#include "core/WListFast.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/stroke/Stroke.h"
#include "touch/dataTouch/stroke/StrokeNormal.h"
#include "core/PointF.h"

class ObjectTesting: public WObject {
public:
    ObjectTesting()
        : WObject(nullptr)
    {

    }

    void launchSignals() {
        W_EMIT_0(signalsEmpty);
    }

    void launchSignal1() {
        W_EMIT_1(signals1, PointF(500., 500.));
    }

    W_EMITTABLE_0(signalsEmpty);
    W_EMITTABLE_1(signals1, PointF, point);
};

class test_WObject : public QObject
{
    Q_OBJECT

private slots:
    void test_launch_signal0 ();
    void test_launch_signal1 ();
};



void test_WObject::test_launch_signal0()
{
    ObjectTesting *tmp = new ObjectTesting;
    bool call = false;

    w_connect_lister(tmp, signalsEmpty, [&call]() {
        call = true;
    });

    tmp->launchSignals();

    QVERIFY(call);
}

void test_WObject::test_launch_signal1()
{
    ObjectTesting *tmp = new ObjectTesting;
    bool call = false;
    PointF p;

    w_connect_lister(tmp, signals1, [&](const PointF &point) {
        call = true;
        p = point;
    });

    tmp->launchSignal1();

    QVERIFY(call);
    QCOMPARE(p, PointF(500., 500.));
}


QTEST_MAIN(test_WObject)

#include "test_WObject.moc"
