#include "utils.h"
#include "kernel_api.h"
#include "msg.h"

#include "user_man.h"
#include "program_list.h"

static void
jon_birthday(void)
{
    print_strln("");
    print_strln("  _|_|_|  _|_|_|      _|_|    _|_|_|_|_|  _|_|_|_|_|  _|_|_|    _|_|_| ");
    print_strln("_|        _|    _|  _|    _|      _|          _|        _|    _|       ");
    print_strln("_|  _|_|  _|_|_|    _|_|_|_|      _|          _|        _|      _|_|   ");
    print_strln("_|    _|  _|    _|  _|    _|      _|          _|        _|          _| ");
    print_strln("  _|_|_|  _|    _|  _|    _|      _|          _|      _|_|_|  _|_|_|   ");
    print_strln("                                                                       ");
    print_strln("                                                                       ");
    print_strln("                                                                       ");
    print_strln("                        _|    _|_|    _|      _|  _|                   ");
    print_strln("                        _|  _|    _|  _|_|    _|  _|                   ");
    print_strln("                        _|  _|    _|  _|  _|  _|  _|                   ");
    print_strln("                  _|    _|  _|    _|  _|    _|_|                       ");
    print_strln("                    _|_|      _|_|    _|      _|  _|                   ");
    print_strln("");
}

void
man(void)
{
    msg_t msg_struct;
    msg_t *msg = &msg_struct;
    char arg[256];

    read_message_by_type(msg, MSG_TYPE_ARGUMENT, 330);
    if (msg_type_is_invalid(msg))
    {
        jon_birthday();
        return;
    }

    strcpy(arg,msg_data_get_string(msg));

    if (program_list_name_exist(arg))
    {
        print_str(arg);
        print_strln(" works like this");        
        /*get_program_man(arg);*/
    }
    else
    {
        print_strln("No such program exist.");
        return;
    }
}
