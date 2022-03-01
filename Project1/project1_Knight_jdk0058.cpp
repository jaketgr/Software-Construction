/* FILE NAME: project1_Knight_jdk0058.cpp 
 * AUTHOR: Jacob Knight
 * Auburn ID: jdk0058
 * Resources: I used the project1 hints file to help with this assignment and I also used 
 * https://stackoverflow.com/questions/9349575/cin-ignore-is-not-working to learn about cin.fail, clear, and ignore.
 * Compile: g++ project1_Knight_jdk0058.cpp 
 * Run: ./a.out project1_Knight_jdk0058.cpp
 */ 
 
#include <iostream> 
using namespace std; 
 
int main() { 
 // VARIABLE INITIALIZATION 
  double loan = 0;
  double interestRate = -1;
  double monthlyPaid = -1;
  double interestRateC = -1;
 // CURRENCY FORMATTING 
 cout.setf(ios::fixed); 
 cout.setf(ios::showpoint); 
 cout.precision(2); 
  
 // USER INPUT 
 // NOTE: For valid input, the loan, interest, and monthly payment must 
 // be positive. The monthly payment must also be large enough to 
 // terminate the loan.  
 while ((cin.fail()) || !cin || (loan <= 0)) {
     cout << "Loan Amount: "; 
     cin >> loan;
     if ((cin.fail()) || !cin || (loan <= 0)) {
         cin.clear();
         cin.ignore(20, '\n');
     }
 }
     cout << "Interest Rate (% per year): "; 
     cin >> interestRate;
  while ((cin.fail()) || !cin || (interestRate < 0)) {
         cout << "Interest Rate (% per year): "; 
         cin.clear();
         cin.ignore(20, '\n');
         cin >> interestRate;
  }

 // GET PROPER INTEREST RATES FOR CALCULATIONS 
 interestRate /= 12; 
 interestRateC = interestRate / 100; 

 while (monthlyPaid <= 0 || monthlyPaid <= loan * interestRateC || cin.fail() || !cin) {
     cout << "Monthly Payments: "; 
     cin >> monthlyPaid;
     if (monthlyPaid <= 0 || monthlyPaid <= loan * interestRateC || cin.fail() || !cin) {
         cin.clear();
         cin.ignore(20, '\n');
     }

 }
  
 cout << endl; 
  
 // AMORTIZATION TABLE 
 cout << "*****************************************************************\n" 
      << "\tAmortization Table\n" 
      << "*****************************************************************\n" 
      << "Month\tBalance\t  Payment\tRate\tInterest\tPrincipal\n"; 

      int currentMonth = 0;
      double interestTotal = 0;
 
 // LOOP TO FILL TABLE 
 while (loan > 0) { 
  if (currentMonth == 0) { 
   cout << currentMonth++ << "\t$" << loan; 
   cout << "  N/A\t\tN/A\tN/A\t\tN/A\n"; 
  } 
  else {
      double interestPayment = loan * interestRateC;
	  double principal = monthlyPaid - interestPayment;
	  loan -= principal;
	  interestTotal += interestPayment;

			if (loan < 0) {
				principal += loan;
				monthlyPaid += loan;
				loan = 0;
			}

			cout << currentMonth++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "  $" << monthlyPaid << "\t" << interestRateC * 100 << "\t$" << interestPayment << "\t\t$" << principal << "\n"; 
		}
	}
 cout << "****************************************************************\n"; 
 cout << "\nIt takes " << --currentMonth << " months to pay off " 
      << "the loan.\n" 
      << "Total interest paid is: $" << interestTotal; 
 cout << endl << endl;  
 return 0; 
} 