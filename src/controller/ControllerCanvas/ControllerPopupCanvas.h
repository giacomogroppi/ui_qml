#pragma once

#include <QObject>
#include "utils/WCommonScript.h"
#include "Scheduler/WObject.h"
#include "core/WFlags.h"

class ControllerPopupCanvas : public QObject
{
    Q_OBJECT

    enum PopupVisibility {
        copy = 0x1,
        del = 0x2,
        cut = 0x4
    };

    WFlags<PopupVisibility> _types;
    bool _isVisible;

public:
    explicit ControllerPopupCanvas(QObject *parent);
    ~ControllerPopupCanvas();

    Q_INVOKABLE void clickCopy(const QPointF& point);
    Q_INVOKABLE void clickDelete(const QPointF& point);
    Q_INVOKABLE void clickCut(const QPointF& point);

    Q_PROPERTY(bool isCopySelectable READ isCopySelectable NOTIFY clickableChanged);
    nd bool isCopySelectable() const;

    Q_PROPERTY(bool isCutSelectable READ isCutSelectable NOTIFY clickableChanged);
    nd bool isCutSelectable() const;

    Q_PROPERTY(bool isDeleteSelectable READ isDeleteSelectable NOTIFY clickableChanged);
    nd bool isDeleteSelectable() const;

    Q_PROPERTY(bool isVisible READ isVisible NOTIFY onVisibilityChanged);
    nd bool isVisible() const;

signals:
    void clickableChanged();
    void onVisibilityChanged();

public:
    DEFINE_LISTENER_1(copySelectable, bool, selectable);
    DEFINE_LISTENER_1(deleteSelectable, bool, selectable);
    DEFINE_LISTENER_1(cutSelectable, bool, selectable);
    DEFINE_LISTENER_1(visibilityChanged, bool, isVisible);

    W_EMITTABLE_0(copyClicked);
    W_EMITTABLE_0(deleteClicked);
    W_EMITTABLE_0(cutClicked);
};

