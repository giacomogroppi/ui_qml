#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

#include "WQMLCanvasHandler.h"
#include "WQMLCanvasComponent.h"

class ControllerCanvas: public QObject {
    Q_OBJECT
private:
    QTimer *_timer;

    int _width;
    int _heigth;

    void wSetWidth(int newWidth);
    void wSetHeigth(int newHeigth);

#ifdef DEBUGINFO
    enum waitingFor {
        begin,
        update
    };

    /**
     * indicates the last function call
    */
    enum waitingFor _status;

#endif // DEBUGINFO

public:
    explicit ControllerCanvas(QObject *parent, std::function<const QPixmap &()> getImg);
    ~ControllerCanvas() = default;

    Q_PROPERTY(int heigthObject READ heigthObject NOTIFY heigthObjectChanged);
    int heigthObject() const;
    Q_SIGNAL void heigthObjectChanged();

    Q_PROPERTY(int widthObject READ widthObject NOTIFY widthObjectChanged);
    int widthObject() const;
    Q_SIGNAL void widthObjectChanged();

    static void registerDrawer(WQMLCanvasComponent *object);
    static void registerHangler(WQMLCanvasHandler *object);
private:
    std::function<const QPixmap &()> _getImg;
public slots:
    void refresh();
    void touchBegin(const QPointF &point, double pressure);
    void touchUpdate(const QPointF &point, double pressure);
    void touchEnd(const QPointF &point, double pressure);

private slots:
    void endTimer();

protected:
    bool event(QEvent *event) override;

signals:
    void onTouchBegin(const QPointF &point, double pressure);
    void onTouchUpdate(const QPointF &point, double pressure);
    void onTouchEnd(const QPointF &point, double pressure);

    /**
     * Il parametro newPosition indica la nuova posizione in pixel
    */
    void positionChanged(const QPointF &newPosition);
};
