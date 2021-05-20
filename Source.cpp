#include <iostream>
#include <string>
#include "initialize.h"  //File that has functions to give seperate values for PMOS and NMOS 
#include "output.h"      //File that contains struct for CMOS and functions to produce the output
  
using namespace std;

int main() {
	
	vector<CMOS> deck;
	vector<char> output_chars;
	vector<string> expressions;
	vector<char> pun, pdn;
	pun.resize(10000);
	string input;
	string output;

	/* User input */
	cout << "Enter valid boolean expressions separated by ';':" << endl;
	cin >> input;
	cout << endl;

	/* Generating postfix expressions*/
	output_chars = extract_output(input);
	expressions = calculate_Priority(input);   


	for (int i = 0; i < expressions.size(); i++) { 

		string first = expressions[i];

		/* Generating separate expressions for both pun and pdn*/
		for (int i = 0; i < first.length(); i++)
			pun.push_back(first[i]);

		pdn= negate_exp(expressions[i]);
		

		/* for testing,this code ptints the postfix expressions for pun and pdn */

	   //for (int i = 0; i < pun.size(); i++)
	   //	 cout << pun[i];
	   // cout << endl;

	   // for (int i = 0; i < pdn.size(); i++)
	   //		 cout << pdn[i];
       // cout << endl;


		 /* Construction of the pun and pdn*/

		bool flag = false;
		output = output_chars[i];
		run(pun, &deck, output, "VDD", PMOS, flag);
		flag = false;
		run(pdn, &deck, output, "0", NMOS, flag);
	}

	/* Netlist output*/
	CMOS decks;
	for (int i = 0; i < deck.size(); i++) {
		decks = deck[i];
		cout << decks.m_name << " " << decks.drain << " " << decks.gate << " "
			<< decks.source << " " << decks.body << " "
			<< (decks.type == PMOS ? "PMOS" : "NMOS") << endl;
	}


}

