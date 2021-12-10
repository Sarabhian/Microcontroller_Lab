function [] = servo_motor()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
motor = servo(board,'D10');
disp('press Ctr-C to exit');
while 1
    for pos = 0:0.25:1
        disp(['position: ',num2str(pos)]);
        writePosition(motor,pos);
        pause(1);
    end
    for pos = 1:-0.25:0
        disp(['position: ',num2str(pos)]);
        writePosition(motor,pos);
        pause(1);
    end   
end
    
end

function exitprogram(b)
clear b;
disp('program has exit');
end

