#include "mainwindow.h"
#include "computeworker.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QObject>
#include <QProgressBar>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  findChilds();
  setupRows(rowCount);
  btnListener = std::unique_ptr<StartButtonListener>(new StartButtonListener());
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::findChilds() {
  ui_table = findChild<QTableWidget *>("mainTable");
  ui_startButton = findChild<QPushButton *>("startButton");
}

void MainWindow::setupRows(int count) {
  ui_table->setRowCount(count);

  for (int i = 0; i < count; i++) {
    QProgressBar *pgbar = new QProgressBar();
    ui_table->setCellWidget(i, ProgressBarColumn, pgbar);
    freeRowIds.push_back(i);
  }
}

void MainWindow::setupRow(int newRowCount, int id) {
  ui_table->setRowCount(newRowCount);

  QProgressBar *pgbar = new QProgressBar();
  ui_table->setCellWidget(id, ProgressBarColumn, pgbar);
  freeRowIds.push_back(id);
}

void MainWindow::changeRowProgressBarValue(int rowId, int value) {
  QProgressBar *bar =
      qobject_cast<QProgressBar *>(ui_table->cellWidget(rowId, 1));

  bar->setValue(value);
}

void MainWindow::changeRowProcedureName(int row, std::string name) {
  QTableWidgetItem *item = new QTableWidgetItem;
  item->setText(QString::fromStdString(name));
  ui_table->setItem(row, ProcedureNameColumn, item);
}

int MainWindow::receiveWorkStatus(ComputeWorker *worker) {

  int freeRowId = occupyRow();

  if (freeRowId == -1)
    freeRowId = addNewRow();

  qDebug() << QString::fromStdString(std::to_string(worker->computeLength));

  changeRowProcedureName(freeRowId, worker->computeType + " : " +
                                        std::to_string(worker->computeLength));

  connect(worker, &ComputeWorker::workProgressed, this,
          [freeRowId, this](int value) {
            changeRowProgressBarValue(freeRowId, value);
          });

  return freeRowId;
}

int MainWindow::occupyRow() {
  if (freeRowIds.empty())
    return addNewRow();

  int id = freeRowIds.front();
  freeRowIds.pop_front();
  return id;
}

void MainWindow::freeRow(int id) { freeRowIds.push_back(id); }

int MainWindow::addNewRow() {
  rowCount++;
  setupRow(rowCount, rowCount);
  freeRowIds.push_back(rowCount);
  return rowCount;
}
