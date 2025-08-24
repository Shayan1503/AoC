#include "utils/graphics.hpp"
#include "utils/solution_registry.cpp"

int main() {
  Aoi ui;
  ui.run(getAvailableSolutions());

  return 0;
}
