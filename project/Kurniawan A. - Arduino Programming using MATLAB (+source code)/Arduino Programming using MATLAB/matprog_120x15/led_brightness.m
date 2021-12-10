function [] = led_brightness()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
configurePin(board,'D3','PWM');
disp('press Ctr-C to exit');
while 1
    for k = 0:5
        writePWMVoltage(board,'D3',k);
        pause(1);
    end
    for k = 5:-1:0
        writePWMVoltage(board,'D3',k);
        pause(1);
    end   
end
    
end

function exitprogram(b)
clear b;
disp('program has exit');
end

