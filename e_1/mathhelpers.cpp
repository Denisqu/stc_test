#include "mathhelpers.h"
#include <QDebug>

using namespace MathHelpers;

void MathHelpers::bubbleSort(std::vector<int> &vec,
                             std::function<void(int)> progressFunc) {
  int steps = 0;
  for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); i++) {

    steps++;
    progressFunc(((float)steps / (float)vec.size()) * 100);

    for (std::vector<int>::iterator j = vec.begin();
         j != vec.end() - (steps + 0); j++) {

      if (*j > *(j + 1)) {
        int temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
      }
    }
  }
}
