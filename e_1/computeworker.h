#ifndef COMPUTEWORKER_H
#define COMPUTEWORKER_H

#include <QObject>
#include <QThread>
#include <functional>
#include <string>

class ComputeWorker : public QObject {
  Q_OBJECT

public:
  int computeLength;
  std::string computeType = "BubbleSort";
  explicit ComputeWorker(int computeLength, QObject *parent = nullptr);
  void stopThread();

public slots:
  void doWork();

signals:
  void workProgressed(int val);
  void workStarted();
  void workEnded(QThread *thread);
};

#endif // COMPUTEWORKER_H
