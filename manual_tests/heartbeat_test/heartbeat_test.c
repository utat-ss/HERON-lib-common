/*
Full test of the heartbeat system
*/

#include <heartbeat/heartbeat.h>
#include <uart/uart.h>

// -----------------------------------------------------------------------------
// Change these values before re-uploading to a new board

// NOTE: Change this variable before re-compiling and re-uploading to match the
// subsystem of the board you are uploading to
#define SELF_ID HB_OBC
// #define SELF_ID HB_EPS
// #define SELF_ID HB_PAY

// Uncomment to ignore received pings and not respond
// #define IGNORE_PINGS

// Uncomment to overwrite hb_ping_period_s (if IGNORE_PINGS is enabled, recommended to set this high so it doesn't reset the other board)
// #define PING_PERIOD 100

// Uncomment for more debug logging
// #define DEBUG_LOG
// -----------------------------------------------------------------------------


void print_bool(char* str, bool val) {
    if (val) {
        print("%s: true\n", str);
    }
}


int main() {
    init_uart();
    init_uptime();
    init_can();
    print("\n\n\nStarting heartbeat test\n");

    if (SELF_ID == HB_OBC) {
        hb_ping_period_s = 15;
    } else if (SELF_ID == HB_EPS) {
        hb_ping_period_s = 20;
    }

#ifdef PING_PERIOD
    // optional override
    hb_ping_period_s = PING_PERIOD;
#endif

#ifndef IGNORE_PINGS
    print("Initializing heartbeat...\n");
    init_hb(SELF_ID);
    print("Done init\n");
#else
    print("Skipped initializing heartbeat\n");
#endif

    print("hb_self_id = ");
    if (hb_self_id == HB_OBC) {
        print("OBC");
    } else if (hb_self_id == HB_EPS) {
        print("EPS");
    } else if (hb_self_id == HB_PAY) {
        print("PAY");
    }
    print("\n");

    print("hb_ping_period_s = %lu\n", hb_ping_period_s);

    print("Starting main loop\n");

    while (1) {

#ifdef DEBUG_LOG
        print_bool("hb_send_obc_ping", hb_send_obc_ping);
        print_bool("hb_send_eps_ping", hb_send_eps_ping);
        print_bool("hb_send_pay_ping", hb_send_pay_ping);
        print_bool("hb_received_obc_resp", hb_received_obc_resp);
        print_bool("hb_received_eps_resp", hb_received_eps_resp);
        print_bool("hb_received_pay_resp", hb_received_pay_resp);       
        print_bool("hb_send_obc_resp", hb_send_obc_resp);
        print_bool("hb_send_eps_resp", hb_send_eps_resp);
        print_bool("hb_send_pay_resp", hb_send_pay_resp);
#endif

        run_hb();
    }
    
    return 0;
}