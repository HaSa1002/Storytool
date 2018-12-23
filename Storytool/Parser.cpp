#include "Parser.hpp"
#include <stack>
#include <exception>
#include <algorithm>

namespace st {
	namespace script {
		void clearWhiteSpace(std::string& source) {
			size_t p = source.find_first_not_of("\r\n\n\t ");
			if (p != std::string::npos)
				source = source.substr(p);
		}

		bool isNumeric(const std::string& input) {
			return input.find_first_not_of("0123456789.- ") == std::string::npos;
		}

		//Returns in left ends (first), right starts (second) manner splitted by the first operator found (operator is gap between first and second);
		auto splitComparision(const std::string& s) -> std::pair<size_t, size_t> {
			//Find where the first operator starts
			size_t f = s.find_first_of("<>~=");

			//Early out, if there is no comparison operator
			if (f == std::string::npos) return { std::string::npos, std::string::npos };

			//Check which char is at this position
			char op = s[f];

			//Check if it's one or two chars long
			size_t fs = f;
			if (s[f + 1] == '=') ++fs;

			//Check if it is a correct comparison operator
			//Else throw
			if (fs == f && (op == '~' || op == '='))	throw std::invalid_argument("Expected '=' near " + s.substr(0, f));

			//Now return our result
			return{ f - 1,  fs + 1 };
		}

		std::string getVariableName(const std::string& s) {
			std::string t { s.substr(0, s.find_first_of(' ')) };
			clearWhiteSpace(t);
			return t;
		}

		double getVariable(const std::string& s, GlobalVars& globals, GlobalVars& locals) {
			std::string var { getVariableName(s) };
			clearWhiteSpace(var);
			if (var[0] == ':') {
				//It's a global
				var = var.substr(1);

				if (globals.find(var) == globals.end()) {
					std::string message { "Global '" + var };
					message.append("' does not exist! Please create it first in the globals table or check the spelling.");
					throw std::invalid_argument(message);
				}
				return globals[var];

			} else {
				//It's a normal var
				if (locals.find(var) == locals.end()) {
					std::string message { "Variable '" + var };
					message.append("' does not exist! Please make sure that it was set and is valid in the scope or check the spelling.");
					throw std::invalid_argument(message);
				}
				return locals[var];
			}
		}

		bool hasMath(const std::string& s) {
			if (s.find_first_of("*/+-!") == std::string::npos) return false;
			return true;
		}

		//throws invalid_argument on syntax error and sth on div by 0
		double calculateMath(std::string& s, GlobalVars& globals, GlobalVars& locals) {

			//1. (
			//2. )

			while (true) {
				size_t k1 = s.find_first_of('(');
				size_t k2 = s.find_first_of(')');
				if (k1 != std::string::npos && k2 != std::string::npos) {
					//Recursive calculation of the bracket
					++k1;
					k2;
					std::string rec { s.substr(k1, k2 - k1) };
					double val = calculateMath(rec, globals, locals);
					//We cut out the area within the brackets and replace it with the result
					rec = s.substr(k2 + 1);
					s = s.substr(0, k1 - 1);
					s.append(std::to_string(val));
					s.append(rec);

				} else if (!(k1 == std::string::npos && k2 == std::string::npos)) {
					//Syntaxerror. Now, we have to check if it is ( or ) without a neighbour
					if (k1 == std::string::npos) {
						//) misses a (
						throw std::invalid_argument("Unexpected ')'. Missing a '('.");
					} else {
						//( misses a )
						throw std::invalid_argument("Unexpected '('. Missing a ')'.");
					}
				} else {
					break;
				}
			}
			//3. *
			//4. /
			//We work from left to right, and since * and / have the same weight we need to check for the first occurence
			double result = 0;

			size_t k = s.find_first_of("*/");
			if (k != std::string::npos) {
				//Different approach: Calc both sides:

				std::string left { s.substr(0, k) };
				std::string right { s.substr(k + 1) };
				std::string bl;
				std::string br;

				//We need to find what excactly to calc
				size_t p = left.find_first_of("+-");
				if (p != std::string::npos) {
					//Now save the substr left from p + 1 and change left to be right of p
					bl = left.substr(0, p + 1);
					left = left.substr(p + 1);
				}
				p = right.find_first_of("+-");
				if (p != std::string::npos) {
					//Now save the substr left from p + 1 and change left to be right of p
					br = right.substr(p);
					right = right.substr(0, p);
				}
				double res;

				if (s[k] == '*') res = calculateMath(left, globals, locals) * calculateMath(right, globals, locals);
				else res = calculateMath(left, globals, locals) / calculateMath(right, globals, locals);

				// put the result back into the string
				s = bl + std::to_string(res) + br;
			}

			//5. +
			//6. -

			k = s.find_first_of("+-");
			if (k != std::string::npos) {
				//Different approach: Calc both sides:

				std::string left { s.substr(0, k) };
				std::string right { s.substr(k + 1) };

				//We can just recurse, since there are just operations without 

				if (s[k] == '+') result = calculateMath(left, globals, locals) + calculateMath(right, globals, locals);
				else result = calculateMath(left, globals, locals) - calculateMath(right, globals, locals);

				// put the result back into the string
				s = std::to_string(result);
			}


			//7. !
			k = s.find_first_of('!');
			if (k != std::string::npos) {
				std::string rec { s.substr(k + 1) }; //FIXME: so that we can write !temp instead of temp!
				//Found either + or -
				// We need to recurse, since there could be a var or a const left
				if (calculateMath(rec, globals, locals) == 0) result = 1;
				else result = 0;


				//Lastly we have to move the string and research the string
				s = std::to_string(result);
			}

			//8. Variables and constants
			//If this is the 1st called func then shouldn't be anything here
			clearWhiteSpace(s);
			if (!s.empty()) {
				if (isNumeric(s)) result = std::stod(s);
				else result = getVariable(s, globals, locals);

				s.clear();
			}
			return result;
		}

