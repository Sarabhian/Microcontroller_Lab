board = arduino();
address = scanI2CBus(board,0); % uno = 0
disp(['i2c address: ', address]);

clear board;