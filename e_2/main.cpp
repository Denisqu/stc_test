#include "mainwindow.h"

#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  TcpServer server;

  w.portLabel->setText("Listening port: " + QString::number(server.listenPort));
  w.portLabel->repaint();

  w.onClickFunc = [&server](Client *client) {
    server.disconnectClient(client);
  };

  QObject::connect(&server, &TcpServer::clientConnected, &w,
                   &MainWindow::addRow);
  QObject::connect(&server, &TcpServer::messageReceived, &w,
                   &MainWindow::printClientsLastMessage);
  QObject::connect(&server, &TcpServer::clientDisconnected, &w,
                   &MainWindow::clearMapAndRow);

  w.show();
  return a.exec();
}
