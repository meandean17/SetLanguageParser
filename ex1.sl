collection highTech, gaming;
collection software, hardware, industrial;
highTech = {"Apple", "Google", "Microsoft", "Nvidia", "Adobe", "Oracle", "Sap"};
highTech = highTech + {"PayPal", "Nice", "Amdocs", "OpenAI", "Ford", "Mercedes"};
gaming = {"Sony", "Apple", "Microsoft", "Google", "Nintendo", "Playtika"};
software = {"Apple", "Microsoft", "Oracle", "Google", "Sap", "PayPal", "Playtika", "Amdocs", "OpenAI"};
hardware = {"Apple", "Nice", "Sony", "Google", "Cummins", "Nucor", "Microsoft", "Nvidia"};
industrial = {"Caterpillar", "Cummins", "Nucor"};
output "Companies that sell hardware & software:" software & hardware;
collection highSW;
highSW = software & highTech;
if (highSW == software)
output "All software companies are high-tech companies:" highSW;
else
output "Not all software companies are high-tech companies:" highSW;
highSW = highSW + "Playtika";
if (highSW == software)
output "Now all software companies are high-tech companies:" highSW;
else
output "Not all software companies are high-tech companies:" highSW;
output "Companies that do software or hardware:" software + hardware;
if (industrial & software == {})
output "No industrial companies sell software";
output "Companies that sell Hardware but not Gaming Software:" hardware – (software & gaming);
