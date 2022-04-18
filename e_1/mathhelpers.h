#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <functional>
#include <vector>

namespace MathHelpers {

void bubbleSort(std::vector<int> &vec, std::function<void(int)> progressFunc);

} // namespace MathHelpers

#endif // MATHFUNCTIONS_H

// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
