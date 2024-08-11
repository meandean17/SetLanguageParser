int a, b, c;
set s1, s2, s3;
collection c1, c2;

a = 10;
b = 5;
c = a + b;

s1 = [1, 2, 3, 4, 5];
s2 = [3, 4, 5, 6, 7];
s3 = s1 & s2;

c1 = {"apple", "banana", "cherry"};
c2 = {"banana", "date", "elderberry"};

output "a + b = " c;
output "Size of s1: " |s1|;
output "Size of s2: " |s2|;
output "Intersection of s1 and s2: " s3;

s1 = s1 + 6;
s2 = s2 - 3;

output "s1 after adding 6: " s1;
output "s2 after removing 3: " s2;

c1 = c1 + "date";
c2 = c2 - "banana";

output "c1 after adding 'date': " c1;
output "c2 after removing 'banana': " c2;

