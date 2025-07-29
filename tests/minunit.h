#undef NDEBUG     //强制启用调试模式（即使编译时定义了NDEBUG），确保dbg.h中的debug宏生效，测试期间输出调试信息。
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <lcthw/dbg.h>
#include <stdlib.h>
//在测试套件函数中初始化错误消息变量，用于存储测试失败的信息。
#define mu_suite_start() char *message = NULL

// 验证条件test，若为假则记录错误信息并返回（终止当前测试函数）
#define mu_assert(test, message) if (!(test)) {\
    log_err(message); return message; }

// 运行测试宏
#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    (void)argc; \
    debug("----- RUNNING: %s", argv[0]);\
    printf("----\nRUNNING: %s\n", argv[0]);\
    char *result = name();\
    if (result != 0) {\
        printf("FAILED: %s\n", result);\
    }\
    else {\
        printf("ALL TESTS PASSED\n");\
    }\
    printf("Tests run: %d\n", tests_run);\
    exit(result != 0);\
}

int tests_run;

#endif // _minunit_h
