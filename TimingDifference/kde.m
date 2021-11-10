x = 100:250;
[f] = ksdensity(s1,x,'Support','positive','Bandwidth',0.05);
plot(x,f);
hold on;
[f] = ksdensity(s0,x,'Support','positive','Bandwidth',0.05);
plot(x,f);
hold on;
axis([130,250,0,0.04]);