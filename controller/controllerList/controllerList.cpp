#include "controllerList.h"
#include <QDebug>

controllerList::controllerList(QObject *parent)
    : QObject(parent)
{
    _list << ListElement("Elettronica lez(1)", 291122);
    _list << ListElement("Elettronica lez(2)", 281122);
    qDebug() << "Constractor call";
}
