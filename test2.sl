collection c1, c2, c3;
int a;

c1 = {"apple", "banana", "cherry"};
c2 = {"banana", "date", "elderberry"};
a = 5;

output "Initial collections:";
output "c1: " c1;
output "c2: " c2;

c3 = c1 + c2;
output "c3 (c1 union c2): " c3;

c1 = c1 - "apple";
output "c1 after removing 'apple': " c1;

c2 = c2 + "fig";
output "c2 after adding 'fig': " c2;

if (c1) {
    output "c1 is not empty";
    output "c1 has " |c1| " elements";
} else {
    output "c1 is empty";
}
