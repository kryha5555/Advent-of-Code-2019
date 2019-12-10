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
    twoAdjacent = 0;
    
    for j=2:length(number)
        if number(j-1) > number(j)
            increasing = 0;
            break;
        end   
    end
    
    for j=2:length(number)
        if number(j-1) == number(j)
             twoAdjacent = 1;
             break;
        end   
    end
    
    if increasing && twoAdjacent
         passwords = passwords+1;
            numbers=[numbers, i];
    end
end

passwords