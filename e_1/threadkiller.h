#ifndef THREADKILLER_H
#define THREADKILLER_H

#include <QObject>

class ThreadKiller : public QObject {
  Q_OBJECT
public:
  explicit ThreadKiller(QObject *parent = nullptr);
public slots:
  void killThread();

signals:
};

#endif // THREADKILLER_H
