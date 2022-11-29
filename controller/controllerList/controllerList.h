#pragma once

#include <qqml.h>
#include <QDebug>
#include <QObject>
#include <QList>

struct ListElement{
    ListElement(const QString &name, int giorno)
    {
        _name = name;
        _giorno = giorno;
    }
    QString _name;
    int _giorno;
};

class controllerList: public QObject
{
    Q_OBJECT
private:
    QList<ListElement> _list;
public:
    controllerList(QObject *parent = nullptr);
    ~controllerList() = default;

    Q_PROPERTY(int numPage READ numPage NOTIFY numPageChanged)
    int numPage() const
    {
        qDebug() << "Num page call";
        Q_ASSERT(_list.length() == 2);
        return _list.length();
    };
    Q_SIGNAL void numPageChanged();

    Q_PROPERTY(QString at(int) READ at(int) NOTIFY atChanged)
    QString at(int index) const { return _list.at(index)._name; };
    Q_SIGNAL void atChanged();
};
