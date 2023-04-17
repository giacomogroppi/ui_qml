#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

#include "WQMLCanvasHandler.h"
#include "WQMLCanvasComponent.h"

class ControllerCanvas: public QObject {
    Q_OBJECT
    Q_PROPERTY(double positionX READ positionX WRITE setPositionX NOTIFY positionXChanged);
    Q_PROPERTY(double positionY READ positionY WRITE setPositionY NOTIFY positionYChanged);
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
    explicit ControllerCanvas(QObject *parent, std::function<void (QPainter &painter, double width)> getImg);
    ~ControllerCanvas() = default;

    Q_PROPERTY(int heigthObject READ heigthObject NOTIFY heigthObjectChanged);
    int heigthObject() const;
    Q_SIGNAL void heigthObjectChanged();

    Q_PROPERTY(int widthObject READ widthObject NOTIFY widthObjectChanged);
    int widthObject() const;
    Q_SIGNAL void widthObjectChanged();

    double positionX() const;
    double positionY() const;

    void setPositionX(double newPosition);
    void setPositionY(double newPosition);

    static void registerDrawer(WQMLCanvasComponent *object);
    static void registerHangler(WQMLCanvasHandler *object);
private:
    double _positionX;
    double _positionY;
    std::function<void (QPainter &painter, double width)> _getImg;

    static void callUpdate(int page);
    static void callUpdate(int pageMin, int pageMax, bool all);

public slots:
    void refresh(int page);
    void sizeHasChanged(const QSizeF &size);
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
    void positionXChanged();
    void positionYChanged();
    /**
     * Il parametro newPosition indica la nuova posizione in pixel
    */
    void positionChanged(const QPointF &newPosition);
};
