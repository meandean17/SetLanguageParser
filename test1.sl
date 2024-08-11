int a, b;
set s1, s2, s3, s4, empty;

s1 = [1, 2, 3, 4, 5];
s2 = [3, 4, 5, 6, 7];
a = 3;
b = 8;

output "Initial sets:";
output "s1: " s1;
output "s2: " s2;
output "empty: " empty;

s1 = s1 + a;
output "s1 after adding 3 (should be unchanged): " s1;

s1 = s1 + b;
output "s1 after adding 8: " s1;

s2 = s2 - a;
output "s2 after removing 3: " s2;

s3 = s1 & s2;
output "s3 (s1 intersection s2): " s3;

s4 = s1 + s2;
output "s4 (s1 union s2): " s4;

s4 = s1 - s2;
output "s4 (s1 difference s2): " s4;

output "Size of s1: " |s1|;
output "Size of empty set: " |empty|;

s3 = s3 + [9, 10];
output "s3 after adding [9, 10]: " s3;

if (s1) {
    output "s1 is not empty";
    output "empty set is empty";

}


s1 = [];
output "s1 after setting to empty set: " s1;