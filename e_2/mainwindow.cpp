#include "mainwindow.h"

#include "qdebug.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  findChilds();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::findChilds() {
  ui_table = findChild<QTableWidget *>("mainTable");
  portLabel = findChild<QLabel *>("portLabel");
}

void MainWindow::addRow(Client *client) {

  ui_table->setRowCount(rowCount + 1);
  map[client] = rowCount;

  // set ip:
  QTableWidgetItem *ip_item = new QTableWidgetItem;
  ip_item->setText(client->ip);
  ui_table->setItem(rowCount, 0, ip_item);

  // set port:
  QTableWidgetItem *port_item = new QTableWidgetItem;
  port_item->setText(QString::number(client->port));
  ui_table->setItem(rowCount, 1, port_item);

  // add button:
  QPushButton *btn_disc = new QPushButton();
  btn_disc->setText("Disconnect");
  ui_table->setCellWidget(rowCount, 3, btn_disc);
  connect(btn_disc, &QPushButton::clicked,
          [this, client] { onClickFunc(client); });

  rowCount++;
}

void MainWindow::printClientsLastMessage(Client *client, QByteArray *data) {
  int row = map[client];

  // set last message
  QTableWidgetItem *msg_item = new QTableWidgetItem;
  msg_item->setText(QString(*data));
  ui_table->setItem(row, 2, msg_item);
}

void MainWindow::clearMapAndRow(Client *deletedClient) {
  qDebug() << "starting clearMapAndRow";
  int deletedRow = map[deletedClient];
  map.erase(deletedClient);
  rowCount--;

  if (deletedRow == rowCount) {
    clearLastRow();
    ui_table->setRowCount(rowCount);
    return;
  }

  rebuildMapAndTable(deletedRow);
}

void MainWindow::rebuildMapAndTable(int deletedRow) {
  for (auto i : map) {
    if (deletedRow > i.second)
      continue;

    // smestit' vse na 1 vverh
    int row = i.second;
    map[i.first] = row - 1;
    Client *client = i.first;

    // ip vverh
    QTableWidgetItem *ip_item = new QTableWidgetItem;
    ip_item->setText(i.first->ip);
    ui_table->setItem(map[i.first], 0, ip_item);

    // port vverh
    QTableWidgetItem *port_item = new QTableWidgetItem;
    port_item->setText(QString::number(i.first->port));
    ui_table->setItem(map[i.first], 1, port_item);

    // last msg vverh
    QTableWidgetItem *msg_item = new QTableWidgetItem;
    msg_item->setText(QString(i.first->lastMsg));
    ui_table->setItem(map[i.first], 2, msg_item);

    // knopka vverh
    // create new button connection
    QPushButton *btn_disc = new QPushButton();
    btn_disc->setText("Disconnect");
    ui_table->setCellWidget(map[i.first], 3, btn_disc);
    connect(btn_disc, &QPushButton::clicked,
            [this, client] { onClickFunc(client); });

    qDebug() << "rebuilded map and table";
  }

  clearLastRow();

  ui_table->setRowCount(rowCount);
}

void MainWindow::clearLastRow() {
  ui_table->setItem(rowCount, 0, new QTableWidgetItem);
  ui_table->setItem(rowCount, 1, new QTableWidgetItem);
  ui_table->setItem(rowCount, 2, new QTableWidgetItem);
  ui_table->setItem(rowCount, 3, new QTableWidgetItem);
}
