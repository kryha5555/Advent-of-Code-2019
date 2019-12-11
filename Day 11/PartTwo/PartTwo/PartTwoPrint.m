clear
clc

registrationPlate = load('output.txt');

registrationPlate = flip(rot90(registrationPlate));
imshow(registrationPlate,'InitialMagnification','fit');