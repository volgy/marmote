from optparse import OptionParser

from gnuradio import gr
import gnuradio.extras

import GNUradio_blocks_pure_python.FrameToFileSink_numtag   as FrameTFS


import frame_source.frame_source_swig as fs


parser = OptionParser()
parser.add_option("-i", "--input", dest="inputfileordir",
                  help="Input binary file or directory containing binary files <FILEORDIRNAME> (default %default)", metavar="FILEORDIRNAME", default="input.bin")


################################################################################
class Top_Block(gr.top_block):

    def __init__(self, FileOrDir):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 750e3


        ##################################################
        # Blocks
        ##################################################
        self.frame_source = fs.frame_source_ss(FileOrDir)
        self.frame_sink = FrameTFS.FrameToFileSink()
        self.gr_interleave = gr.interleave(gr.sizeof_short*1)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.frame_source, 0), (self.gr_interleave, 0))
        self.connect((self.frame_source, 1), (self.gr_interleave, 1))

        self.connect((self.gr_interleave, 0), (self.frame_sink, 0))



################################################################################
if __name__ == "__main__":
    (options, args) = parser.parse_args()

    tb = Top_Block(options.inputfileordir)

    tb.run()