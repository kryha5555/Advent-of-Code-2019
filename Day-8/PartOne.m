clc
clear

input = fileread('input.txt')-'0';
width = 25;
height = 6;

layersCount = length(input)/width/height;
layers = zeros(height,width,layersCount);
zeroDigits = zeros(1,layersCount);

i=1;
for layer=1:layersCount
    for h=1:height
        for w=1:width
            layers(h,w,layer)=input(i);
            i=i+1;
        end
    end
     zeroDigits(layer) = sum(sum(layers(:,:,layer)==0));
end

[~, index] = min(zeroDigits);
sum(sum(layers(:,:,index)==1))*sum(sum(layers(:,:,index)==2))