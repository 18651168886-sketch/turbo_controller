function ntc_temp = fcn(u)
%#codegen
ntc_res=4095*10000/u-10000;
ntc_temp=abs(1/((log10(complex(ntc_res/10000))/3434)+1/298.15)-273.15);