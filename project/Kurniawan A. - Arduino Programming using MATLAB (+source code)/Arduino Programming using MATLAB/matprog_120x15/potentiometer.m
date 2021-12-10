function [] = potentiometer()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
disp('press Ctr-C to exit');
while 1
    analog = readVoltage(board,'A0');
    disp(['analog= ',num2str(analog)]);
    pause(1);    
end
    
end

function exitprogram(b)
clear b;
disp('program has exit');
end

