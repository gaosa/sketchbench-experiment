#ifndef DATA_H
#define DATA_H

#include "stdio.h"
#include "stdlib.h"

class Data {
private:
    FILE *fp = NULL;
    int strLen;
    int fileSize = -1;
public:
    void Open(const char *path, const int _strLen = 4) {
        if (fp != NULL) {
            fclose(fp);
            fp = NULL;
        }
        strLen = _strLen;
        if (!(fp = fopen(path, "rb"))) {
			printf("Wrong file path: %s\n", path);
			return;
		}
        fseek(fp, 0L, SEEK_END);
        fileSize = ftell(fp);
        rewind(fp);
    }
    int Size() { return fileSize; }
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