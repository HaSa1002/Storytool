#pragma once
#include "Config.hpp"
#include <unordered_map>


namespace st {
	namespace script {
		/*
			ST Script: A Simple Language to express simple comparisions and store data locally
			Example:
				temp = 101;
				if :some_global < temp {
					:other_global += 100;
					temp /= 2;
				} else {
					return 0; // states that the node won't be executed/activated
				}
				if temp {
					temp = temp!; //Inverses temp in a boolean way; Means if temp != 0, it will become 0 and if it's different it will be 1
				}
				//Saying nothing at the end is fine
				//return 1; is assumed

			Syntax:
				variables are just named. Every var is an double; There is no type guessing
				via the : operator is a global accessed

				booleans are expressed via the != 0 logic
				! inverses in this manner

				if is followed by a statement and this by a { ... } block
				else is optional

				Every statement ends with ;

				Comparison Operators:
				<, >, <=, >=, ~=, ==

				Setting operators:
				=, +, -, /, *, +=, -=, /=, *=



			Idea:
				Caching of the result, and only recompute if the globals changed
		
		*/

		bool run(std::string script, GlobalVars& globals);
		bool hasMath(const std::string& s);
		std::string getVariableName(const std::string& s);
		auto splitComparision(const std::string& s)->std::pair<size_t, size_t>;
		void clearWhiteSpace(std::string& source);
		double calculateMath(std::string& s, GlobalVars& globals, GlobalVars& locals);

	}
}