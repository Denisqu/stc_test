#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <client.h>

#include <list>

class TcpServer : public QObject {
  Q_OBJECT
public:
  const quint16 listenPort = 9999;
  explicit TcpServer(QObject *parent = nullptr);
  std::list<Client *> clients;

public slots:
  void newConnection();
  void disconnectClient(Client *client);
  void receiveMessage(QByteArray *data);

private:
  QTcpServer *server;

signals:
  void clientDisconnected(Client *client);
  void clientConnected(Client *client);
  void messageReceived(Client *client, QByteArray *data);
};

#endif // TCPSERVER_H
