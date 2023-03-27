#pragma once
#ifndef university_h
#define university_h

#include <iostream>
#include <string>

using namespace std;

class University
{

	private:
		int uni_rank; string uni_institution; string uni_location_code; string uni_location; double uni_ar_score;
		int uni_ar_rank; double uni_er_score; int uni_er_rank; double uni_fsr_score; int uni_fsr_rank;
		double uni_cpf_score; int uni_cpf_rank; double uni_ifr_score; int uni_ifr_rank; double uni_isr_score;
		int uni_isr_rank; double uni_irn_score; int uni_irn_rank; double uni_ger_score; int uni_ger_rank;
		double uni_score_scaled;

	public:
		// constructors
		University(int, string);
		University(
			int, string, string, string, double, int, double, int, double, int, double, int, double, int,
			double, int, double, int, double, int, double
		);

		// getters
		int getRank(); string getInstitution(); string getLocationCode(); string getLocation(); double getARScore();
		int getARRank(); double getERScore(); int getERRank(); double getFSRScore(); int getFSRRank();
		double getCPFScore(); int getCPFRank(); double getIFRScore(); int getIFRRank(); double getISRScore();
		int getISRRank(); double getIRNScore(); int getIRNRank(); double getGERScore(); int getGERRank();
		double getScoreScaled();

		// setters
		void setRank(int); void setInstitution(string); void setLocationCode(string); void setLocation(string); void setARScore(double);
		void setARRank(int); void setERScore(double); void setERRank(int); void setFSRScore(double); void setFSRRank(int);
		void setCPFScore(double); void setCPFRank(int); void setIFRScore(double); void setIFRRank(int); void setISRScore(double);
		void setISRRank(int); void setIRNScore(double); void setIRNRank(int); void setGERSCore(double); void setGERRank(int);
		void setScoreScaled(double);


};

#endif
