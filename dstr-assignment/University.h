#pragma once
#ifndef university_h
#define university_h

#include "Rank.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class University
{

	private:
		int uni_rank; string uni_institution; string uni_location_code; string uni_location; double uni_ar_score;
		Rank* uni_ar_rank; double uni_er_score; Rank* uni_er_rank; double uni_fsr_score; Rank* uni_fsr_rank;
		double uni_cpf_score; Rank* uni_cpf_rank; double uni_ifr_score; Rank* uni_ifr_rank; double uni_isr_score;
		Rank* uni_isr_rank; double uni_irn_score; Rank* uni_irn_rank; double uni_ger_score; Rank* uni_ger_rank;
		double uni_score_scaled;

	public:
		// constructors
		University(int, string, Rank*, double);
		University(
			int, string, string, string, double, Rank*, double, Rank*, double, Rank*, double, Rank*, double, Rank*,
			double, Rank*, double, Rank*, double, Rank*, double
		);
		~University();

		// general getters
		string getStringValue(string); // by passing the field name, the value is returned
		double getScoreValue(string);
		Rank* getRankValue(string);

		// getters
		int getRank(); string getInstitution(); string getLocationCode(); string getLocation(); double getARScore();
		Rank* getARRank(); double getERScore(); Rank* getERRank(); double getFSRScore(); Rank* getFSRRank();
		double getCPFScore(); Rank* getCPFRank(); double getIFRScore(); Rank* getIFRRank(); double getISRScore();
		Rank* getISRRank(); double getIRNScore(); Rank* getIRNRank(); double getGERScore(); Rank* getGERRank();
		double getScoreScaled();

		// setters
		void setRank(int); void setInstitution(string); void setLocationCode(string); void setLocation(string); void setARScore(double);
		void setARRank(Rank*); void setERScore(double); void setERRank(Rank*); void setFSRScore(double); void setFSRRank(Rank*);
		void setCPFScore(double); void setCPFRank(Rank*); void setIFRScore(double); void setIFRRank(Rank*); void setISRScore(double);
		void setISRRank(Rank*); void setIRNScore(double); void setIRNRank(Rank*); void setGERSCore(double); void setGERRank(Rank*);
		void setScoreScaled(double);

		void printDetails();
};

#endif
