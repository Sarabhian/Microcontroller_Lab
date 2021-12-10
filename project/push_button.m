% PUSH BUTTON IMPLEMENTATION USING ARDUINO UNO 

% I will read the data from arduino and will plot it using matlab 
clear all
clear 
clc
global a ; 

a=arduino('COM4' ,'Uno');
Push_button='D8';

configurePin(a,Push_button ,'DigitalInput');

finishup = onCleanup(@() exitprogram(a));
disp('press ctrl + c to end the code');

led='D12';

i=1; x=0;
while(1) 
b=a.readDigitalPin(Push_button);
pause(0.1);       % creates delay of 0.5 sec
disp(b); 
x=[x b];% negation of value is plotted 
plot(x);
ylim([-3 3]);
hold on ;
% drawnow; 
i= i+1;
a.writeDigitalPin(led,~b);
end
hold off ;
a.writeDigitalPin(led,0);


function exitprogram(b)
clear b;
disp('program has exit');
end