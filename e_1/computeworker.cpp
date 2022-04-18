#include "computeworker.h"
#include "mathhelpers.h"

#include <QCoreApplication>
#include <QDebug>
#include <algorithm>
#include <ctime>
#include <vector>

ComputeWorker::ComputeWorker(int vectorLength, QObject *parent)
    : QObject(parent) {
  this->computeLength = vectorLength;
}

void ComputeWorker::doWork() {
  emit workStarted();

  std::srand(unsigned(std::time(nullptr)));
  std::vector<int> v(computeLength);
  std::generate(v.begin(), v.end(), std::rand);

  MathHelpers::bubbleSort(v, [=](int val) { emit workProgressed(val); });

  emit workEnded(this->thread());

  this->moveToThread(QCoreApplication::instance()->thread());
}
