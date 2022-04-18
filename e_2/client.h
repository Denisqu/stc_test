#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject {
  Q_OBJECT
public:
  QString ip;
  quint16 port;
  QByteArray lastMsg;
  explicit Client(QObject *parent = nullptr);
  void setSocket(QTcpSocket *socket);
  bool disconnectFromServer();

signals:
  void readMessage(QByteArray *data);
  void disconnected(Client *client);

public slots:
  void connected();
  void disconnected_slot();
  void readyRead();

private:
  QTcpSocket *socket;
};

#endif // CLIENT_H
