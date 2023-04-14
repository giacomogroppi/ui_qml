#include <QtTest>

#include "core/WList.h"
#include "utils/WCommonScript.h"

class test_WList : public QObject
{
Q_OBJECT

private slots:
    void test_copy ();
    void append_2Argument();
    void operatorCopy();
};

void test_WList::append_2Argument()
{
    WList<int> c;
    c.append(4);

    QCOMPARE_EQ(4, c.first());
    QCOMPARE_EQ(4, c.last());

    QCOMPARE_EQ(1, c.length());
    QCOMPARE_EQ(4, *c.get_first());

    QCOMPARE_EQ(0, c.length());
}

void test_WList::test_copy()
{
    WList<int> c;

    c.append(4);
    c.append(6);

    WList<int> c2(c);

    QCOMPARE_EQ(2, c.size());
    QCOMPARE_EQ(2, c2.size());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

void test_WList::operatorCopy()
{
    WList<int> c;

    c.append(4);
    c.append(6);

    WList<int> c2 = c;

    QCOMPARE_EQ(c2.size(), c.size());

    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());

    c.clear();

    QCOMPARE_EQ(2, c2.size());
    QCOMPARE_EQ(4, c2.first());
    QCOMPARE_EQ(6, c2.last());
}

QTEST_MAIN(test_WList)

#include "test_WList.moc"
