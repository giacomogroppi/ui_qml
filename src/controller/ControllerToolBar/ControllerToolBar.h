#pragma once

#include <QObject>
#include <QColor>
#include <QQmlApplicationEngine>

#include "touch/TabletController.h"

class ControllerToolBar: public QObject {
    Q_OBJECT

    enum ToolType {
        Pen,
        Rubber,
        Highlighter,
        Hand,
        Cut
    } _type;

    QColor _color;

    TabletController *_tabletController;

    struct EventStack {
        EventStack(const QPointF &point, double pressure, int type) : point(point), pressure(pressure), type(type) {};
        QPointF point;
        double pressure;

        /**
         * 0 --> begin
         * 1 --> update
         * 2 --> end
        */
        int type;
    };

    //QList<EventStack> points;

#define brown QColor(165,42,42)

public:
    explicit ControllerToolBar(QObject *parent, TabletController *tabletController);
    ~ControllerToolBar();

    Q_INVOKABLE void clickSelectPen();
    Q_INVOKABLE void clickRubber();
    Q_INVOKABLE void clickHand();
    Q_INVOKABLE void clickHighlighter();
    Q_INVOKABLE void clickCut();

    Q_INVOKABLE void clickBlack();
    Q_INVOKABLE void clickBrown();
    Q_INVOKABLE void clickWhite();
    Q_INVOKABLE void clickYellow();
    Q_INVOKABLE void clickRed();

    Q_PROPERTY(bool isPenSelected READ isPen NOTIFY toolHasChanged);
    bool isPen() const;

    Q_PROPERTY(bool isRubberSelected READ isRubber NOTIFY toolHasChanged);
    bool isRubber() const;

    Q_PROPERTY(bool isHandSelected READ isHand NOTIFY toolHasChanged);
    bool isHand() const;

    Q_PROPERTY(bool isHighlighterSelected READ isHighlighter NOTIFY toolHasChanged);
    bool isHighlighter() const;

    Q_PROPERTY(bool isCutSelected READ isCut NOTIFY toolHasChanged);
    bool isCut() const;

    bool isBlack()  const { return this->_color == Qt::black; };
    bool isBrown()  const { return this->_color == brown; };
    bool isWhite()  const { return this->_color == Qt::white; };
    bool isYellow() const { return this->_color == Qt::yellow; };
    bool isRed()    const { return this->_color == Qt::red; };

    Q_PROPERTY(bool isBlack     READ isBlack    NOTIFY colorChanged);
    Q_PROPERTY(bool isBrown     READ isBrown    NOTIFY colorChanged);
    Q_PROPERTY(bool isWhite     READ isWhite    NOTIFY colorChanged);
    Q_PROPERTY(bool isYellow    READ isYellow   NOTIFY colorChanged);
    Q_PROPERTY(bool isRed       READ isRed      NOTIFY colorChanged);

    const QPixmap &getImg();

signals:
    void toolHasChanged();
    void colorChanged();
    void onNeedRefresh();
public slots:
    void touchBegin(const QPointF &point, double pressure);
    void touchUpdate(const QPointF &point, double pressure);
    void touchEnd(const QPointF &point, double pressure);

    void positionChanged(const QPointF &newPosition);
    //void endDraw();
};
