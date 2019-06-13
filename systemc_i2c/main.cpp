#include <systemc.h>

#include "i2c_controller_tb.h"
#include "i2c_controller.h"

int sc_main(int argc,char *argv[])
{
    sc_signal<bool> rst;
    sc_signal<sc_uint<7>> addr;
    sc_signal<sc_uint<8>> data_in;
    sc_signal<bool> valid;
    sc_signal<bool> rw;
    sc_signal<sc_lv<8>> data_out;
    sc_signal<bool> ready;
    sc_signal<sc_logic, SC_MANY_WRITERS> i2c_sda_o;
    sc_signal<sc_logic> i2c_scl_o;


    sc_signal<sc_logic> scl;
    sc_signal<sc_logic> sda;
    sc_trace_file *f_trace;

    i2c_controller_tb tb("tb");

    f_trace = sc_create_vcd_trace_file("waveforms");
    f_trace->set_time_unit(1.0, SC_PS);

    sc_trace(f_trace, *tb.clk, "n_clk");
    sc_trace(f_trace, tb.rst, "reset");
    sc_trace(f_trace, tb.master->i2c_sda_o, "sda_o");
    sc_trace(f_trace, tb.ready, "ready");
    sc_trace(f_trace, tb.master->i2c_scl_o, "scl_o");
    sc_trace(f_trace, tb.addr, "addr");
    sc_trace(f_trace, tb.rw, "rw");
    sc_trace(f_trace, tb.data_in, "data");
    sc_trace(f_trace, tb.valid, "valid");
    sc_trace(f_trace, tb.master->i2c_clk, "clk");
    sc_trace(f_trace, tb.master->i2c_scl_o_enable, "i2c_scl_o_enable");
    sc_trace(f_trace, tb.master->sda_out, "sda_out");
    sc_trace(f_trace, tb.master->counter, "counter");
    sc_trace(f_trace, tb.master->write_enable, "write_enable");
    sc_trace(f_trace, tb.master->i2c_sda_m, "sda_m");
    sc_trace(f_trace, tb.master->i2c_scl_m, "scl_m");
    sc_trace(f_trace, tb.master->i2c_sda, "sda");
    sc_trace(f_trace, tb.master->i2c_scl, "scl");
    sc_start(3000, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(f_trace);

    return 0;
}
