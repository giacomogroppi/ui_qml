#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>
#include <QAbstractListModel>

#include "WQMLCanvasHandler.h"
#include "WQMLCanvasComponent.h"
#include "touch/UpdateEvent.h"

class ControllerCanvas: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double positionX READ positionX WRITE setPositionX NOTIFY positionXChanged);
    Q_PROPERTY(double positionY READ positionY WRITE setPositionY NOTIFY positionYChanged);
    Q_PROPERTY(int heigthObject READ getHeigthObject NOTIFY onHeigthObjectChanged);
    Q_PROPERTY(int widthObject READ getWidthObject NOTIFY onWidthObjectChanged);
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
    explicit ControllerCanvas(QObject *parent = nullptr);
    ~ControllerCanvas() = default;

    int getHeigthObject() const;
    int getWidthObject() const;

    double positionX() const;
    double positionY() const;

    void setPositionX(double newPosition);
    void setPositionY(double newPosition);

    void setFunc(std::function<void (QPainter &painter, double width)> getImg);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

    static void registerDrawer(WQMLCanvasComponentStroke *object);
    static void registerHangler(WQMLCanvasHandler *object);
private:
    double _positionX;
    double _positionY;
    std::function<void (QPainter &painter, double width)> _getImg;

    static void callUpdate(const UpdateEvent& event);

public slots:
    void refresh(const UpdateEvent& event);
    void sizeHasChanged(const QSizeF &size);
    void touchBegin(const QPointF &point, double pressure);
    void touchUpdate(const QPointF &point, double pressure);
    void touchEnd(const QPointF &point, double pressure);

    void duplicateData(int row);
    void removeData(int row);

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

    void onWidthObjectChanged();
    void onHeigthObjectChanged();
};
