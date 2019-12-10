clc
clear

inputChar = importdata('input.txt');
input = zeros(length(inputChar),length(inputChar{1}));
output = zeros(size(input));

for w = 1:length(input)
    for h = 1:length(input)
        if inputChar{w}(h) == '#'
            input(w,h) = 1; % replace #'s with 1 and .'s with 0
        end
    end
end

for y_0 = 1:length(input) 
    for x_0 = 1:length(input) 
        if input(y_0,x_0) == 1 % for each '1' in input table 
            totalForPoint = zeros(size(input)); 
            for y_1 = 1:length(input)
                for x_1 = 1:length(input)
                    if input(y_1,x_1) == 1 % for each '1' in input table  
                        if y_0 ~= y_1 || x_0 ~= x_1 % that is not '1' from 5 lines above
                            dy = y_1 - y_0; % distance between two '1's
                            dx = x_1 - x_0; 
                            divisor = gcd(dy,dx); % greatest common divisor of distances by axis
                            dy_adj = dy/divisor; % adjusted step in direction of axis
                            dx_adj =dx/divisor;
                            
                            it = divisor+1; % iterations count
                            mask = zeros(size(input)); % 0 if detected, 1 if not
                            
                            while((y_0+it*dy_adj <= length(input) && y_0+it*dy_adj > 0) && (x_0+it*dx_adj <= length(input)&& x_0+it*dx_adj >0)) % while next point is inside desired area
                                mask(y_0+it*dy_adj,x_0+it*dx_adj) = 1; % set point as not being detected
                                it = it+1;
                            end
                            
                            inputMasked = input.*mask; % apply mask to input
                            totalForPoint = totalForPoint + inputMasked; % sum input with applied masks for each '1' besides the one considered
                        end
                    end
                end
            end
            
            output(y_0,x_0) = sum(sum(~totalForPoint & input))-1; % get sum of detected '1's for each '1'
        end
    end
end

[Y,X] = find(output == max(max(output)));
fprintf('Best -> (%d, %d) = %d\n', Y-1, X-1, max(max(output))); 
save output X Y % save coordinates for part two