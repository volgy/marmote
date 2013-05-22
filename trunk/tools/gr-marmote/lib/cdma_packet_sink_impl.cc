/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "cdma_packet_sink_impl.h"

namespace gr {
  namespace marmote {

    cdma_packet_sink::sptr
    cdma_packet_sink::make(bool debug)
    {
      return gnuradio::get_initial_sptr (new cdma_packet_sink_impl(debug));
    }

    cdma_packet_sink_impl::cdma_packet_sink_impl(bool debug)
      : gr_block("cdma_packet_sink",
		      gr_make_io_signature(0, 0, 0),
		      gr_make_io_signature(0, 0, 0)),
        d_debug(debug)
    {
      message_port_register_in(pmt::mp("in"));
      set_msg_handler(pmt::mp("in"), boost::bind(&cdma_packet_sink_impl::process_packet, this, _1));
    }

    cdma_packet_sink_impl::~cdma_packet_sink_impl()
    {
    }

    void cdma_packet_sink_impl::process_packet(pmt::pmt_t pkt)
    {
      if (pmt::pmt_is_blob(pkt))
      {
        std::cout << "Processing packet... [not implemented yet]" << std::endl;
      }
      else
      {
        std::cerr << "@cdma_packet_sink_impl::process_packet: unexpected PMT type" << std::endl;
        assert(false);
      }
    }

    // void
    // cdma_packet_sink_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    // {
    //     /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    // }

    // int
    // cdma_packet_sink_impl::general_work (int noutput_items,
    //                    gr_vector_int &ninput_items,
    //                    gr_vector_const_void_star &input_items,
    //                    gr_vector_void_star &output_items)
    // {
    //     const float *in = (const float *) input_items[0];
    //     float *out = (float *) output_items[0];

    //     // Do <+signal processing+>
    //     // Tell runtime system how many input items we consumed on
    //     // each input stream.
    //     consume_each (noutput_items);

    //     // Tell runtime system how many output items we produced.
    //     return noutput_items;
    // }

  } /* namespace marmote */
} /* namespace gr */
