function [] = spi_loopback()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
spi = spidev(board, 10);
k = 3;
m = 10;
n = 30;
disp('press Ctr-C to exit');
while 1    
    disp('datain: ');
    dataIn = [k m n];
    disp(dataIn);
    dataOut = writeRead(spi,dataIn);
    disp('dataout: ');
    disp(dataOut);
    pause(1.5);
    k = k + 1;
    m = m + 1;
    n = n + 1;
end
    
end

function exitprogram(b)
clear b;
disp('program has exit');
end

