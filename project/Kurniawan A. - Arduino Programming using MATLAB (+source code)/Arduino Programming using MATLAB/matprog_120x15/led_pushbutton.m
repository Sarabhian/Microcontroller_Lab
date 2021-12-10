function [] = led_pushbutton()
pushbutton = 'D8';
led = 'D9';
board = arduino();
finishup = onCleanup(@() exitprogram(board));

configurePin(board,pushbutton,'DigitalInput');
disp('press Ctr-C to exit');
while 1
    state = readDigitalPin(board,pushbutton);
    writeDigitalPin(board,led,state);
    disp(state);
    pause(0.5);    
end
    
end


function exitprogram(b)
clear b;
disp('program has exit');
end

