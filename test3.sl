int a, b;
set s1, s2, s3, s4;

s1 = [1, 2, 3, 4, 5];
s2 = [3, 4, 5, 6, 7];

output "Size of s1: " |s1|;
output "Size of s2: " |s2|;

s3 = s1 & s2;
output "Intersection of s1 and s2: " s3;
