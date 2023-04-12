#pragma once
#ifndef rank_h
#define rank_h

#include <iostream>

using namespace std;

class Rank
{
	private:
		string rank;
		int rank_number;

	public:
		Rank(string);

		string getRank();
		int getRankNumber();

		void setRank(string);
		void setRankNumber(int);

		bool isHigherThan(Rank*);
		bool isLowerThan(Rank*);
		bool isEqual(Rank*);

		void printDetails();

};

#endif
