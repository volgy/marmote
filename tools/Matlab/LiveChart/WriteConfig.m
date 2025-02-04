function WriteConfig( u, RFInput, RFGain, RFFrequency, DC_Offset_I, DC_Offset_Q, DDCFrequency, Shift )
%WRITECONFIG Summary of this function goes here
%   Detailed explanation goes here

    data = [int8(0) ...
        typecast(swapbytes(uint8(RFInput)),'int8') ...
        typecast(swapbytes(uint32(RFGain)),'int8') ...        
        typecast(swapbytes(uint32(RFFrequency)),'int8') ...
        typecast(swapbytes(int16(DC_Offset_I)),'int8') ... 
        typecast(swapbytes(int16(DC_Offset_Q)),'int8') ... 
        typecast(swapbytes(int32(DDCFrequency)),'int8') ... 
        typecast(swapbytes(uint8(Shift)),'int8')];
    
    fwrite(u, data, 'int8');

end

