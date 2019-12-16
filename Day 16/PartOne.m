clc
clear

input = fileread('input.txt')-'0';
patternBase = [0 1 0 -1];
goal = 100;

for phase=1:goal % for each phase
    temp = zeros(size(input)); % create temp vector
    for digit = 1:length(input) % for each digit in signal
        pattern = repelem(patternBase,digit); % repeat each value of pattern 'digit' times
        pattern = repmat(pattern,1,ceil(length(input)/length(pattern))); % replicate pattern so its size is at least of signal size
        pattern = pattern(2:end); % skip the very first value of pattern
        pattern = pattern(1:length(input)); % cut off last pattern elements so its length equals signal length
        temp(digit) = mod(abs(sum(input.*pattern)),10); % multiply each signal digit with pattern mask, save its abs and mod10 to temp vector
    end
    input = temp; 
end

str2double(char(input(1:8)+'0')) % display first 8 digits