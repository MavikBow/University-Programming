var x integer >= 0;
var y integer >= 0;

maximize c: 16.32*x + 3.96*y;

s.t. M1: x <= 2000;
s.t. M2: y <= 6000;
s.t. M3: x + 3*y <= 2500;