		void setVar(std::string& s, GlobalVars& globals, GlobalVars& locals) {
			clearWhiteSpace(s);
			size_t p = s.find_first_of("+-*/");
			if (p != std::string::npos) {
				if (s[p + 1] != '=') throw std::invalid_argument("Didn't found required '='."); //TODO: Write better err msg
				std::string temp { s.substr(p + 2, s.find_first_of(';') - p - 2) };
				std::string var { getVariableName(s.substr(0, p)) };
				double res = calculateMath(temp, globals, locals);
				if (var[0] == ':') {
					//Global
					var = var.substr(1);
					if (globals.find(var) == globals.end())
						throw std::invalid_argument("Global () doesn't exist. Create it first in the Globals Window and then recompile the script!");

					switch (s[p]) {
						case '+':
							globals[var] += res;
							break;
						case '-':
							globals[var] -= res;
							break;
						case '*':
							globals[var] *= res;
							break;
						case '/':
							globals[var] /= res;
							break;
					}
				} else {
					if (locals.find(var) == locals.end())
						throw std::invalid_argument("Local () doesn't exist.");

					switch (s[p]) {
						case '+':
							locals[var] += res;
							break;
						case '-':
							locals[var] -= res;
							break;
						case '*':
							locals[var] *= res;
							break;
						case '/':
							locals[var] /= res;
							break;
					}
				}
			} else {
				//Check for normal assign operator (=)
				p = s.find_first_of('=');
				if (p == std::string::npos) throw std::invalid_argument("Unexpected variable found. What to do with it?"); //TODO: Make more elegant
				std::string var { getVariableName(s.substr(0, p)) };
				std::string temp { s.substr(p + 1) };
				double res = calculateMath(temp, globals, locals);
				if (var[0] == ':') {
					//Global (Have to cut out ':')
					if (globals.find(var.substr(1)) == globals.end())
						throw std::invalid_argument("Global () doesn't exist. Create it first in the Globals Window and then recompile the script!");
					else
						globals[var.substr(1)] = res;
				} else {
					//Local
					locals.insert_or_assign(var, res);
				}
			}
			s.clear();
		}

		bool run(std::string script, GlobalVars & globals) {
			std::string executing;
			std::stack<std::string> code;
			std::unordered_map<std::string, double> vars;

			// A statement has to end with either a ; or { (in ifs)
			while (af::getline(script, executing, true, ";{")) {
				//Clear white spaces, \t, \r\n, \n
				clearWhiteSpace(executing);
				//Check for keywords (return, if, else, {, }
				//1. Check for return _;
				if (executing.substr(0, 6) == "return") {
					std::string temp { executing.substr(6, executing.find_first_of(';', 6) - 6) };
					return calculateMath(temp, globals, vars) != 0;
				}

				//2. Check for if
				if (executing.substr(0, 2) == "if") {
					code.push("if");
					clearWhiteSpace(executing);
					//Get on what to check
					std::pair<size_t, size_t> res { splitComparision(executing) };
					bool result = false;

					if (res.first == std::string::npos) {
						//Special case: Just bool check
						//CalculateMath will return always something if there was something
						std::string temp { executing.substr(2) };
						double res = calculateMath(temp, globals, vars);
						if (res != 0.0) result = true;



					} else {
						//We have to Compare
						std::string lefts { executing.substr(2, res.first) };
						std::string rights { executing.substr(res.second) };
						double left = calculateMath(lefts, globals, vars);
						double right = calculateMath(rights, globals, vars);

						switch (executing[res.first + 1]) {
							case '<':
								if (executing[res.first + 2] == '=') result = left <= right;
								else result = left < right;
								break;
							case '>':
								if (executing[res.first + 2] == '=') result = left >= right;
								else result = left > right;
								break;
							case '~':
								result = left != right;
								break;
							case '=':
								result = left == right;
								break;
							default:
								throw std::invalid_argument("Comparison failed! Not a operator: " + executing[res.first + 1]);
						}
					}
					executing.clear();
					if (result) {
						//Execute block,
						af::getline(script, executing, true, "}");
						std::string elseBlock;
						af::getline(script, elseBlock, true, "}");
						script = executing + script; //TODO: Make this hack nicer
						executing.clear();
						code.pop();
						continue;

					} else {
						//We have to skip the block
						af::getline(script, executing, true, "}");
						executing.clear();
						af::getline(script, executing, true, "{");
						//Check for else then return to normal buisness
						clearWhiteSpace(executing);
						if (executing.substr(0, 4) == "else") {
							executing.clear();
							code.pop();
							continue;
						}
						code.pop();
					}

				}
				//3. Check for {
				//4. Check for }
				//5. Check for else

				//Check for operators


				//Check for setters
				//1. *=
				//2. /=
				//3. +=
				//4. -=
				//5. =
				setVar(executing, globals, vars);
				if (!executing.empty())
					throw std::invalid_argument("Unexpected symbol(s) left. Is a ';' missing?");

			}

			return true;
		}
	}
}


