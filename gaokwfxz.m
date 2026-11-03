H=5; %11 (km)
T0=288.15;
P0=101.325;%kpa
if H>=11
    T1=T0-11*6.5;
    P1=23.385*exp((H-11)*-0.1576932);
else
    T1=T0-H*6.5;
    P1=P0*(1-0.022577*H)^5.25588;
end
x1=[40000 62000];
y1=[2028 7342];
xin=62000;
xcr=xin/sqrt(T1/T0);
ycr=interp1(x1,y1,xcr,'linear','extrap');
y=ycr*sqrt(T1/T0)*(P1/P0);