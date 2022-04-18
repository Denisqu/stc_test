#ifndef STARTBUTTONLISTENER_H
#define STARTBUTTONLISTENER_H

#include <QObject>

class StartButtonListener : public QObject {
  Q_OBJECT
public:
  explicit StartButtonListener(QObject *parent = nullptr);

public slots:
  void buttonPushed();
};

#endif // STARTBUTTONLISTENER_H
