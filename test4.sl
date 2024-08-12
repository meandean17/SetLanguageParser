set s1;
s1 = [1, 2, 4, 3];
if (|s1| > 5)
    output "set is of size bigger than 5";
else
    output "set is smaller than 5";

if (|s1 - 2 - 1 - 3 - 4|)
    output "set is not empty";
else
    output "set is empty";