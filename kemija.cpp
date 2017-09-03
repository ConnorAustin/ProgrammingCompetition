#include <algorithm>
#include <cstdint>
#include <cstdio>
using i64 = int64_t;

int w, h;
i64 matrix[10000][10001];

i64& augment(int y) {
    return matrix[y][w];
}

// Shortcut row subtract we can sometimes take
void special_row_sub(int startX, int y, int dest) {
  matrix[dest][startX] = 0;
  matrix[dest][startX + 1] = 0;
  matrix[dest][startX + 2] = -1;
  
  augment(dest) -= augment(y);
}

void row_add(int startX, int y, int dest, i64 mul) {
  for(int x = startX; x < w; ++x) {
      matrix[dest][x] += matrix[y][x] * mul;
  }
  augment(dest) += augment(y) * mul;
}

void elim(int x, int elimY, int y) {
  int mul = matrix[elimY][x] / matrix[y][x];
  row_add(x, y, elimY, -mul);
}

// Shortcut elim that we can sometimes take
void special_elim(int offset, int x, int elimY, int y) {
  matrix[elimY][x] = 0;
  matrix[elimY][x + offset] = -1;
  
  augment(elimY) += augment(y);
}

i64 max(i64 a, i64 b) {
    return a > b ? a : b;
}

void constraint_solve() {
    // Exclusive
    int amin = 0;
    int bmin = 0;

    for(int y = 0; y < h - 2; ++y) {
        int a = matrix[y][w - 2];
        int b = matrix[y][w - 1];

        if(a == -1) {
            if(augment(y) < 0) {
                amin = max(-augment(y), amin);
            }
        } 
        else if(b == -1) {
            if(augment(y) < 0) {
                bmin = max(-augment(y), bmin);
            }
        }
    }
    amin += 1;
    bmin += 1;

    augment(h - 1) = amin;
    augment(h - 2) = bmin;

    for(int y = 0; y < h - 2; ++y) {
        augment(y) -= amin * matrix[y][w - 2];
        augment(y) -= bmin * matrix[y][w - 1];   
    }
    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            matrix[y][x] = x == y ? 1 : 0;
        }
    }
    
    augment(h - 2) = amin;
    augment(h - 1) = bmin;
}


void gaussian_jordan() {
    for(int pivot = 1; pivot < h - 2; ++pivot) {
        special_row_sub(pivot, pivot, pivot - 1);
    }

    for(int offset = 3; offset < h - 2; offset *= 2) {
        for(int pivot = offset; pivot < h - 2; ++pivot) {
            if(pivot + offset < w - 1) {
                special_elim(offset, pivot, pivot - offset, pivot);
            } else {
                elim(pivot, pivot - offset, pivot);
            }
        }
    }

    elim(0, h - 2, 0);
    elim(1, h - 2, 1);

    // Free variables!
    if(matrix[h - 2][w - 2] == 0) {
        constraint_solve();
        return;
    }

    elim(0, h - 1, 0);

    for(int y = 0; y < h - 2; ++y) {
        elim(w - 2, y, h - 2);
    }
    elim(w - 2, h - 1, h - 2);

    // Divide row
    augment(h - 2) /= matrix[h - 2][w - 2];
    matrix[h - 2][w - 1] /= matrix[h - 2][w - 2];
    matrix[h - 2][w - 2] = 1;

    // Divide row
    augment(h - 1) /= matrix[h - 1][w - 1];
    matrix[h - 1][w - 1] = 1;

    for(int y = 0; y < h - 1; ++y) {
        elim(w - 1, y, h - 1);
    }
}

void init_matrix() {
    for(int y = 0; y < h - 2; ++y) {
        matrix[y][y] = 1;
        matrix[y][y + 1] = 1;
        matrix[y][y + 2] = 1;
    }
    matrix[h - 2][0] = 1;
    matrix[h - 2][1] = 1;
    matrix[h - 2][w - 1] = 1;

    matrix[h - 1][0] = 1;
    matrix[h - 1][w - 1] = 1;
    matrix[h - 1][w - 2] = 1;
}

int main() {
    scanf("%d", &h);
    w = h;
    
    scanf("%lld", &augment(h - 2));
    for(int y = 0; y < h - 2; ++y) {
        scanf("%lld", &augment(y));
    }
    scanf("%lld", &augment(h - 1));
    
    init_matrix();
    
    switch(w) {
        case 1:
            printf("%lld\n", augment(0));
            return 0;
        case 2:
            puts("1");
            printf("%lld\n", augment(1) - 1);
            return 0;
        case 3:
            constraint_solve();
            break;
        default:
            gaussian_jordan();
            break;
    }
    
    for(int y = 0; y < h; ++y) {
        printf("%lld\n", augment(y));
    }
}