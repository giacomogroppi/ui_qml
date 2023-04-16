#include <QtTest>

#include "core/WPair.h"
#include "utils/WCommonScript.h"

class test_WPair : public QObject
{
    Q_OBJECT

private slots:
    void test_copy ();
};

void test_WPair::test_copy()
{
    WPair<QString, int> t1;

    t1.setKey(QString("testing_1"));
    t1.setValue(4);

    WPair<QString, int> t2("testing_1", 4);

    QCOMPARE_EQ(t1, t2);
}

QTEST_MAIN(test_WPair)

#include "test_WPair.moc"
