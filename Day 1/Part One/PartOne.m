clear
clc

inputArray = importdata('../input.txt');

outputArray = arrayfun(@(x) floor(x/3)-2,inputArray);

output = sum(outputArray)