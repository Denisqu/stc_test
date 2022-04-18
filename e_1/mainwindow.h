#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "computeworker.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <memory>
#include <startbuttonlistener.h>
#include <string>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  QTableWidget *ui_table;
  QPushButton *ui_startButton;
  std::unordered_map<ComputeWorker *, int> map;
  int rowCount = 10;
  const int ProcedureNameColumn = 0;
  const int ProgressBarColumn = 1;

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void freeRow(int id);

public slots:
  int receiveWorkStatus(ComputeWorker *worker);
  void changeRowProgressBarValue(int rowId, int value);
  void changeRowProcedureName(int row, std::string name);

private:
  Ui::MainWindow *ui;
  std::unique_ptr<StartButtonListener> btnListener;
  std::list<int> freeRowIds;

  void setupRow(int newRowCount, int id);
  void setupRows(int count);
  void findChilds();
  int occupyRow();
  int addNewRow();
};

#endif // MAINWINDOW_H
