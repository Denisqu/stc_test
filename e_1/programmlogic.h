#ifndef PROGRAMMLOGIC_H
#define PROGRAMMLOGIC_H

#include "computeworker.h"
#include <QObject>
#include <QThread>
#include <list>
#include <utility>

class ProgrammLogic : public QObject {
  Q_OBJECT
public:
  std::list<QThread *> threadPool;
  std::list<QThread *> occupiedThreads;
  std::list<ComputeWorker *> freeComputeWorkers;
  const unsigned int ThreadCount = 10;

  explicit ProgrammLogic(QObject *parent = nullptr);
  void createThreadPool(int count);

  void startHeavyComputation();

public slots:
  void quitThread(QThread *thread);

signals:
  void heavyComputationStarted();
  void killThreads();

private:
  void init();
};

#endif // PROGRAMMLOGIC_H
