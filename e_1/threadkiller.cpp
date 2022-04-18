#include "threadkiller.h"
#include <QApplication>
#include <QThread>
ThreadKiller::ThreadKiller(QObject *parent) : QObject(parent) {}

void ThreadKiller::killThread() {
  if (this->thread() == QApplication::instance()->thread())
    return;

  this->thread()->exit();
  this->deleteLater();
}
