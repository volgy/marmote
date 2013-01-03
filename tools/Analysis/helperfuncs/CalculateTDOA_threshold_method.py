import Onset_Threshold as OT

def CalculateTDOA_threshold_method(y, y2, T, th_cross_level = 0.15) :
	AE_start = []
	AE_start2 = []
	TD_meas = []
	
	for ii in xrange(len(y)) :
		AE_start.append( OT.Onset_Threshold(y[ii], T, th_cross_level ) )
		AE_start2.append( OT.Onset_Threshold(y2[ii], T, th_cross_level ) )
		
		TD_meas.append(AE_start2[-1] - AE_start[-1])
		
	return AE_start, AE_start2, TD_meas
