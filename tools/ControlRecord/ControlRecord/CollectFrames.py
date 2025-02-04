from optparse import OptionParser

import sys

import tools.FileSource     as FS
import tools.DSPConfig      as conf
import tools.GenerateData   as GD
import tools.FrameConfig    as FC


parser = OptionParser()
parser.add_option("-i", "--input", dest="inputfileordir",
                  help="Input binary file or directory containing binary files <FILEORDIRNAME> (default %default)", metavar="FILEORDIRNAME", default="input.bin")


################################################################################
if __name__ == "__main__":
    (options, args) = parser.parse_args()

    DSPconf = conf.DSPconf_t()
    FrameConf = FC.Frameconf_t()

    Display_N = 0
    MF_hist_len = 0


    Source = FS.FileSource(options.inputfileordir)
    dg = GD.DataGenerator(Source, DSPconf, Display_N, MF_hist_len)

    while True :
        #####################################
        # Get all the data
        dg.tf.ClearFromBeginning( dg.tf.byte_buff_len )
        
        dg.GetTHFilteredData(stop_after_each = True)

        if dg.tf.byte_buff_len == 0 :
            sys.exit(0)

        #####################################
        # Write data to file
        f = open('./collect_%d.bin'%dg.tf.frame_cnt[0], 'wb')

    
        frame_starts = list(dg.tf.frame_starts)
        frame_starts.append(dg.tf.byte_buff_len)

        #print "len(frames_starts) : %d"%len(frame_starts)
        #print "dg.tf.frame_cnt.size : %d"%dg.tf.frame_cnt.size

        for ii in xrange(len(frame_starts) - 1) :

            FrameConf.START_OF_FRAME.tofile(f)
            FrameConf.DATA_FRAME_ID.tofile(f)

            dg.tf.frame_cnt[ii].newbyteorder('B').tofile(f)

            dg.tf.byte_buff[frame_starts[ii]:frame_starts[ii+1]].tofile(f)
                
        f.close()