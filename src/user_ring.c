#include "utils.h"
#include "kernel_api.h"

#include "kernel.h" /* SUPER REMOVE XXXXXXXXX */
#include "msg.h"

#include "user_ring.h"
#include "user_ringnode.h"

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */


void
ring(int number_of_nodes)
{
    int i = number_of_nodes;
    i++;
    
    /* 
    
    int pids[number_of_nodes]; 
    
    int i = 0;
    pids[i] = exec(ringnode, nån_prio);
    
    for (i = 1; i < number_of_nodes; i++)
    {
        pids[i] = exec(ringnode, nån_prio);
        send_int_message(pids[i-1], pids[i]); // skicka pids[i] till pids[i-1]
    }
    
    send_int_message(pids[number_of_nodes], pids[0]); // skicka första nodens pid till sista noden
    
    send_string_message_and_awaken(pids[0], "hej hopp"); // sätt igång ringen
    
    // dö
    */
}