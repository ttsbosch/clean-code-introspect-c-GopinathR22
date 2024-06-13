char** splitDelimeterFromGivenString(const char* str, char delimiter) {
    int totaldelimeter = 0;
    const char* StringPtr = str;
    while (*StringPtr != '\0') {
        if (*StringPtr++ == delimiter) {
            totaldelimeter++;
        }
    }

    char** StringDuplicationBuff = (char**)malloc(sizeof(char*) * (count + 2));
    int StringIndex = 0;
    StringPtr = str;
    char* StringBuffwithoutDelimiter = (char*)malloc(strlen(str) + 1);
    int StringPosition = 0;
    while (*StringPtr != '\0') {
        if (*StringPtr == delimiter) {
            StringBuffwithoutDelimiter[StringPosition] = '\0';
            StringDuplicationBuff[StringIndex++] = strdup(StringBuffwithoutDelimiter);
            StringPosition = 0;
        } else {
            StringBuffwithoutDelimiter[StringPosition++] = *StringPtr;
        }
        StringPtr++;
    }
    StringBuffwithoutDelimiter[StringPosition] = '\0';
    StringDuplicationBuff[StringIndex++] = strdup(StringBuffwithoutDelimiter);
    StringDuplicationBuff[StringIndex] = NULL;
    free(StringBuffwithoutDelimiter);
    return StringDuplicationBuff;
}
