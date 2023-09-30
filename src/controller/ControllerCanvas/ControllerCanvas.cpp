#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include "WQMLCanvasHandler.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/page/Page.h"
#include "controller/Controller.h"
#include <QVector>


static WQMLCanvasHandler *handler = nullptr;
static ControllerCanvas *controllerCanvas = nullptr;
static QList<WQMLCanvasComponentPage *> drawerPage;
static WQMLCanvasComponentStroke *drawerStroke;

bool init = false;

ControllerCanvas::ControllerCanvas(QObject *parent)
    : QAbstractListModel(parent)
    , _width(Page::getWidth())
    , _heigth(Page::getHeight())
    , _status(waitingFor::begin)
    , _positionX(0.)
    , _positionY(0.)
{
    Q_ASSERT(init == false);
    init = true;

    controllerCanvas = this;
    //Controller::registerControllerCanvas(this);

    qDebug() << "ControllerCanvas::ControllerCanvas call";
}

bool ControllerCanvas::event(QEvent *event)
{
    //qDebug() << event->type();
    return QObject::event(event);
}

void ControllerCanvas::wSetWidth(int newWidth)
{
    this->_width = newWidth;
    emit onWidthObjectChanged();
}

void ControllerCanvas::wSetHeigth(int newHeigth)
{
    this->_heigth = newHeigth;
    emit onHeigthObjectChanged();
}

int ControllerCanvas::getHeigthObject() const
{
    return this->_heigth;
}

int ControllerCanvas::getWidthObject() const
{
    return this->_width;
}

double ControllerCanvas::positionX() const
{
    return this->_positionX;
}

double ControllerCanvas::positionY() const
{
    return this->_positionY;
}

void ControllerCanvas::setPositionX(double newPosition)
{
    W_ASSERT(newPosition >= 0.);

    if (newPosition != this->_positionX) {
        _positionX = newPosition;
        WDebug(true, "Call");
        emit this->positionXChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::setPositionY(double newPosition)
{
    W_ASSERT(newPosition >= 0.);

    if (newPosition != this->_positionY) {
        _positionY = newPosition;
        WDebug(true, "call");
        emit this->positionYChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::setFunc(std::function<void (QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> updateFlag)> getImg)
{
    this->_getImg = std::move(getImg);
}

int ControllerCanvas::rowCount(const QModelIndex &parent) const
{
    qDebug() << "ControllerCanvas::rowCount";
    if (parent.isValid())
        return 0;

    return 2;
}

// this function should not be call from qml
QVariant ControllerCanvas::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    // this function should not be call
    return QVariant();
}

// this function should not be call from qml
QHash<int, QByteArray> ControllerCanvas::roleNames() const
{
    static QHash<int, QByteArray> mapping {
    };

    return mapping;
}

// this function should not be call from qml
void ControllerCanvas::duplicateData(int row)
{
    /*
    if (row < 0 || row >= drawer.size())
        return;

    beginInsertRows(QModelIndex(), row + 1, row + 1);
    endInsertRows();
    */
}

// this function should not be call from qml
void ControllerCanvas::removeData(int row)
{
    /*
    if (row < 0 || row >= drawer.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    */
}

void ControllerCanvas::registerDrawerStroke(WQMLCanvasComponentStroke *object)
{
    W_ASSERT(object != nullptr);
    W_ASSERT(controllerCanvas != nullptr);
    W_ASSERT(drawerStroke == nullptr);

    drawerStroke = object;

    QObject::connect(object, &WQMLCanvasComponentStroke::onXPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(object->xPosition(), 0.));
    });

    QObject::connect(object, &WQMLCanvasComponentStroke::onYPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(0., object->yPosition()));
    });
    object->setFunc(controllerCanvas->_getImg);
}

void ControllerCanvas::unregisterDrawerStroke(WQMLCanvasComponentStroke *object)
{
    W_ASSERT(object != nullptr);
    drawerStroke = nullptr;
}

