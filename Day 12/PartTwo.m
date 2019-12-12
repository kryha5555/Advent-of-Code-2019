clear
clc

input = regexp(importdata('input.txt'),'-?\d*','Match'); % get digits with signs
positions = str2double(cat(1,input{:}));                 % split into elements of matrix
velocities = zeros(size(positions));
moonsCount = size(positions,1);

initialPositions = positions;
foundPositions = zeros(3,1);
timeStep = 1;

while ~all(foundPositions)
    for firstMoon = 1:moonsCount                % for each moon
        for secondMoon = firstMoon+1:moonsCount % pair with other moons
            for xyz = 1:size(positions,2)       % for each axis
                axisPosition = sign(positions(firstMoon,xyz) -  positions(secondMoon,xyz)); % calculate difference sign
                velocities(firstMoon,xyz) = velocities(firstMoon,xyz) - axisPosition;       % subtract from first velocity
                velocities(secondMoon,xyz) = velocities(secondMoon,xyz) + axisPosition;     % add to second velocity
            end                                                                             % to get them closer to each other
        end
    end
    
    positions = positions + velocities; % update positions
    
    for xyz=1:size(positions,2) % for each axis
        if ~foundPositions(xyz) % if position not found
            if isequal(positions(:,xyz), initialPositions(:,xyz)) % if positions are equal
                foundPositions(xyz) = timeStep+1;                 % save timestep
            end
        end
    end
    
    timeStep = timeStep+1;
end

double(lcm(sym(foundPositions))) % get LCM of positions for all axes