collection class, highGradeStudents, lowGradeStudents, avgGradeStudents;
set grades, gradesHigh;
int grd;
str student;
class = {"Rafi_Suisa", "Tamar_Even", "Avi_Maoz", "Eli_Kamer", "Shlomit_Raz",
"Haim_Mizrachi", "Moshe_Samocha", "Tali_Raban", "Sharon_Tal", "Gal_Elbaz"};
gradesHigh = [];
highGradeStudents = {};
for (student:class)
{
output "Grade for:" student;
input ">" grd;
grades = grades + grd;
if (grd >= 90)
{
gradesHigh = gradesHigh + grd;
highGradeStudents = highGradeStudents + student;
}
}
if (gradesHigh)
{
output "Number of top grades:" |gradesHigh|;
output "Top Grades are:" gradesHigh;
output "High Grade Students are:" highGradeStudents;
}
input "Low-grade students >" lowGradeStudents;
for (student : lowGradeStudents)
output "Get better next time:" student;
avgGradeStudents = class - highGradeStudents - lowGradeStudents;
output "Students with good grades:" avgGradeStudents;
