clc
clear

input = fileread('input.txt')-'0';
goal = 100;

offset = str2double(char(input(1:7)+'0')); % take first 7 digits as offset
input = repmat(input,1,10000); % replicate input 10k times
input = input(offset+1:end); % take only significant part

for phase=1:goal
    next = zeros(size(input));
    prev = 0; % value of previous digit, 0 as initial
    for position = length(input):-1:1 % for each digit of current phase, reverse order
        % for last digit, pattern is all zeros and 1 in last place
        % so last digit in current phase is the same as in previous phase
        % for second-to-last digit, pattern is all zeros and two 1's in the end
        % so second-to-last digit in current phase is sum of (this digit and digit on its right side) in previous phase, taking mod10 of sum
        % for n-th digit, pattern is all zeros and n 1's in the end
        % so n-th digit in current phase is sum of (this digit and all digits on its right side) in previous phase, taking mod10 of sum
        next(position) = mod(input(position)+prev,10);
        prev = next(position); % sum of all previous digits for digit n is just digit n-1, considering mod10
    end
    input = next;
end

str2double(char(input(1:8)+'0'))