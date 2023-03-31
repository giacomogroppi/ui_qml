#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

#include "WQMLCanvasComponent.h"

class ControllerCanvas: public QObject {
    Q_OBJECT
private:
    WQMLCanvasComponent *_component;
    QTimer *_timer;

    int _width;
    int _heigth;

    void wSetWidth(int newWidth);
    void wSetHeigth(int newHeigth);

#ifdef DEBUGINFO
    enum waitingFor {
        begin,
        update,
        end
    };

    /**
     * indicates the last function call
    */
    enum waitingFor _status;

#endif // DEBUGINFO

public:
    explicit ControllerCanvas(QObject *parent = nullptr);
    ~ControllerCanvas() = default;

    Q_PROPERTY(int heigthObject READ heigthObject NOTIFY heigthObjectChanged);
    int heigthObject();
    Q_SIGNAL void heigthObjectChanged();

    Q_PROPERTY(int widthObject READ widthObject NOTIFY widthObjectChanged);
    int widthObject() const;
    Q_SIGNAL void widthObjectChanged();

public slots:
    void refresh();
    void touchBegin(double x, double y, double pressure);
    void touchUpdate(double x, double y, double pressure);
    void touchEnd(double x, double y, double pressure);

private slots:
    void endTimer();

protected:
    bool event(QEvent *event) override;


signals:
    void onTouchBegin(const QPointF &point, double pressure);
    void onTouchUpdate(const QPointF &point, double pressure);
    void onTouchEnd(const QPointF &point, double pressure);
};
