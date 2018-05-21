#ifndef DATA_H
#define DATA_H

#include "stdio.h"
#include "stdlib.h"

class Data {
private:
    FILE *fp = NULL;
    int strLen;
public:
    void Open(const char *path, const int _strLen) {
        if (fp != NULL) {
            fclose(fp);
            fp = NULL;
        }
        strLen = _strLen;
        if (!(fp = fopen(path, "rb"))) {
			printf("Wrong file path: %s\n", path);
			return;
		}
    }
    ~Data() {
        if (fp != NULL) {
            fclose(fp);
            fp = NULL;
        }
    }
    bool Next(char* str) { return fread(str, sizeof(char), strLen, fp) == strLen; }
    void Reset() { fseek(fp, 0, 0); }
};
#endif