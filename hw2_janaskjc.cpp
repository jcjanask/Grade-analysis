// Copyright
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;



string convertToLetter(double a) {
int b = static_cast<int>(a);
std::string ret = "";
if (a >= 90.0) ret = "(A";
else if (a >= 80.0) ret = "(B";
else if (a >= 70.0) ret = "(C";
else if (a >= 60.0) ret = "(D";
else
ret = "(F";
std::string extra = "";
if (a >= 100) extra = "+";
else if (b % 10 >= 7.0) extra = "+";
else if (b % 10 <= 3.0 && (b % 10) >= 0.0) extra = "-";

std::string grade = ret + extra + ")";
return grade;
}


void printResults(vector<string> names, map<string, vector<double>> list,
     ostream &os) {
     double grade;
     os << fixed << setprecision(2);
     for (int i = static_cast<int>(list.size() - 1); i >= 0; i--) {
          if (names[i].compare("quiz") == 0 || names[i].compare("lab") == 0)
          grade += list[names[i]][0] * 0.1;
          else if (names[i].compare("midterm") == 0)
          grade += list[names[i]][0] * 0.2;
          else if (names[i].compare("homework") == 0)
          grade += list[names[i]][0] * 0.35;
          else if (names[i].compare("final_exam") == 0)
          grade += list[names[i]][0] * 0.25;
}

        for (const auto& x : list) {
            double tmp = x.second[0] * 100;
        os << x.first << ": " << x.second[0] * 100 << " " <<
            convertToLetter(tmp) << endl;
    }
    os << "Course Grade: " << grade*100 << " " <<
    convertToLetter(grade * 100) << endl;
}




int main(int argc, char *argv[]) {
if (argc > 3) {
std::cerr << "Invalid number of arguments" << endl;
return 1;
}


ifstream input(argv[1]);
ofstream output(argv[2]);

if (!input.good() || !output.good()) {
std::cerr << "File streams are invalid" << endl;
return 1;
}

std::string line;
std::map<string, vector<double>> calc;
vector<string> result;
vector<string> names;

while (getline(input, line)) {
boost::split(result, line, boost::is_any_of(","));
double first = std::stod(result[1]);
double second = std::stod(result[2]);

if (!count(names.begin(), names.end(), result[0])) names.push_back(result[0]);


calc[result[0]].push_back(first);
calc[result[0]].push_back(second);
}


double e;
double bottom;
double avge;
std::string letter;
for (int i = 0; i < static_cast<int>(names.size()); i++) {
  for (int j = 0; j < static_cast<int>(calc[names[i]].size()); j++) {
       if (j % 2 == 0)
       e += calc[names[i]][j];
       else
       bottom += calc[names[i]][j];
}
         avge = e / bottom;
         calc[names[i]].clear();
         calc[names[i]].push_back(avge);
         e = 0;
         bottom = 0;
}
         printResults(names, calc, cout);
         printResults(names, calc, output);

output.close();

return 0;
}
