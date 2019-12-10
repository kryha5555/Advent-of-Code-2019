clear
clc

inputArray = importdata('../input.txt');
output = 0;

while 1
    outputArray = arrayfun(@(x) floor(x/3)-2,inputArray);
    partSum = sum(outputArray(outputArray>0));
      
    if partSum<1
        break;
    end
    
    output = output+partSum;
    inputArray = outputArray;
end

output