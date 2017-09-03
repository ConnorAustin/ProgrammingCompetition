#include <iostream>

static int nums[4][4];
static bool merged[4][4];

static void move(int direction) {
  switch (direction) {
  case 0:
    for (int y = 0; y < 4; ++y) {
      for (int x = 1; x < 4; ++x) {
        int xx = x;
        while (xx != 0) {
          if (nums[xx - 1][y] == 0) {
            nums[xx - 1][y] = nums[xx][y];
            nums[xx][y] = 0;
            merged[xx - 1][y] = merged[xx][y];
            merged[xx - 1][y] = false;
          } else if (nums[xx - 1][y] == nums[xx][y] && !merged[xx - 1][y] && !merged[xx][y]) {
            nums[xx - 1][y] *= 2;
            nums[xx][y] = 0;
            merged[xx - 1][y] = true;
          } else {
            break;
          }
          --xx;
        }
      }
    }
    break;

  case 1:
    for (int y = 1; y < 4; ++y) {
      for (int x = 0; x < 4; ++x) {
        int yy = y;
        while (yy != 0) {
          if (nums[x][yy - 1] == 0) {
            nums[x][yy - 1] = nums[x][yy];
            nums[x][yy] = 0;
            merged[x][yy - 1] = merged[x][yy - 1];
            merged[x][yy] = false;
          } else if (nums[x][yy - 1] == nums[x][yy] && !merged[x][yy - 1] && !merged[x][yy]) {
            nums[x][yy - 1] *= 2;
            nums[x][yy] = 0;
            merged[x][yy - 1] = true;
          } else {
            break;
          }
          --yy;
        }
      }
    }
    break;
  case 2:
    for (int y = 0; y < 4; ++y) {
      for (int x = 2; x > -1; --x) {
        int xx = x;
        while (xx != 3) {
          if (nums[xx + 1][y] == 0) {
            nums[xx + 1][y] = nums[xx][y];
            nums[xx][y] = 0;
            merged[xx + 1][y] = merged[xx][y];
            merged[xx][y] = false;
          } else if (nums[xx + 1][y] == nums[xx][y] && !merged[xx + 1][y] && !merged[xx][y]) {
            nums[xx + 1][y] *= 2;
            nums[xx][y] = 0;
            merged[xx + 1][y] = true;
          } else {
            break;
          }
          ++xx;
        }
      }
    }
    break;
  case 3:
    for (int y = 2; y > -1; --y) {
      for (int x = 0; x < 4; ++x) {
        int yy = y;
        while (yy != 3) {
          if (nums[x][yy + 1] == 0) {
            nums[x][yy + 1] = nums[x][yy];
            nums[x][yy] = 0;
            merged[x][yy + 1] = merged[x][yy];
            merged[x][yy] = false;
          } else if (nums[x][yy + 1] == nums[x][yy] && !merged[x][yy + 1] && !merged[x][yy]) {
            nums[x][yy + 1] *= 2;
            nums[x][yy] = 0;
            merged[x][yy + 1] = true;
          } else {
            break;
          }
          ++yy;
        }
      }
    }
    break;
  }
}

int main() {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      std::cin >> nums[x][y];
    }
  }
  
  int moveDir;
  std::cin >> moveDir;
  move(moveDir);

  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      std::cout << nums[x][y] << " ";
    }
    std::cout << std::endl;
  }
}
