#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "core/core.h"
#include <functional>

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _getImg([]() -> const QPixmap &{
        return QPixmap();
    })
    , _functionSet(false)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    ControllerCanvas::registerDrawer(this);
    this->setAntialiasing(true);
    this->setRenderTarget(QQuickPaintedItem::Image);
}

void WQMLCanvasComponent::paint(QPainter *painter)
{
    const auto width = this->width();
    const auto height = this->height();

    //core::painter_set_antialiasing(*painter);
    //painter->setRenderHint(QPainter::LosslessImageRendering);
    const auto timeOld = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );

    const auto &img = this->_getImg();

    const auto timeNew = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );

    if (this->_functionSet) {
        const QRect target = QRect(0, 0, width, img.height() * width / img.width());


        const auto timeOld = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        );

        //painter->drawLine(10, 10, 600, 600);
        painter->drawPixmap(target, img);

        const auto timeNew = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        );
        //qDebug() << "Time draw img" << (timeNew - timeOld).count();
    }

    /*static std::chrono::milliseconds ms;
    const auto old = ms;
    ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );*/

    const auto now = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    const auto diff = (now - timeOld).count();

    qDebug() << "Paint T=" << diff << "ms" << "Time for getImg(): " << (timeNew - timeOld).count() << "["<< 1./(double(diff) / 1000.) << "Hz]";
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

void WQMLCanvasComponent::setFunc(std::function<const QPixmap &()> getImg)
{
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
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
