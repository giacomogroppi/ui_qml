#pragma once

#include <QObject>
#include "utils/WCommonScript.h"
#include "Scheduler/WObject.h"
#include "core/WFlags.h"
#include "touch/TabletController.h"

class ControllerPopupCanvas final: public QObject
{
    Q_OBJECT

    enum PopupVisibility {
        copy = 0x1,
        del = 0x2,
        cut = 0x4,
        paste = 0x8
    };

    WFlags<PopupVisibility> _types;
    bool _isVisible;

public:
    explicit ControllerPopupCanvas(QObject *parent);
    ~ControllerPopupCanvas();

    Q_INVOKABLE void clickCopy();
    Q_INVOKABLE void clickDelete();
    Q_INVOKABLE void clickCut();
    Q_INVOKABLE void clickPaste();

    Q_PROPERTY(bool isCopySelectable READ isCopySelectable NOTIFY clickableChanged);
    nd bool isCopySelectable() const;

    Q_PROPERTY(bool isCutSelectable READ isCutSelectable NOTIFY clickableChanged);
    nd bool isCutSelectable() const;

    Q_PROPERTY(bool isDeleteSelectable READ isDeleteSelectable NOTIFY clickableChanged);
    nd bool isDeleteSelectable() const;

    Q_PROPERTY(bool isPasteSelectable READ isPasteSelectable NOTIFY clickableChanged);
    nd bool isPasteSelectable() const;

    Q_PROPERTY(bool isVisible READ isVisible NOTIFY onVisibilityChanged);
    nd bool isVisible() const;

signals:
    void clickableChanged();
    void onVisibilityChanged();

public:
    DEFINE_LISTENER_1(copySelectable, bool, selectable);
    DEFINE_LISTENER_1(deleteSelectable, bool, selectable);
    DEFINE_LISTENER_1(cutSelectable, bool, selectable);
    DEFINE_LISTENER_1(pasteSelectable, bool, selectable);

    DEFINE_LISTENER_2(propertyShow, const PointF&, point, ActionProperty, actionProperty);

    DEFINE_LISTENER_1(visibilityChanged, bool, isVisible);

    W_EMITTABLE_0(copyClicked);
    W_EMITTABLE_0(deleteClicked);
    W_EMITTABLE_0(cutClicked);
    W_EMITTABLE_0(pasteClicked);
};