void ControllerCanvas::registerDrawerPage(WQMLCanvasComponentPage *object)
{
    W_ASSERT(object != nullptr);
    W_ASSERT(controllerCanvas != nullptr);

    drawerPage.append(object);

    QObject::connect(object, &WQMLCanvasComponentPage::onXPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(object->xPosition(), 0.));
    });

    QObject::connect(object, &WQMLCanvasComponentPage::onYPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(0., object->yPosition()));
    });
    object->setFunc(controllerCanvas->_getImg);

    object->regFinishDraw([]() {
        if (controllerCanvas->_isWaitingForDrawInPage) {
            if (controllerCanvas->eventWaiting & UpdateEvent::stroke) drawerStroke->callUpdate();
            // TODO: update other drawer in case

            controllerCanvas->_isWaitingForDrawInPage = false;
        }
    });
}

void ControllerCanvas::unregisterDrawerPage(WQMLCanvasComponentPage *object)
{
    W_ASSERT(object != nullptr);
    drawerPage.remove(drawerPage.indexOf(object));
}

void ControllerCanvas::callUpdate(int page)
{
    // TODO: da mettere a posto
    W_ASSERT(page == -1 || (page >= 0 && page < drawerPage.size()));
    if (page == -1) {
        for (auto &d : drawerPage) {
            d->callUpdate(page);
        }
    } else {
        drawerPage[page]->callUpdate(page);
    }
}

void ControllerCanvas::callUpdate(const UpdateEvent& event)
{
    if (event & (UpdateEvent::page | UpdateEvent::sheet)) {
        if (event.isAll()) {
            ControllerCanvas::callUpdate(-1);
        } else {
            for (int i = event.getPageLow(); i < event.getPageHigh(); i++) {
                ControllerCanvas::callUpdate(i);
            }
        }
    }

    if (event & UpdateEvent::stroke) {
        if (not (event & (UpdateEvent::page)))
            drawerStroke->callUpdate();
    }
}

void ControllerCanvas::refresh(const UpdateEvent& event)
{
    //emit this->widthObjectChanged();
    //emit this->heigthObjectChanged();
    ControllerCanvas::callUpdate(event);
}

void ControllerCanvas::sizeHasChanged(const QSizeF &size)
{
    qDebug() << "asked for new size: " << size;

    this->_width = size.width();
    this->_heigth = size.height();

    WDebug(false, "Call");

    emit this->onWidthObjectChanged();
    emit this->onHeigthObjectChanged();

    ControllerCanvas::callUpdate(UpdateEvent::makeAll());
}

void ControllerCanvas::touchBegin(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::begin);
    DO_IF_DEBUG(_status = waitingFor::update);

    emit this->onTouchBegin(point, pressure);
}

void ControllerCanvas::touchUpdate(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::update);
    emit this->onTouchUpdate(point, pressure);
}

void ControllerCanvas::touchEnd(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::begin);
    emit this->onTouchEnd(point, pressure);
}

void ControllerCanvas::registerHandler(WQMLCanvasHandler *object)
{
    W_ASSERT(object != nullptr);
    W_ASSERT(handler == nullptr);
    W_ASSERT(controllerCanvas != nullptr);

    handler = object;

    QObject::connect(handler, &WQMLCanvasHandler::touchBegin,   controllerCanvas, &ControllerCanvas::touchBegin);
    QObject::connect(handler, &WQMLCanvasHandler::touchUpdate,  controllerCanvas, &ControllerCanvas::touchUpdate);
    QObject::connect(handler, &WQMLCanvasHandler::touchEnd,     controllerCanvas, &ControllerCanvas::touchEnd);
}

void ControllerCanvas::unregisterHandler(WQMLCanvasHandler* object)
{
    W_ASSERT(object != nullptr);
    W_ASSERT(handler != nullptr);

    handler = nullptr;

    QObject::disconnect(object, &WQMLCanvasHandler::touchBegin,   controllerCanvas, &ControllerCanvas::touchBegin);
    QObject::disconnect(object, &WQMLCanvasHandler::touchUpdate,  controllerCanvas, &ControllerCanvas::touchUpdate);
    QObject::disconnect(object, &WQMLCanvasHandler::touchEnd,     controllerCanvas, &ControllerCanvas::touchEnd);
}

