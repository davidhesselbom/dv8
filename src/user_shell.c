#include "utils.h"
#include "kernel.h"
#include "kernel_api.h"
#include "user_shell.h"

#include "program_list.h"

/*
 * ---------------------------------------------------------------------------
 * Globals.
 * ---------------------------------------------------------------------------
 */

/*
 * Buffer for input line.
 */
static char
g_line[1024];

/*
 * Pointers to all arguments.
 */
static char *
g_args[512];

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

/*
 * Skips spaces in the beginning of the string.
 */
static char *
skipwhite(char str[])
{
    while (*str == ' ')
    {
        ++str;
    }
    return str;
}

/*
 * XXXXX
 */
static void
split(char cmd[])
{
    cmd = skipwhite(cmd);
    char *next = strchr(cmd, ' ');
    size_t i = 0;

    while (next)
    {
        *next = '\0';
        g_args[i] = cmd;
        ++i;
        cmd = skipwhite(next + 1);
        next = strchr(cmd, ' ');
    }

    if (*cmd)
    {
        g_args[i] = cmd;
        next = strchr(cmd, '\0');
        *next = '\0';
        ++i;
    }

    g_args[i] = NULL;
}

/*
 * XXXXX
 */
static int
command(void)
{
    uint32_t pid = exec(g_args[0], PROCESS_DEFAULT_PRIORITY);
    if (pid)
    {
        size_t i = 1;
        msg_t *msg = msg_alloc();
        print_str("Executed ");
        print_strln(g_args[0]);
        msg_type_set_argument(msg);
        msg_set_receiver_pid(msg, pid);
        while (g_args[i])
        {
            msg_data_set_string(msg, g_args[i]);
            send_message(msg);
            ++i;
        }
        msg = msg_free(msg);
    }
    else
    {
        print_str("Unknown command ");
        print_strln(g_args[0]);
    }

    return 1;
}

/*
 * XXXXX
 */
static int
do_kill(void)
{
    if (g_args[1])
    {
        uint32_t pid = atoi(g_args[1]);
        if (pid == 0)
        {
            print_strln("USAGE KILL!!!");
        }
        else
        {
            if (!kill(pid))
            {
                print_strln("Failed to kill process");
                return 0;
            }
            return 1;
        }
    }
    else
    {
        print_strln("USAGE KILL!!!");
    }
    return 0;
}

static int
do_priority_change(void)
{
    if (g_args[1] && g_args[2])
    {
        uint32_t pid = atoi(g_args[1]);
        uint32_t new_priority = atoi(g_args[2]);
        if (pid == 0)
        {
            print_strln("USAGE KILL!!!");
        }
        else
        {
            if (!change_priority(pid, new_priority))
            {
                print_strln("Failed to change priority.");
                return 0;
            }
            return 1;
        }
    }
    else
    {
        print_strln("USAGE KILL!!!");
    }
    return 0;
}

static int
do_ls(void)
{
    program_list_print();
    return 1;
}

static int
run(char cmd[])
{
    split(cmd);
    if (g_args[0])
    {
        if (0 == strcmp(g_args[0], "exit"))
        {
            kill_self();
        }
        else if (0 == strcmp(g_args[0], "kill"))
        {
            return do_kill();
        }
        else if (0 == strcmp(g_args[0], "priority"))
        {
            return do_priority_change();
        }
        else if (0 == strcmp(g_args[0], "ls"))
        {
            return do_ls();
        }
        else if (0 == strcmp(g_args[0], "top"))
        {
            top();
            return 1;
        }
        else
        {
            return command();
        }
    }

    return 0;
}

/*
 * XXXXX
 */

void
shell(void)
{
    msg_t *msg = msg_alloc();

    print_strln("Shell. Type 'exit' to exit.");
    while (1)
    {
        print_str("deviate> ");
        read_from_console(msg);
        if (msg_type_is_console_input(msg))
        {
            strcpy(g_line, msg_data_get_string(msg));
            run(g_line);
        }
        else
        {
            print_strln("Shell: could not read input!");
        }
    }

    msg = msg_free(msg);
}
