clear
clc

input = importdata('input.txt');
lowerLimit = input(1);
upperLimit = input(2);
passwords = 0;
numbers = [];

for i=lowerLimit:upperLimit
    number = num2str(i);
    increasing = 1;
    adjacent = 0;
    
    for j=2:length(number)
        if number(j-1) > number(j)
            increasing = 0;
            break;
        end
    end
    
    if number(1) == number(2) && number(2) ~= number(3) || number(end) == number(end-1) && number(end-1) ~= number(end-2) % checking for first and last element
        adjacent = 1;
    else
        for j=4:length(number)
            if number(j-2) == number(j-1) && number(j-1) ~= number(j) && number(j-3) ~= number(j-2)
                adjacent = 1;
                break;
            end
        end
    end
    
    if increasing && adjacent
        passwords = passwords+1;
        numbers=[numbers, i];
    end
end

passwords