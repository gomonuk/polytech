#include <systemc.h>

#include "i2c_controller_tb.h"

void i2c_controller_tb::stimuli() {
    rst = 1;
    i2c_scl_m = 1;
    i2c_sda_m = 1;

    wait(100, SC_NS);
    rst = 0;
    addr = 42;
    data_in = 42;
    rw = 0;
    valid = 1;

    wait(10, SC_NS);
    valid = 0;
    wait(100, SC_NS);
    i2c_scl_m = 0;
    i2c_sda_m = 0;
    wait(10, SC_NS);
    i2c_scl_m = 1;
    wait(20, SC_NS);
    i2c_sda_m = 1;
    wait(500, SC_NS);}