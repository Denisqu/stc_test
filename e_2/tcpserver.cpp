#include "tcpserver.h"
#include "client.h"
#include <QDebug>

TcpServer::TcpServer(QObject *parent) : QObject(parent) {
  server = new QTcpServer(this);

  QObject::connect(server, &QTcpServer::newConnection, this,
                   &TcpServer::newConnection);

  if (!server->listen(QHostAddress::Any, listenPort)) {
    qDebug() << "Server could not start";
    return;
  }

  qDebug() << "Server started on port " << server->serverPort();
  qDebug() << "Server ip address: " << server->serverAddress();
}

void TcpServer::newConnection() {
  // need to grab the socket
  QTcpSocket *socket = server->nextPendingConnection();

  Client *client = new Client(this);
  client->setSocket(socket);
  clients.push_front(client);

  emit clientConnected(client);

  QObject::connect(client, &Client::readMessage, this,
                   &TcpServer::receiveMessage);
  QObject::connect(client, &Client::disconnected, this,
                   &TcpServer::disconnectClient);

  socket->write("Hello client\r\n");
  socket->flush();

  qDebug() << "client ip: " << socket->peerAddress().toString();
  qDebug() << "client port: " << socket->peerPort();

  // socket->close();
}

void TcpServer::receiveMessage(QByteArray *data) {
  emit messageReceived(qobject_cast<Client *>(sender()), data);
}

void TcpServer::disconnectClient(Client *client) {
  if (client->disconnectFromServer())
    return;

  emit clientDisconnected(client);
}
