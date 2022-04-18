#include "mainwindow.h"
#include "programmlogic.h"

#include "customtyperegistrator.h"
#include "mathhelpers.h"
#include <QApplication>
#include <QDebug>
#include <list>
#include <vector>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  CustomTypeRegistrator *registrator = new CustomTypeRegistrator();
  registrator->registerCustomTypes();

  MainWindow w;
  ProgrammLogic logic;

  QObject::connect(w.ui_startButton, &QPushButton::clicked, &logic,
                   &ProgrammLogic::startHeavyComputation);

  for (std::list<ComputeWorker *>::iterator it =
           logic.freeComputeWorkers.begin();
       it != logic.freeComputeWorkers.end(); ++it) {
    ComputeWorker *worker = *it;
    QObject::connect(&logic, &ProgrammLogic::heavyComputationStarted,
                     w.ui_table, [&w, worker] {
                       int rowId = w.MainWindow::receiveWorkStatus(worker);
                       w.map[worker] = rowId;
                     });

    QObject::connect(worker, &ComputeWorker::workEnded, [&w, worker] {
      int rowId = w.map[worker];
      w.freeRow(rowId);
      QObject::disconnect(worker, nullptr, &w, nullptr);
      w.map.erase(worker);
    });
  }

  w.show();

  return a.exec();
}
