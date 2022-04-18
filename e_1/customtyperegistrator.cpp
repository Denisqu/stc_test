#include "customtyperegistrator.h"

CustomTypeRegistrator::CustomTypeRegistrator(QObject *parent)
    : QObject(parent) {}

void CustomTypeRegistrator::registerCustomTypes() {
  qRegisterMetaType<std::string>();
}
