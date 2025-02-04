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

#include <gnuradio/io_signature.h>
#include "pn_spreader_b_impl.h"

namespace gr {
  namespace marmote {

    pn_spreader_b::sptr
    pn_spreader_b::make(bool debug, int mask, int seed, int spread_factor)
    {
      return gnuradio::get_initial_sptr (new pn_spreader_b_impl(debug, mask, seed, spread_factor));
    }

    pn_spreader_b_impl::pn_spreader_b_impl(bool debug, int mask, int seed, int spread_factor)
      : gr::sync_interpolator("pn_spreader_b",
		      gr::io_signature::make(1, 1, sizeof (uint8_t)),
		      gr::io_signature::make(1, 1, sizeof (uint8_t)), spread_factor),
      d_debug(debug),
      d_mask(mask),
      d_seed(seed),
      d_sf(spread_factor),
      d_lfsr(mask, seed)
    {
      std::cout << "Spread factor: " << d_sf << std::endl;
        // std::cout << "PN sequence: ";
        // d_lfsr.reset();
        // for (int i = 0; i < spread_factor * 4; i++)
        // {
        //   std::cout << (int)(d_lfsr.get_next_bit());
        // }
        // std::cout << std::endl;

    }

    pn_spreader_b_impl::~pn_spreader_b_impl()
    {
    }

    int
    pn_spreader_b_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const uint8_t *in = (const uint8_t *) input_items[0];
        uint8_t *out = (uint8_t *) output_items[0];
        int nout = 0;

        d_tags.clear();
        get_tags_in_range(d_tags, 0, nitems_read(0), nitems_read(0) + noutput_items/d_sf);

        // std::cout << "Found " << d_tags.size() << " tag(s) ";
        // std::vector<gr_tag_t>::iterator it = d_tags.begin();
        // while (it != d_tags.end())
        // {
          // std::cout << "@" << it->offset << " ";
        //   it++;
        // }
        // std::cout << std::endl;

        d_tags_itr = d_tags.begin();

        for (int i = 0; i < noutput_items/d_sf; i++)
        {
          if (d_tags_itr != d_tags.end() && i == d_tags_itr->offset - nitems_read(0))
          {
            d_lfsr.reset();
            d_tags_itr++;
          }

          for (int j = 0; j < d_sf; j++)
          {
            out[nout++] = in[i] ^ d_lfsr.get_next_bit();
          }
        }


        if (d_debug)
        {
          std::cout << "Spreader input:  ";
          for (int j = 0; j < noutput_items/d_sf; j++)
          {
            std::cout << (int)in[j];
          }
          std::cout << std::endl;

          std::cout << "Spreader output: ";
          for (int i = 0; i < nout; i++)
          {
            std::cout << (int)out[i];
          }
          std::cout << std::endl;
        }

        return nout;
    }

  } /* namespace marmote */
} /* namespace gr */

