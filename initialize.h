#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>       
#include <sstream>
using namespace std;

//function to get the output character 
vector <char> extract_output(string& input_exp)
{
	int found;
	vector <char> output_chars;

	found = input_exp.find("=");
	while (found != string::npos)
	{
		output_chars.push_back(input_exp[found - 1]);
		input_exp.erase(found - 1, 2);
		found = input_exp.find("=");
	}
	return output_chars;
}

//Function to check priority of labels 
bool check_priority(char& operator1, char& operator2)
{
	bool priority_bool = false;

	if ((operator1 == '`' && operator2 == '&') ||
		(operator1 == '`' && operator2 == '|') ||
		(operator1 == '&' && operator2 == '|'))
		priority_bool = true;

	return priority_bool;
}

//function to push the characters in a vector according to thier priority 
vector <string> calculate_Priority(string& input_exp)
{
	vector <string> string_vec;
	vector <string> last_vect;
	string current_str, expression;
	char top_char;
	stack<char> stack;
	stringstream ss(input_exp);

	while (ss.good())
	{
		string substr;
		getline(ss, substr, ';');
		string_vec.push_back(substr);
	}

	for (int i = 0; i < string_vec.size(); i++)
	{
		current_str = string_vec[i];
		for (int i = 0; i < current_str.length(); i++)
		{
			if (current_str[i] == '`' || current_str[i] == '&' || current_str[i] == '|')
			{
				if (!stack.empty())
					top_char = stack.top();
				while (!stack.empty() && check_priority(top_char, current_str[i]))
				{
					top_char = stack.top();
					stack.pop();
					expression += top_char;
					if (!stack.empty())
						top_char = stack.top();
				}
				stack.push(current_str[i]);
			}

			else if (current_str[i] == '(')
				stack.push(current_str[i]);

			else if (current_str[i] == ')' && !stack.empty())
			{
				top_char = stack.top();
				stack.pop();
				while (!stack.empty() && top_char != '(')
				{
					expression += top_char;
					top_char = stack.top();
					stack.pop();
				}
			}
			else
				expression += current_str[i];
		}

		while (!stack.empty())
		{
			top_char = stack.top();
			stack.pop();
			expression += top_char;
		}
		last_vect.push_back(expression);
		expression = "";
	}
	return last_vect;
}

//Function that does the same thing as de Morgan Law 
vector<char>negate_exp(string input) {

	vector<char>temp;
	vector<char>new_temp;
	vector<char>final_temp;
	bool flag = true;

	for (int i = input.length(); i >= 0; i--) {
		temp.push_back(input[i]);
	}
	if (input.back() == '`') {
		input.pop_back();
		for (int i = 0; i < input.length(); i++)
			final_temp.push_back(input[i]);
	}
	else {
		for (int i = 0; i < temp.size(); i++) {

			if ((temp[i] == '`' && temp[i + 1] == '&') || (temp[i] == '`' && temp[i + 1] == '|')) {
				flag = false;
				continue;
			}
			else if (flag == true) {

				if (temp[i] == '`' && (temp[i + 1] != '&' || '|')) {
					continue;
				}
				else if (temp[i] == '|') {
					new_temp.push_back('&');
				}
				else if (temp[i] == '&') {
					new_temp.push_back('|');
				}
				else {
					if (i != 0 && temp[i - 1] != '`' && temp[i] != ('|' || '&'))
						new_temp.push_back('`');
					new_temp.push_back(temp[i]);

				}

			}

			if (!flag)
				new_temp.push_back(temp[i]);


		}

		for (int j = new_temp.size() - 1; j > 0; j--)
			final_temp.push_back(new_temp[j]);
	}

	return final_temp;
}
