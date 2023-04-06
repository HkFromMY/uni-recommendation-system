#include "University.h"

#include "UniversityNode.h"

University::University(int rank, string institution) {
    // for testing only
    uni_rank = rank;
    uni_institution = institution;
}

University::University(
    int rank, string institution, string location_code, string location, double ar_score,
    int ar_rank, double er_score, int er_rank, double fsr_score, int fsr_rank,
    double cpf_score, int cpf_rank, double ifr_score, int ifr_rank, double isr_score,
    int isr_rank, double irn_score, int irn_rank, double ger_score, int ger_rank, double score_scaled
) {
    uni_rank = rank;
    uni_institution = institution;
    uni_location_code = location_code;
    uni_location = location;
    uni_ar_score = ar_score;
    uni_ar_rank = ar_rank;
    uni_er_score = er_score;
    uni_er_rank = er_rank;
    uni_fsr_score = fsr_score;
    uni_fsr_rank = fsr_rank;
    uni_cpf_score = cpf_score;
    uni_cpf_rank = cpf_rank;
    uni_ifr_score = ifr_score;
    uni_ifr_rank = ifr_rank;
    uni_isr_score = isr_score;
    uni_isr_rank = isr_rank;
    uni_irn_score = irn_score;
    uni_irn_rank = irn_rank;
    uni_ger_score = ger_score;
    uni_ger_rank = ger_rank;
    uni_score_scaled = score_scaled;
}

// getters
int University::getRank() { return uni_rank; }
string University::getInstitution() { return uni_institution; }
string University::getLocationCode() { return uni_location_code; }
string University::getLocation() { return uni_location; }
double University::getARScore() { return uni_ar_score; }
int University::getARRank() { return uni_ar_rank; }
double University::getERScore() { return uni_er_score; }
int University::getERRank() { return uni_er_rank; }
double University::getFSRScore() { return uni_fsr_score; }
int University::getFSRRank() { return uni_fsr_rank; }
double University::getCPFScore() { return uni_cpf_score; }
int University::getCPFRank() { return uni_cpf_rank; }
double University::getIFRScore() { return uni_ifr_score; }
int University::getIFRRank() { return uni_ifr_rank; }
double University::getISRScore() { return uni_isr_score; }
int University::getISRRank() { return uni_isr_rank; }
double University::getIRNScore() { return uni_irn_score; }
int University::getIRNRank() { return uni_irn_rank; }
double University::getGERScore() { return uni_ger_score; }
int University::getGERRank() { return uni_ger_rank; }
double University::getScoreScaled() { return uni_score_scaled; }

// setters
void University::setRank(int rank) { uni_rank = rank; }
void University::setInstitution(string institution) { uni_institution = institution; }
void University::setLocationCode(string location_code) { uni_location_code = location_code; }
void University::setLocation(string location) { uni_location = location; }
void University::setARScore(double ar_score) { uni_ar_score = ar_score; }
void University::setARRank(int ar_rank) { uni_ar_rank = ar_rank; }
void University::setERScore(double er_score) { uni_er_score = er_score; }
void University::setERRank(int er_rank) { uni_er_rank = er_rank; }
void University::setFSRScore(double fsr_score) { uni_fsr_score = fsr_score; }
void University::setFSRRank(int fsr_rank) { uni_fsr_rank = fsr_rank; }
void University::setCPFScore(double cpf_score) { uni_cpf_score = cpf_score; }
void University::setCPFRank(int cpf_rank) { uni_cpf_rank = cpf_rank; }
void University::setIFRScore(double ifr_score) { uni_ifr_score = ifr_score; }
void University::setIFRRank(int ifr_rank) { uni_ifr_rank = ifr_rank; }
void University::setISRScore(double isr_score) { uni_isr_score = isr_score; }
void University::setISRRank(int isr_rank) { uni_isr_rank = isr_rank; }
void University::setIRNScore(double irn_score) { uni_irn_score = irn_score; }
void University::setIRNRank(int irn_rank) { uni_irn_rank = irn_rank; }
void University::setGERSCore(double ger_score) { uni_ger_score = ger_score; }
void University::setGERRank(int ger_rank) { uni_ger_rank = ger_rank; }
void University::setScoreScaled(double score_scale) { uni_score_scaled = score_scale; }

University::~University() {}