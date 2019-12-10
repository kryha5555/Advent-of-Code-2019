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

panelOutput=panelA+panelB;
[intersectionPosX,intersectionPosY]=find(panelOutput==2);% X and Y positions of intersections

lengthOfA = zeros(1,length(intersectionPosX)); % vector of lengths from starting point to intersections over wire A
lengthOfB = zeros(1,length(intersectionPosX)); % vector of lengths from starting point to intersections over wire B 

for k=1:length(intersectionPosX) % looping over intersections
    currentPosX = panelSize;
    currentPosY = panelSize;
    current = [currentPosX,currentPosY];
    stepsCount = 0; % steps from starting point to intersection
    intersectionFound = 0;
    
    for i=1:length(A) % looping over segments of first wire
        if intersectionFound == 1
            break;
        end
        
        if labelA{i}=='R'
            for j=1:A(i) % looping over length of segment A(i)
                current(2) = current(2)+1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfA(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelA{i}=='U'
            for j=1:A(i) % looping over length of segment A(i)
                current(1) = current(1)-1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfA(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelA{i}=='L'
            for j=1:A(i) % looping over length of segment A(i)
                current(2) = current(2)-1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfA(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelA{i}=='D'
            for j=1:A(i) % looping over length of segment A(i)
                current(1) = current(1)+1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfA(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
        end
    end
end

lengthOfA; % vector of lengths from starting point to intersections over wire A

for k=1:length(intersectionPosX) % looping over intersections
    currentPosX = panelSize;
    currentPosY = panelSize;
    current = [currentPosX,currentPosY];
    stepsCount = 0; % steps from starting point to intersection
    intersectionFound = 0;
    
    for i=1:length(B) % looping over segments of second wire
        if intersectionFound == 1
            break;
        end
        
        if labelB{i}=='R'
            for j=1:B(i) % looping over length of segment B(i)
                current(2) = current(2)+1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfB(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelB{i}=='U'
            for j=1:B(i) % looping over length of segment B(i)
                current(1) = current(1)-1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfB(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelB{i}=='L'
            for j=1:B(i) % looping over length of segment B(i)
                current(2) = current(2)-1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfB(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
            
        elseif labelB{i}=='D'
            for j=1:B(i) % looping over length of segment B(i)
                current(1) = current(1)+1;
                stepsCount = stepsCount+1;
                if current == [intersectionPosX(k), intersectionPosY(k)]
                    lengthOfB(k) = stepsCount;
                    intersectionFound = 1;
                    break;
                end
            end
        end
    end
end

lengthOfB; % vector of lengths from starting point to intersections over wire B

lengthTotal = lengthOfA + lengthOfB; % total number of steps to intersection over both wires

min(lengthTotal)