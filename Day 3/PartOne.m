clear 
clc

A=importdata('inputA.txt')';
labelA=importdata('labelA.txt')';
B=importdata('inputB.txt')';
labelB=importdata('labelB.txt')';

panelSize=5983; % minimal size for my input

currentPosX=panelSize;
currentPosY=panelSize;
panelA=zeros(2*panelSize,2*panelSize);
panelA(currentPosX,currentPosY) = 2;

for i=1:length(A)
    if labelA{i}=='R'
        panelA(currentPosX,currentPosY+1:currentPosY+A(i))=1;
        currentPosY=currentPosY+A(i);
    elseif labelA{i}=='U'
        panelA(currentPosX-A(i):currentPosX-1,currentPosY)=1;
        currentPosX=currentPosX-A(i);
    elseif labelA{i}=='L'
        panelA(currentPosX,currentPosY-A(i):currentPosY-1)=1;
        currentPosY=currentPosY-A(i);
    elseif labelA{i}=='D'
        panelA(currentPosX+1:currentPosX+A(i),currentPosY)=1;
        currentPosX=currentPosX+A(i);
    end
    
end

currentPosX=panelSize;
currentPosY=panelSize;
panelB=zeros(2*panelSize,2*panelSize);
panelB(currentPosX,currentPosY) = 2;

for i=1:length(B)
    if labelB{i}=='R'
        panelB(currentPosX,currentPosY+1:currentPosY+B(i))=1;
        currentPosY=currentPosY+B(i);
    elseif labelB{i}=='U'
        panelB(currentPosX-B(i):currentPosX-1,currentPosY)=1;
        currentPosX=currentPosX-B(i);
    elseif labelB{i}=='L'
        panelB(currentPosX,currentPosY-B(i):currentPosY-1)=1;
        currentPosY=currentPosY-B(i);
    elseif labelB{i}=='D'
        panelB(currentPosX+1:currentPosX+B(i),currentPosY)=1;
        currentPosX=currentPosX+B(i);
    end
end

panelOutput=panelA+panelB; % 4 = starting point, 2 = intersection
panelOutput( ~any(panelOutput,2), : ) = [];  % delete empty rows
panelOutput( :, ~any(panelOutput,1) ) = [];  %delete emptycolumns

[intersectionPosX,intersectionPosY]=find(panelOutput==2); % X and Y positions of intersections
[currentPosX,currentPosY]=find(panelOutput==4);% X and Y positions of starting point
manhattanDistance=zeros(1,length(intersectionPosX));

for i=1:length(intersectionPosX)
    manhattanDistance(i)=abs(intersectionPosX(i)-currentPosX)+abs(intersectionPosY(i)-currentPosY);
end

min(manhattanDistance)
