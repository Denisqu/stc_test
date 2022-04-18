#include "client.h"
#include "QTcpServer"

Client::Client(QObject *parent) : QObject(parent) {}

void Client::setSocket(QTcpSocket *socket) {
  this->socket = socket;
  this->ip = socket->peerAddress().toString();
  this->port = socket->peerPort();

  qDebug() << "A new socket created!";

  connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected_slot()));
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

  qDebug() << " Client connected at " << socket->peerAddress().toString();
}

void Client::connected() { qDebug() << "Client connected event"; }

void Client::disconnected_slot() {
  qDebug() << "Client disconnected";
  emit disconnected(this);
}

bool Client::disconnectFromServer() {

  if (!socket->isOpen())
    return true;

  this->socket->close();
  return false;
}

void Client::readyRead() {
  QByteArray data = socket->readAll();
  lastMsg = data;
  emit readMessage(&data);
}
