PartOne % run part one to get coordinates of best location
clc
clear

partOneData = load('output'); % get coordinates
y_0 = partOneData.Y;
x_0 = partOneData.X;

inputChar = importdata('input.txt');
input = zeros(length(inputChar),length(inputChar{1}));
angleTable = [];
output = [];

for w = 1:length(input)
    for h = 1:length(input)
        if inputChar{w}(h) == '#'
            input(w,h) = 1;
        end
    end
end

for y_1 = 1:length(input)
    for x_1 = 1:length(input)
        if input(y_1,x_1) == 1 % for each '1' in input table 
            if y_0 ~= y_1 || x_0 ~= x_1 % that is not best located one
                dy = y_1 - y_0; % distance between two '1's
                dx = x_1 - x_0;
                radius =atan2(dx,-dy); % atan2(x, -y) makes 0 deg. start in the up direction and increases going clockwise
                radiusDeg =  mod(rad2deg(radius),360); % mod 360 adds 360 degrees whenever the result is negative 
                angleTable = [angleTable; y_1 x_1 dy dx radius radiusDeg hypot(dx,dy)]; % save angle and distance to table
            end
        end
    end
end

angleTable = sortrows(angleTable,[6 7],{'ascend' 'descend'}); % sort by radiusDeg ascending, then by distance descending
i = 1;

while(length(output) < 200)
    
    if (angleTable(i,6) ~= angleTable(i+1,6)) % if next angle is not the same as current
        output = [output; angleTable(i,:)]; % append to output
    end
    i=i+1;
end

Y = output(200,1);
X = output(200,2);
fprintf('200th -> (X, Y) = (%d, %d) = %d -> %d\n', X-1, Y-1, input(Y,X), (X-1) * 100 + Y-1);
