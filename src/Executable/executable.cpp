#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    std::string cwd = argv[0];
    if (cwd.empty()) return 1;
    cwd.erase(cwd.rfind(
#ifdef _WIN32
        '\\'
#else
        '/'
#endif
        ));
    cwd +=
#ifdef _WIN32
        '\\';
#else
        '/';
#endif

    chdir(cwd.c_str());

    pid_t pid = fork();
    if (pid == 0) { /* child process */
        execv("./KurcEngine.keng", argv);
        exit(127);          /* only if execv fails */
    } else {                /* pid!=0; parent process */
        waitpid(pid, 0, 0); /* wait for child to exit */
    }

    return 0;
}