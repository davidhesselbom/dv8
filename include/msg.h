#ifndef MSG_H
#define MSG_H

#include "utils.h"

/*
 * ---------------------------------------------------------------------------
 * Types.
 * ---------------------------------------------------------------------------
 */

/*
 * Determines the type of the message.
 */
typedef enum
{
    MSG_TYPE_INVALID = 0,
    MSG_TYPE_ARGUMENT,
    MSG_TYPE_CONSOLE_INPUT,
    MSG_TYPE_SUPERVISOR_NOTICE_STATE,
    MSG_TYPE_SUPERVISOR_NOTICE_ID
} msg_type_t;

/*
 * Determines the type of data the message contains.
 */
typedef enum
{
    MSG_DATA_TYPE_INVALID = 0,
    MSG_DATA_TYPE_INTEGER,
    MSG_DATA_TYPE_STRING
} msg_data_type_t;

/*
 * Message used for inter-process communication.
 */
typedef struct msg_ msg_t;
struct msg_
{
    msg_type_t type;
    msg_data_type_t data_type;
    union
    {
        int32_t integer;
        char    string[CONSOLE_INPUT_MAX_LENGTH];
    } data;

    uint32_t sender_pid;
    uint32_t receiver_pid;
    uint32_t priority;

    /* Internal freelist pointer. */
    msg_t *next_free;
};

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

/*
 * Returns a free message, or NULL if none free.
 */
msg_t *
msg_alloc(void);

/*
 * Releases a message back to the system. Always returns NULL, to make it easy
 * to avoid dangling pointers by simply using the return value in an
 * assignment.
 */
msg_t *
msg_free(msg_t *msg);

/*
 * Returns the number of free messages in the system.
 */
size_t
msg_num_free(void);

/*
 * Copies a message, byte for byte.
 */
void
msg_copy(msg_t *dst, const msg_t *src);

/*
 * Zeroes a message and sets its type to invalid.
 */
msg_t *
msg_zero(msg_t *msg);

/*
 * Comparison function for messages. Used by generic data structures.
 */
int
msg_cmp_priority(const void *pmsg1, const void *pmsg2);

/*
 * Returns true if the message is of the given type. Used by generic data
 * structures.
 */
int
msg_has_type(const void *pmsg, const void *ptype);

/*
 * Returns true if the message is of given type.
 */
int
msg_type_is(const msg_t *msg, msg_type_t type);

/*
 * - set() makes the message be of a type
 */
void msg_set_type(msg_t *msg, msg_type_t type);

/*
 * - is() returns true if the message is of an invalid type
 * - set() makes the message be of an invalid type
 */
int  msg_type_is_invalid(const msg_t *msg);
void msg_type_set_invalid(msg_t *msg);

/*
 * - is() returns true if the message represents an argument
 * - set() makes the message represent an argument
 */
int  msg_type_is_argument(const msg_t *msg);
void msg_type_set_argument(msg_t *msg);

/*
 * - is() returns true if the message represents console input
 * - set() makes the message represent console input
 */
int  msg_type_is_console_input(const msg_t *msg);
void msg_type_set_console_input(msg_t *msg);

/*
 * - set() sets the priority of the message
 * - get() returns the priority of the message
 */
void     msg_set_priority(msg_t *msg, uint32_t priority);
uint32_t msg_get_priority(const msg_t *msg);

/*
 * - set() sets the sender's pid of the message
 * - get() returns the sender's pid of the message
 */
void     msg_set_sender_pid(msg_t *msg, uint32_t sender_pid);
uint32_t msg_get_sender_pid(const msg_t *msg);

/*
 * - set() sets the receiver's pid of the message
 * - get() returns the receiver's pid of the message
 */
void     msg_set_receiver_pid(msg_t *msg, uint32_t receiver_pid);
uint32_t msg_get_receiver_pid(const msg_t *msg);

/*
 * - is() returns true if the data within the message is invalid
 * - set() makes the data within the message be invalid
 */
int  msg_data_is_invalid(const msg_t *msg);
void msg_data_set_invalid(msg_t *msg);

/*
 * - is() returns true if the data within the message is string
 * - set() copies the given string into the message data and sets the
 *     message's data type to string
 * - get() returns the string data of the message, or NULL if the data type is
 *     not string
 */
int         msg_data_is_string(const msg_t *msg);
void        msg_data_set_string(msg_t *msg, const char string[]);
const char *msg_data_get_string(const msg_t *msg);

/*
 * - is() returns true if the data within the message is integer
 * - set() copies the given integer into the message data and sets the
 *     message's data type to integer
 * - get() returns the integer data of the message, or 0 if the data type is
 *     not integer
 */
int  msg_data_is_integer(const msg_t *msg);
void msg_data_set_integer(msg_t *msg, int integer);
int  msg_data_get_integer(const msg_t *msg);

#endif
