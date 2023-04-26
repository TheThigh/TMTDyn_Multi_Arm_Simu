% 2023.01.22
% This subscript is for testing the intersection set of two or more spaces
% in MATLAB, which could be useful to confirm the impact position in the
% TMTDyn package.

clear all; clc;
t = linspace(0,2*pi,6);
xv = cos(t);
yv = sin(t);
xv = [xv,xv(1)];
yv = [yv,yv(1)];

X = randn(100,1);
Y = randn(100,1);

IN = inpolygon(X, Y, xv, yv);

plot(xv, yv, 'k', X(IN), Y(IN), '*r', X(~IN), Y(~IN), 'ob');