#include "ControllerPageCounter.h"

ControllerPageCounter::ControllerPageCounter(QObject *parent)
    : QObject (parent),
      _page(1)
{
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
