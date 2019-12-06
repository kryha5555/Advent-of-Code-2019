clear
clc

input = importdata('input.txt')';
[parents,children]=deal(strings(size(input))); % declare empty arrays of strings
for i=1:length(input)
    parents(i) = input{i}(1:3); % split input into parents part
    children(i)= input{i}(5:7); %             and children part
end

G = graph; % create new graph
for i=1:length(parents)
    G = addedge(G,parents(i),children(i)); % add edge to graph G between each partent and children
end

[~,pathLength] = shortestpath(G,"YOU","SAN"); % find length of shortest path between YOU and SAN children, ignoring first output
totalLength = pathLength-2 % subtract 2 to get length between objects YOU and SAN are orbiting
