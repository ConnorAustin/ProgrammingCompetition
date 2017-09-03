#include <iostream>

int boxes[6];

void sort(int* box) {
    if(box[1] < box[2]) {
        std::swap(box[1], box[2]);
    }
    if(box[0] < box[1]) {
        std::swap(box[0], box[1]);
    }
    if(box[1] < box[2]) {
        std::swap(box[1], box[2]);
    }
}

bool try_mask(int mask, int first_height, int second_height) {
    int first_boxes_len = 0;
    int first_boxes[3];
    
    int second_boxes_len = 0;
    int second_boxes[3];
    
    for(int i = 0; i < 6; ++i) {
        if((mask & (1 << i)) != 0) {
            if(first_boxes_len == 3) {
                return false;
            }
            first_boxes[first_boxes_len++] = boxes[i];
        } else {
            if(second_boxes_len == 3) {
                return false;
            }
            second_boxes[second_boxes_len++] = boxes[i];
        }
    }
    if(first_boxes_len != 3 || second_boxes_len != 3) {
        return false;
    }
    int first_sum = first_boxes[0] + first_boxes[1] + first_boxes[2];
    int second_sum = second_boxes[0] + second_boxes[1] + second_boxes[2];
    
    if(first_sum == second_height && second_sum == first_height) {
        std::swap(first_boxes, second_boxes);
        std::swap(first_sum, second_sum);
    }
    if(first_sum == first_height && second_sum == second_height) {    
        sort(first_boxes);
        sort(second_boxes);
        for(int i = 0; i < 3; ++i) {
            std::cout << first_boxes[i] << ' ';
        }
        for(int i = 0; i < 2; ++i) {
            std::cout << second_boxes[i] << ' ';
        }
        std::cout << second_boxes[2] << std::endl;
        return true;
    }
    return false;
}

int main() {
    for(int i = 0; i < 6; ++i) {
        std::cin >> boxes[i];
    }
    int first_height, second_height;
    std::cin >> first_height >> second_height;
    
    for(int mask = 0; mask < (1 << 6); ++mask) {
        if(try_mask(mask, first_height, second_height)) {
            return 0;
        }
    }
}