close all; clear all;
R=47000;
C=1000*10^-6;
V0=5;

for t=0:(4*R*C)
   v(t+1)=V0-V0*exp(-t/(R*C));
end

plot(linspace(0,4*R*C,length(v)),v)