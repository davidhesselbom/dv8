#include "utils.h"
#include "prio_queue.h"
#include "list.h"
#include "list_node.h"

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

/*
 * Init the queue.
 */
void
prio_init(prio_queue_t *q, compare_func compare, match_func is_match)
{
    list_init(q, compare, is_match);
}

/*
 * Returns true if the queue is empty, false otherwise.
 */
int
prio_is_empty(const prio_queue_t *q)
{
    return list_is_empty(q);
}

/*
 * Returns the length of the queue.
 */
size_t
prio_length(const prio_queue_t *q)
{
    return list_length(q);
}

/*
 * Ordered insert in the prio_queue.
 */
int
prio_enqueue(prio_queue_t *q, void *data)
{
    return list_insert_ordered(q, data);
}

/*
 * Returns the first data of the queue.
 */
void *
prio_dequeue(prio_queue_t *q)
{
    return list_remove_head(q);
}

/*
 * Returns and removes the found data from the queue.
 */
void *
prio_remove(prio_queue_t *q, const void *id)
{
    return list_remove(q, id);
}

void *
prio_remove_head(prio_queue_t *q)
{
    return list_remove_head(q);
}

void *
prio_remove_from_head(prio_queue_t *q, const void *id)
{
    return list_remove_from_head(q, id);
}

void *
prio_remove_from_foot(prio_queue_t *q, const void *id)
{
    return list_remove_from_foot(q, id);
}

/*
 * Returns, but does not remove, the first item from the end of the queue that
 * matches the given id.
 */
void *
prio_find(const prio_queue_t *q, const void *id)
{
    return list_find(q, id);
}

void *
prio_find_head(const prio_queue_t *q)
{
    return list_find_head(q);
}

void *
prio_find_from_head(const prio_queue_t *q, const void *id)
{
    return list_find_from_head(q, id);
}

void *
prio_find_from_foot(const prio_queue_t *q, const void *id)
{
    return list_find_from_foot(q, id);
}

void
prio_iter_reset(prio_queue_t *q)
{
    list_iter_reset(q);
}

int
prio_iter_has_next(const prio_queue_t *q)
{
    return list_iter_has_next(q);
}

void *
prio_iter_next(prio_queue_t *q)
{
    return list_iter_next(q);
}
