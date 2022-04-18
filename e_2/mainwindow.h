#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QLabel>
#include <QMainWindow>
#include <QString>
#include <QTableWidget>
#include <functional>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  int rowCount = 0;
  QTableWidget *ui_table;
  QLabel *portLabel;
  std::unordered_map<Client *, int> map;
  std::function<void(Client *)> onClickFunc;

  ~MainWindow();
  MainWindow(QWidget *parent = nullptr);
  void findChilds();

public slots:
  void addRow(Client *client);
  void clearMapAndRow(Client *deletedClient);
  void clearLastRow();
  void printClientsLastMessage(Client *client, QByteArray *data);

private:
  Ui::MainWindow *ui;
  void rebuildMapAndTable(int deletedRow);
};

#endif // MAINWINDOW_H
