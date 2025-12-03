// ✅ EXP-08 – a b c string**

// Language:

// Zero or more a’s

// Exactly one b

// Zero or more c’s
// 👉 Form: a* b c*




#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int state = 0;  // q0 = reading 'a*'

    printf("Enter a string: ");
    scanf("%s", str);

    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];

        switch (state) {

        case 0: // q0: zero or more 'a'
            if (c == 'a')
                state = 0;           // still in a*
            else if (c == 'b')
                state = 1;           // found 'b'
            else if (c == 'c')
                state = 3;           // c before b → invalid
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 1: // q1: after seeing 'b', expecting c* or end
            if (c=='c')
                state = 2;           // entering c*
            else if (c=='a' || c=='b')
                state = 3;           // invalid sequence
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 2: // q2: reading zero or more c
            if (c=='c')
                state = 2;           // continue c*
            else if (c=='a' || c=='b')
                state = 3;           // invalid
            else {
                printf("input invalid\n");
                return 1;
            }
            break;

        case 3: // q3: trap state (invalid string)
            if (c=='a' || c=='b' || c=='c')
                state = 3;
            else {
                printf("input invalid\n");
                return 1;
            }
            break;
        }
    }

    if (state == 1 || state == 2)
        printf("accepted\n");
    else
        printf("rejected\n");

    return 0;
}
