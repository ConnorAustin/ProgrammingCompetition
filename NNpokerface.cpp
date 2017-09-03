#include <cstdio>
#include <cstring>

int clubs[13];
int hearts[13];
int diamonds[13];
int spades[13];

void parse_card(int num, char suit) {
    if(num >= '2' && num <= '9') {
        num = num - '1';
    } else {
        switch(num) {
            case 'A': num = 0; break;
            case 'T': num = 9; break;
            case 'J': num = 10; break;
            case 'Q': num = 11; break;
            case 'K': num = 12; break;
        }
    }
    switch(suit) {        
        case 'C': ++clubs[num]; break;
        case 'H': ++hearts[num]; break;
        case 'D': ++diamonds[num]; break;
        case 'S': ++spades[num]; break;
    }    
}

bool royal_flush(int* suit) {
    return suit[0] == 1 && suit[9] == 1 && suit[10] == 1 && suit[11] == 1 && suit[12] == 1;
}

bool flush(int* suit) {
    int cards = 0;
    
    for(int i = 0; i < 13; ++i) {
        if(suit[i] > 0) {
            ++cards;
        }
    }
    return cards == 5;
}

int card_count(int number) {
    return clubs[number] + hearts[number] + diamonds[number] + spades[number];
}

bool straight() {
    int a = card_count(0);
    int b = card_count(1);
    int c = card_count(2);
    int d = card_count(3);
    int e = card_count(4);
    if(a == 1 && b == 1 && c == 1 && d == 1 && e == 1) {
        return true;
    }
    
    for(int i = 5; i < 13; ++i) {    
        a = b;
        b = c;
        c = d;
        d = e;
        e = card_count(i);
        
        if(a == 1 && b == 1 && c == 1 && d == 1 && e == 1) {
            return true;
        }
    }
    
    return card_count(0) == 1 && b == 1 && c == 1 && d == 1 && e == 1;
}

void analyze() {
    // FOUR OF A KIND, FULL HOUSE, TWO PAIR
    int old_cnt = 0;
    
    for(int i = 0; i < 13; ++i) {
        int cnt = card_count(i);
        if(cnt == 4) {
            puts("FOUR OF A KIND");
            return;
        }
        if(cnt == 3) {
            if(old_cnt == 2) {
                puts("FULL HOUSE");
                return;
            } else {
                old_cnt = 3;
                continue;
            }
        }
        if(cnt == 2) {
            if(old_cnt == 3) {
                puts("FULL HOUSE");
                return;
            } else if(old_cnt == 2) {
                puts("TWO PAIR");
                return;
            } else {
                old_cnt = 2;
                continue;
            }
        }
    }
    
    // Royal flush
    if(royal_flush(clubs) || royal_flush(hearts) || royal_flush(diamonds) || royal_flush(spades)) {
        puts("ROYAL FLUSH");
        return;
    }
    
    bool is_straight = straight();
    bool is_flush = flush(clubs) || flush(hearts) || flush(diamonds) || flush(spades);
    
    // Straight flush
    if(is_straight && is_flush) {
        puts("STRAIGHT FLUSH");
        return;
    }
    
    // Flush
    if(is_flush) {
        puts("FLUSH");
        return;
    }
    
    // Straight
    if(is_straight) {
        puts("STRAIGHT");
        return;
    }
    
    // Three of a kind
    if(old_cnt == 3) {
        puts("THREE OF A KIND");
        return;
    }
     
    // One pair
    if(old_cnt == 2) {
        puts("ONE PAIR");
        return;
    }
    
    puts("NOTHING");
}

int main() {
    char buf[15];
    while(true) {
        memset(clubs,    0, sizeof(clubs));
        memset(diamonds, 0, sizeof(diamonds));
        memset(hearts,   0, sizeof(hearts));
        memset(spades,   0, sizeof(spades));
        
        if(fgets(buf, 16, stdin) == NULL) {
            return 0;
        }
        
        for(int i = 0; i < 15; i += 3) {
            parse_card(buf[i], buf[i + 1]);
        }
        
        analyze();
    }
}
