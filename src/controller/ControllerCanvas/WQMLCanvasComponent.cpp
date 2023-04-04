#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "core/core.h"
#include <functional>

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _getImg([]() {
        return QImage();
    })
    , _functionSet(false)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    ControllerCanvas::registerDrawer(this);
}

void WQMLCanvasComponent::paint(QPainter *painter)
{
    const auto width = this->width();
    const auto height = this->height();

    core::painter_set_antialiasing(*painter);
    //painter->setRenderHint(QPainter::LosslessImageRendering);
    const auto &img = this->_getImg();
    if (this->_functionSet) {
        const QRect target = QRect(0, 0, width, img.height() * width / img.width());

        painter->drawImage(target, img);
    }
    /*static int x = 0;
    static int y = 0;
    painter->drawLine(x, y, x + 100, y + 100);

    x += 1;
    y += 1;*/
    static std::chrono::milliseconds ms;
    const auto old = ms;
    ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
        );

    const int diff = (ms - old).count();
    //WDebug(true, diff);
    WDebug(true, "update call" << diff << "ms" << 1. / (double(diff) / 1000.) << "Hz");
}

void WQMLCanvasComponent::setXPosition(double x)
{
    this->_x = x;
    emit onXPositionChanged();
}

double WQMLCanvasComponent::xPosition() const
{
    return this->_x;
}

double WQMLCanvasComponent::yPosition() const
{
    return this->_y;
}

void WQMLCanvasComponent::setFunc(std::function<const QImage &()> getImg)
{
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
    const auto &img = this->_getImg();
    WDebug(false, "ciao");
}

void WQMLCanvasComponent::callUpdate()
{
    this->update();
}

void WQMLCanvasComponent::setYPosition(double y)
{
    this->_y = y;
    emit onYPositionChanged();
}
