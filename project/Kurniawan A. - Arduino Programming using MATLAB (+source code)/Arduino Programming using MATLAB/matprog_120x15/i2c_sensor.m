function [] = i2c_sensor()
board = arduino();
finishup = onCleanup(@() exitprogram(board));
disp('press Ctr-C to exit');
PCF8591 = '0x48';
PCF8591_ADC_CH0 = '40'; % thermistor
PCF8591_ADC_CH1 = '41'; % photo-voltaic
PCF8591_ADC_CH3 = '43'; % potentiometer
i2c = i2cdev(board,PCF8591);
disp(['thermistor  ', 'photo  ', 'potentiometer']); 
while 1
    thermistor = read_adc(i2c,hex2dec(PCF8591_ADC_CH0));
    pause(0.5);
    photo = read_adc(i2c,hex2dec(PCF8591_ADC_CH1));
    pause(0.5);
    potentiometer = read_adc(i2c,hex2dec(PCF8591_ADC_CH3));
    pause(0.5);
    disp([thermistor, photo, potentiometer]);        
end
    
end

function adc = read_adc(dev,config)
write(dev,config);
read(dev, 1);
out = read(dev, 1);
adc = out;
end

function exitprogram(b)
clear b;
disp('program has exit');
end

