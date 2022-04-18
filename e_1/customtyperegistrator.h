#ifndef CUSTOMTYPEREGISTRATOR_H
#define CUSTOMTYPEREGISTRATOR_H

#include <QObject>

class CustomTypeRegistrator : public QObject {
  Q_OBJECT
public:
  explicit CustomTypeRegistrator(QObject *parent = nullptr);
  void registerCustomTypes();

signals:
};

Q_DECLARE_METATYPE(std::string)

#endif // CUSTOMTYPEREGISTRATOR_H
