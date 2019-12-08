clc
clear

input = fileread('input.txt')-'0';
width = 25;
height = 6;

layersCount = length(input)/width/height;
final = zeros(height,width);
final(:,:)=2;

i=1;
for layer=1:layersCount
    for h=1:height
        for w=1:width
            if final(h,w)==2
                final(h,w) = input(i);;
            end            
            i=i+1;
        end
    end
end

imshow(final,'InitialMagnification','fit');