clear
clc

input = importdata('input.txt');
input(2)=12;
input(3)=2;

for i=1:4:length(input)
    if input(i)==1
        input(input(i+3)+1) = input(input(i+1)+1) + input(input(i+2)+1);
    end
    
    if input(i)==2
        input(input(i+3)+1) = input(input(i+1)+1) * input(input(i+2)+1);
    end
    
    if input(i)==99
        break;
    end
end

input(1)