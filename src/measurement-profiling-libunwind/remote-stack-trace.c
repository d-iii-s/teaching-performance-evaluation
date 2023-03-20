#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include <libunwind-ptrace.h>


void print_stack (pid_t pid) {
    unw_addr_space_t address_space;
    void *remote_context;
    unw_cursor_t cursor;
    unw_word_t ip;
    unw_word_t sp;
    char name [256];
    unw_word_t offset;

    address_space = unw_create_addr_space (&_UPT_accessors, 0);
    remote_context = _UPT_create (pid);
    int init_remote_status = unw_init_remote (&cursor, address_space, remote_context);
    assert (init_remote_status == 0);

    int depth = 0;
    while (unw_step (&cursor) > 0) {
        unw_get_reg (&cursor, UNW_REG_IP, &ip);
        unw_get_reg (&cursor, UNW_REG_SP, &sp);
        unw_get_proc_name (&cursor, name, sizeof (name), &offset);
        for (int space = 0 ; space < depth ; space ++) printf (" ");
        printf ("%s+%lx IP %lx SP %lx\n", name, offset, ip, sp);
        depth ++;
    }

    _UPT_destroy (remote_context);
}


int main (int argc, char *argv []) {
    assert (argc == 2);
    pid_t pid = atoi (argv [1]);

    long ptrace_attach_status = ptrace (PTRACE_ATTACH, pid, 0, 0);
    assert (ptrace_attach_status == 0);
    int status_wait;
    int status_pid;
    status_pid = waitpid (pid, &status_wait, 0);
    assert (status_pid == pid);
    assert (WIFSTOPPED (status_wait));

    print_stack (pid);

    long ptrace_detach_status = ptrace (PTRACE_DETACH, pid, 0, 0);
    assert (ptrace_detach_status == 0);

    return (0);
}
