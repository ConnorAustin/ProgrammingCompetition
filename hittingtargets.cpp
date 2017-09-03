#include <iostream>
#include <cmath>
#include <vector>

class shape {
public:
  bool isCirc;
  int x, y, x2, y2, r;
  shape(int x, int y, int r) : isCirc(true), x(x), y(y), r(r) { }
  shape(int x, int y, int x2, int y2) : isCirc(false), x(x), y(y), x2(x2), y2(y2) { }
  
  bool contains(int x, int y) {
    if(isCirc) {
      double xDiff = x - this->x;
      double yDiff = y - this->y;
      xDiff *= xDiff;
      yDiff *= yDiff;
      return std::sqrt(xDiff + yDiff) <= (double)r;
    } else {
      return x >= this->x && x <= this->x2 && y >= this->y && y <= this->y2;
    }
  }
};

int main() {
  int shapeCount;
  std::cin >> shapeCount;
  
  std::vector<shape> shapes;
  
  for(int i = 0; i < shapeCount; ++i) {
    std::string shapeType;
    std::cin >> shapeType;
    
    if(shapeType == "rectangle") {
      int x, y, x2, y2;
      std::cin >> x;
      std::cin >> y;
      std::cin >> x2;
      std::cin >> y2;
      
      shapes.emplace_back(x, y, x2, y2);
    } else {
      int x, y, r;
      std::cin >> x;
      std::cin >> y;
      std::cin >> r;
      
      shapes.emplace_back(x, y, r);
    }
  }
  
  int shots;
  std::cin >> shots;
  
  for(int i = 0; i < shots; ++i) {
    int hits = 0;
    
    int x, y;
    std::cin >> x;
    std::cin >> y;
    
    for(shape s : shapes) {
      if(s.contains(x, y)) {
        ++hits;
      }
    }
    std::cout << hits << std::endl;
  }
}
