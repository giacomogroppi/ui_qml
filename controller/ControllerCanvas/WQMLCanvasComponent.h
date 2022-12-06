#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    QML_NAMED_ELEMENT(CanvasController)

    QTimer *_timer;

    int _width;
    int _heigth;

    bool _need_refresh;
public:
    WQMLCanvasComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    Q_PROPERTY(bool rightAligned READ isRightAligned WRITE setRightAligned NOTIFY rightAlignedChanged)
    bool isRightAligned() const;
    void setRightAligned (bool rightAligned) {
        rightAligned = rightAligned;
    };

    Q_PROPERTY(int heigthObject
               READ heigthObject
               NOTIFY heigthObjectChanged);

    int heigthObject();
    Q_SIGNAL void heigthObjectChanged();

    Q_PROPERTY(int widthObject READ widthObject NOTIFY widthObjectChanged);
    int widthObject() const;
    Q_SIGNAL void widthObjectChanged();

    Q_PROPERTY(bool needRefresh READ needRefresh NOTIFY needRefreshChanged);
    bool needRefresh() const;
    void setNeedRefresh();
    Q_SIGNAL void needRefreshChanged();

private:
    bool rightAligned;

signals:
    void rightAlignedChanged();
private slots:
    void endTimer();
};
