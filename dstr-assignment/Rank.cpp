#include "Rank.h"
#include "util.h"

Rank::Rank(string newRank) {
	rank = newRank;
	rank_number = convertToInt(newRank);
}

string Rank::getRank() { return rank; }
int Rank::getRankNumber() { return rank_number; }

void Rank::setRank(string newRank) { rank = newRank; }
void Rank::setRankNumber(int newRank) { rank_number = newRank; }

bool Rank::isHigherThan(Rank* otherRank) { return this->rank_number < otherRank->rank_number; }
bool Rank::isLowerThan(Rank* otherRank) { return this->rank_number > otherRank->rank_number; }
bool Rank::isEqual(Rank* otherRank) { return this->rank_number == otherRank->rank_number; }

void Rank::printDetails() {

}