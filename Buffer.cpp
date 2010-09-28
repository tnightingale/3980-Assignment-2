#include "Main.h"

VOID AddData(TCHAR newData, PCPARAMS cp) {
    PVOID reallocTest;
    size_t i;

    if (cp->numChars == cp->maxChars - 1) {
        reallocTest = realloc(cp->buffer,cp->maxChars * 2 * sizeof(TCHAR));
        if (reallocTest != NULL) {
            cp->buffer = (TCHAR*)reallocTest;
            cp->maxChars *= 2;
            for (i = cp->numChars + 1; i <= cp->maxChars; i++) {
                cp->buffer[i] = ' ';
            }
        } else {
            //Handle realloc failing
        }
    }

    cp->buffer[cp->numChars++] = newData;

    InvalidateRect(GetActiveWindow(), NULL, TRUE);
    return;
}


