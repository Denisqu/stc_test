#include "startbuttonlistener.h"
#include "QDebug"

StartButtonListener::StartButtonListener(QObject *parent) : QObject(parent) {}

void StartButtonListener::buttonPushed() { qDebug() << "Button pushed!!!"; }
