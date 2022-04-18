#include "programmlogic.h"
#include "computeworker.h"
#include <QDebug>
#include <threadkiller.h>

ProgrammLogic::ProgrammLogic(QObject *parent) : QObject(parent) { init(); }

void ProgrammLogic::init() {
  for (int i = 1; i < ThreadCount + 1; i++) {
    ComputeWorker *worker = new ComputeWorker(2500 * i);
    QObject::connect(this, &ProgrammLogic::heavyComputationStarted, worker,
                     &ComputeWorker::doWork);
    QObject::connect(worker, &ComputeWorker::workEnded, this,
                     &ProgrammLogic::quitThread);
    freeComputeWorkers.push_back(worker);
  }
}

void ProgrammLogic::quitThread(QThread *thread) {
  ComputeWorker *worker = qobject_cast<ComputeWorker *>(sender());

  worker->moveToThread(this->thread());

  ThreadKiller *killer = new ThreadKiller;
  QObject::connect(this, &ProgrammLogic::killThreads, killer,
                   &ThreadKiller::killThread);
  killer->moveToThread(thread);

  emit killThreads();

  freeComputeWorkers.push_back(worker);
}

void ProgrammLogic::createThreadPool(int count) {
  for (int i = 0; i < count; i++) {
    QThread *thread = new QThread();
    thread->setPriority(QThread::TimeCriticalPriority);

    this->threadPool.push_front(thread);
  }
}

void ProgrammLogic::startHeavyComputation() {

  if (freeComputeWorkers.size() < ThreadCount)
    return;

  createThreadPool(ThreadCount);

  for (int i = 0; i < ThreadCount; i++) {
    QThread *thread = threadPool.back();
    threadPool.pop_back();

    ComputeWorker *worker = freeComputeWorkers.back();
    freeComputeWorkers.pop_back();

    worker->moveToThread(thread);

    thread->start(QThread::TimeCriticalPriority);
  }

  emit heavyComputationStarted();
}
