/* Samuel Knight
Project 2 - Grade Calculation Program
COSC 120
04-03-24
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


//Constants for assignment percentage values
const double QUIZ_PERCENTAGE = .10;
const double LAB_PERCENTAGE = .10;
const double PROJECT_PERCENTAGE = .20;
const double MIDTERM_PERCENTAGE = .30;
const double FINAL_EXAM_PERCENTAGE = .30;
const double ATT_PEN = .10; 

//Function to calculate average of an array
double averageGrade(double gradeArray[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += gradeArray[i];
    }
    return sum / size;
}

//Function to calculate minimum of an array
double minGrade(double gradeArray[], int size) {
    double min = gradeArray[0];
    for (int i = 1; i < size; ++i) {
        if (gradeArray[i] < min) {
            min = gradeArray[i];
        }
    }
    return min;
}

//Function to calculate maximum of an array
double maxGrade(double gradeArray[], int arraySize) {
    double max = gradeArray[0];
    for (int i = 1; i < arraySize; ++i) {
        if (gradeArray[i] > max) {
            max = gradeArray[i];
        }
    }
    return max;
}

//Function to calculate final letter grade
char finalLetterGrade(double finalGrade) {
    if (finalGrade >= 90.0)
        return 'A';
    else if (finalGrade >= 80.0)
        return 'B';
    else if (finalGrade >= 70.0)
        return 'C';
    else if (finalGrade >= 60.0)
        return 'D';
    else
        return 'F';
}

int main() {

  string headingLine;

    //Open the file
    ifstream dataIn("COSC120Grades.txt");

    //Check if the file was opened successfully
    if (!dataIn) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
  
   cout << "File opened successfully." << endl;
   cout << endl;
  
    //gets first two lines of file
    for (int i =1; i <= 2; i++) {
      getline(dataIn, headingLine);
      cout << headingLine << endl;
    }

 

    //Variables to store first and last name along with assignment scores
    string firstName, lastName;
    double quizGrades[10], labGrades[10], projectGrades[3], midtermGrades[3], finalExamGrade, attendance;

    //Read data for each student
    while (dataIn >> firstName >> lastName) {
        for (int i = 0; i < 10; ++i)
          dataIn >> quizGrades[i];

        for (int i = 0; i < 10; ++i)
          dataIn >> labGrades[i];

        for (int i = 0; i < 3; ++i)
          dataIn >> projectGrades[i];

        for (int i = 0; i < 3; ++i)
          dataIn >> midtermGrades[i];

        dataIn >> finalExamGrade;

        dataIn >> attendance;

        //Calculate average grades
      double quizAverage = averageGrade(quizGrades, 10);
      double labAverage = averageGrade(labGrades, 10);
      double projectAverage = averageGrade(projectGrades, 3);
      double midtermAverage = averageGrade(midtermGrades, 3);

        //Apply attendance penalty
      double attPen = (ATT_PEN * 100.0 * attendance); 

      //Calculate total grade percentages
      double totalGrade = ((QUIZ_PERCENTAGE * quizAverage) + (LAB_PERCENTAGE * labAverage) + (PROJECT_PERCENTAGE * projectAverage) + (MIDTERM_PERCENTAGE * midtermAverage) + (FINAL_EXAM_PERCENTAGE * finalExamGrade) - attPen);

        //Get minimum and maximum grades
        double minQuizGrade = minGrade(quizGrades, 10);
        double minLabGrade = minGrade(labGrades, 10);
        double maxProjectGrade = maxGrade(projectGrades, 3);
        double maxMidtermGrade = maxGrade(midtermGrades, 3);

        //Calculate final letter grade
        char letterGrade = finalLetterGrade(totalGrade);

        //Output the results
        cout << setw(15) << left << firstName << setw(15) << left << lastName
             << setw(10) << left << minQuizGrade << setw(10) << left << minLabGrade
             << setw(13) << left << maxProjectGrade << setw(13) << left << maxMidtermGrade
             << setw(13) << left << fixed << setprecision(1) << totalGrade
             << setw(2) << left << letterGrade << endl;
    }

    //Close the file
  dataIn.close();

    return 0;
}
