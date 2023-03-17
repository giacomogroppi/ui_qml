#pragma once

#include <QQuickPaintedItem>
#include <QQuickItem>

class WQMLItemListComponent : public QQuickPaintedItem
{
    Q_OBJECT
    //QML_ELEMENT
private:
    int _index;
public:
    WQMLItemListComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    Q_PROPERTY(int indexObject READ indexObject WRITE setIndexObject NOTIFY indexChangedObject)
    int indexObject();
    void setIndexObject(int index);
    Q_SIGNAL void indexChangedObject();

public slots:
    void needRefresh();
};


