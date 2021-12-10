function [] = led_rgb()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
configurePin(board,'D3','PWM');
configurePin(board,'D5','PWM');
configurePin(board,'D6','PWM');
disp('press Ctr-C to exit');
while 1
    disp('red');
    write_rgb(board,0,1,1); % red    
    pause(1);
    
    disp('green');
    write_rgb(board,1,0,1); % green    
    pause(1);
    
    disp('blue');
    write_rgb(board,1,1,0); % blue    
    pause(1);
    
    disp('yellow');
    write_rgb(board,0,0,1); % yellow    
    pause(1);
    
    disp('purple');
    write_rgb(board,0.3,1,0.3); % purple    
    pause(1);
    
    disp('aqua');
    write_rgb(board,1,0,0); % aqua    
    pause(1);
end
    
end

% testing for Arduino Uno
function write_rgb(board,r,g,b)
writePWMDutyCycle(board,'D3',r);
writePWMDutyCycle(board,'D5',g);
writePWMDutyCycle(board,'D6',b);
end

function exitprogram(b)
clear b;
disp('program has exit');
end

