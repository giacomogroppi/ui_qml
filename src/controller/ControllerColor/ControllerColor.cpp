#include "ControllerColor.h"

ControllerColor::ControllerColor(QObject *parent)
    : QObject{parent}
{

}

bool ControllerColor::isDarkMode() const
{
    return true;
}
