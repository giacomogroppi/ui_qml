#include "ControllerPageCounter.h"
#include <QDebug>

ControllerPageCounter::ControllerPageCounter(QObject *parent)
    : QObject (parent),
      _page(1)
{
}

void ControllerPageCounter::pageUp()
{
    qWarning() << "ControllPageCounter::pageUp() not implemented";
}

void ControllerPageCounter::pageDown()
{
    qWarning() << "ControllerPageCounter::pageDown() not implemented";
}

int ControllerPageCounter::page() const
{
    return this->_page;
}

void ControllerPageCounter::setPage(int index)
{
    this->_page = index;
    emit pageChanged();
}

int ControllerPageCounter::numberOfPage() const
{
    return 23;
}
