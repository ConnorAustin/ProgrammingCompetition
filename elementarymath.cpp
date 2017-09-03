#include <cstdio>

int A[2500];
int B[2500];
int answers[2500];
char ops[2500];

int pairs;

int find(int val) {
    for(int p = 0; p < pairs; ++p) {
        if(answers[p] == val) {
            return p;
        }
    }
    return -1;
}

bool fix(int index) {
    int a = A[index];
    int b = B[index];    
    char op = ops[index];
    
    if(op == '+')
    {
        int mult_index = find(a * b);
        if(mult_index == -1) 
        {
            answers[index] = a * b;
            ops[index] = '*';
            return true;
        }
        
        int sub_index = find(a - b);
        if(sub_index == -1) 
        {
            answers[index] = a - b;
            ops[index] = '-';
            return true;
        }
        return false;
    }
    else if(op == '*')
    {
        int sub_index = find(a - b);
        if(sub_index == -1) 
        {
            answers[index] = a - b;
            ops[index] = '-';
            return true;
        }
        return false;
    }
    else return false;
}

bool stuff() 
{
    for(int p = 0; p < pairs; ++p) {
        int a = A[p];
        int b = B[p];
        
        int plus_index = find(a + b);
        
        if(plus_index == -1) {
            answers[p] = a + b;
            ops[p] = '+';
        } 
        else 
        {
            int mult_index = find(a * b);
            
            if(mult_index == -1) 
            {
                answers[p] = a * b;
                ops[p] = '*';
            }
            else 
            {
                int minus_index = find(a - b);
                
                if(minus_index == -1) 
                {
                    answers[p] = a - b;
                    ops[p] = '-';
                }
                else 
                {
                    if(fix(plus_index)) 
                    {
                        answers[p] = a + b;
                        ops[p] = '+';
                    }
                    else if(fix(mult_index)) 
                    {
                        answers[p] = a * b;
                        ops[p] = '*';
                    }
                    else if(fix(minus_index)) 
                    {
                        answers[p] = a - b;
                        ops[p] = '-';    
                    }
                    else 
                    {
                        puts("impossible");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d\n", &pairs);
    
    for(int p = 0; p < pairs; ++p) 
    {
        scanf("%d %d", &A[p], &B[p]);
    }
    if(stuff()) 
    {
        for(int p = 0; p < pairs; ++p) 
        {
            printf("%d %c %d = %d\n", A[p], ops[p], B[p], answers[p]);
        }
    }
}