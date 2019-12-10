clear
clc

inputOriginal = importdata('input.txt');
found = 0;

for noun=0:99
    for verb=0:99
        input = inputOriginal;
        input(2)=noun;
        input(3)=verb;
        
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
        
        if input(1)==19690720
            found = 1;
            break;
        end
    end
    
    if found
        break;
    end
end

noun
verb
100*noun+verb