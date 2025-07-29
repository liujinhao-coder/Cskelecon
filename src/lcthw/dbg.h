#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG  //调试开关控制  如果你定义了NDEBUG之后编译，没有任何调试信息会输出
// ...：可变参数列表 
// M：格式化字符串参数
#define debug(M, ...)
#else

//它将任何使用debug("format", arg1, arg2)的地方替换成fprintf对stderr的调用。
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

//clean_errno宏用于获取errno的安全可读的版本。
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

//log_err，log_warn和log_info宏用于为最终用户记录信息。
#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

// check会保证条件A为真，否则会记录错误M（带着log_err的可变参数），之后跳到函数的error:区域来执行清理。
#define check(A, M, ...) if(!(A)) {\
    log_err(M, ##__VA_ARGS__); errno=0; goto error; }
//sentinel可以放在函数的任何不应该执行的地方，它会打印错误信息并且跳到error:标签。
//你可以将它放到if-statements或者switch-statements的不该被执行的分支中，比如default。
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")
//用于替代的check_debug宏，它仍然会检查并处理错误，尤其是你并不想报告的普遍错误。
//它里面使用了debug代替log_err来报告错误，所以当你定义了NDEBUG，它仍然会检查并且发生错误时跳出，但是不会打印消息了。
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#endif
