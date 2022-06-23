#include "StringUtilities.h"


std::string StringUtilities::ClampString(std::string s, int n, bool left) {
	if (s.size() <= n)
		return s;
	if (left) {
		while (s.size() > n)
			s.pop_back();
	}
	else {
		char* buffer = new char[n];
		s.copy(buffer, n, s.size() - n);
		s.clear();
		for (int i = 0; i < n; i++)
			s.push_back(buffer[i]);
	}
	return s;
}