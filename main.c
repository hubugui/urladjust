#include <stdio.h>
#include <string.h>

static char *testcases[][2] = {
    {"/index.m3u8", "http://127.0.0.1/index.m3u8"},
    {"/test/../../index0.ts", "http://127.0.0.1/index0.ts"},
    {"/test/../helloworld/../index1.ts", "http://127.0.0.1/index1.ts"},
    {"/test/../../helloworld/xiaohei/../index2.ts"
        , "http://127.0.0.1/helloworld/index2.ts"},
    {"/test/helloworld/xiaohei/../index3.ts"
        , "http://127.0.0.1/test/helloworld/index3.ts"},
    {"/../test/helloworld/xiaohei/../index4.ts"
        , "http://127.0.0.1/test/helloworld/index4.ts"},
    {"/./test/helloworld/xiaohei/../index5.ts"
        , "http://127.0.0.1/./test/helloworld/index5.ts"},
    {"/test/helloworld/xiaohei/../index6.ts"
        , "http://127.0.0.1/test/helloworld/index6.ts"},
    {"/../../test/helloworld/xiaohei/../../../../../../index7.ts"
        , "http://127.0.0.1/index7.ts"},
};

char *url_adjust(char *url, const char *prefix, char *output)
{
    char *ret = output;
    int i = 0, op_point = 0;
    char dotdot = 0;
    char pre_is_dot = 0;

    if (!url || !prefix || !output)
        return NULL;

    /**
     * input:   "/test/../../helloworld/xiaohei/../index2.ts"
     * output:  "/helloworld/index2.ts"},
     * input:   "/../../test/helloworld/xiaohei/../../../../../../index7.ts""
     * output:  "/index7.ts"},
     */
    while (url[i] != '\0') {
        if (url[i] == '.') {
            if (pre_is_dot) {
                dotdot = 1;
                pre_is_dot = 0;
            } else
                pre_is_dot = 1;
        } else
            pre_is_dot = 0;
        output[op_point++] = url[i];

        if (dotdot) {
            op_point = 0;
            dotdot = 0;
        }

        i++;
    }

    output[op_point++] = '\0';
    return ret;
}

int main(int argc, char **argv)
{
    int ret = 0;
    const char *prefix = "http://127.0.0.1";
    char buffer[4096] = {0};

    for (int i = 0; i < sizeof(testcases) / (2 * sizeof(char *)); i++) {
        char *output = url_adjust(testcases[i][0], prefix, buffer);

        if (output && strcmp(output, testcases[i][1]) == 0)
            printf("%02d pass, input=\"%s\", output=\"%s\"\n"
                    , i, testcases[i][0], testcases[i][1]);
        else
            printf("%02d fail, input=\"%s\", output=\"%s\", answer=\"%s\"\n"
                    , i, testcases[i][0], output ? output : "NULL"
                    , testcases[i][1]);
    }
    
    return ret;
}