function [] = sensing()
board = arduino();
disp('press Ctr-C to exit');
h = figure(1);
finishup = onCleanup(@() exitprogram(board,h));

PCF8591 = '0x48';
PCF8591_ADC_CH0 = '40'; % thermistor
PCF8591_ADC_CH1 = '41'; % photo-voltaic
PCF8591_ADC_CH3 = '43'; % potentiometer
i2c = i2cdev(board,PCF8591);

hLine1 = line(nan, nan, 'Color','red'); 
hLine2 = line(nan, nan, 'Color', 'blue');
hLine3 = line(nan, nan, 'Color', 'black'); 
i = 0;
while 1
    thermistor = read_adc(i2c,hex2dec(PCF8591_ADC_CH0));
    pause(0.5);
    photo = read_adc(i2c,hex2dec(PCF8591_ADC_CH1));
    pause(0.5);
    potentiometer = read_adc(i2c,hex2dec(PCF8591_ADC_CH3));
    pause(0.5);
    
    x1 = get(hLine1, 'XData');
    y1 = get(hLine1, 'YData');
    x2 = get(hLine2, 'XData');
    y2 = get(hLine2, 'YData');
    x3 = get(hLine3, 'XData');
    y3 = get(hLine3, 'YData');
    
    x1 = [x1 i];
    y1 = [y1 thermistor];    
    x2 = [x2 i];
    y2 = [y2 photo];    
    x3 = [x3 i];
    y3 = [y3 potentiometer];

    set(hLine1, 'XData', x1, 'YData', y1); 
    set(hLine2, 'XData', x2, 'YData', y2); 
    set(hLine3, 'XData', x3, 'YData', y3); 
    i = i + 1;
    pause(1);
end

end

function adc = read_adc(dev,config)
write(dev,config);
read(dev, 1);
out = read(dev, 1);
adc = out;
end

function exitprogram(b,h)
clear b;
close(h);
disp('program has exit');
end

