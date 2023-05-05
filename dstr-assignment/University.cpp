#include "University.h"

University::University(int rank, string institution, Rank* rank_obj, double score) {
    // for testing only
    uni_rank = rank;
    uni_institution = institution;
    uni_ar_rank = rank_obj;
    uni_ar_score = score;
}

University::University(
    int rank, string institution, string location_code, string location, double ar_score,
    Rank* ar_rank, double er_score, Rank* er_rank, double fsr_score, Rank* fsr_rank,
    double cpf_score, Rank* cpf_rank, double ifr_score, Rank* ifr_rank, double isr_score,
    Rank* isr_rank, double irn_score, Rank* irn_rank, double ger_score, Rank* ger_rank, double score_scaled
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

// general getters
string University::getStringValue(string field) {
    // return value of respective field given the field name
    // e.g. field = "institution" returns institution variable

    if (field == "uni_institution") {
        return uni_institution;

    }
    else if (field == "uni_location_code") {
        return uni_location_code;

    }
    else if (field == "uni_location") {
        return uni_location;

    }
    else {
        return NULL;
    }
}

double University::getScoreValue(string field) {
    if (field == "uni_ar_score") {
        return uni_ar_score;
    }
    else if (field == "uni_er_score") {
        return uni_er_score;
    }
    else if (field == "uni_fsr_score") {
        return uni_fsr_score;
    }
    else if (field == "uni_cpf_score") {
        return uni_cpf_score;
    }
    else if (field == "uni_ifr_score") {
        return uni_ifr_score;
    }
    else if (field == "uni_isr_score") {
        return uni_isr_score;
    }
    else if (field == "uni_irn_score") {
        return uni_irn_score;
    }
    else if (field == "uni_ger_score") {
        return uni_ger_score;
    }
    else if (field == "uni_score_scaled") {
        return uni_score_scaled;
    }
    else {
        return NULL;
    }
}

Rank* University::getRankValue(string field) {
    if (field == "uni_ar_rank") {
        return uni_ar_rank;
    }
    else if (field == "uni_er_rank") {
        return uni_er_rank;
    }
    else if (field == "uni_fsr_rank") {
        return uni_fsr_rank;
    }
    else if (field == "uni_cpf_rank") {
        return uni_cpf_rank;
    }
    else if (field == "uni_ifr_rank") {
        return uni_ifr_rank;
    }
    else if (field == "uni_isr_rank") {
        return uni_isr_rank;
    }
    else if (field == "uni_irn_rank") {
        return uni_irn_rank;
    }
    else if (field == "uni_ger_rank") {
        return uni_ger_rank;
    }
    else {
        return NULL;
    }
}

// getters
int University::getRank() { return uni_rank; }
string University::getInstitution() { return uni_institution; }
string University::getLocationCode() { return uni_location_code; }
string University::getLocation() { return uni_location; }
double University::getARScore() { return uni_ar_score; }
Rank* University::getARRank() { return uni_ar_rank; }
double University::getERScore() { return uni_er_score; }
Rank* University::getERRank() { return uni_er_rank; }
double University::getFSRScore() { return uni_fsr_score; }
Rank* University::getFSRRank() { return uni_fsr_rank; }
double University::getCPFScore() { return uni_cpf_score; }
Rank* University::getCPFRank() { return uni_cpf_rank; }
double University::getIFRScore() { return uni_ifr_score; }
Rank* University::getIFRRank() { return uni_ifr_rank; }
double University::getISRScore() { return uni_isr_score; }
Rank* University::getISRRank() { return uni_isr_rank; }
double University::getIRNScore() { return uni_irn_score; }
Rank* University::getIRNRank() { return uni_irn_rank; }
double University::getGERScore() { return uni_ger_score; }
Rank* University::getGERRank() { return uni_ger_rank; }
double University::getScoreScaled() { return uni_score_scaled; }

// setters
void University::setRank(int rank) { uni_rank = rank; }
void University::setInstitution(string institution) { uni_institution = institution; }
void University::setLocationCode(string location_code) { uni_location_code = location_code; }
void University::setLocation(string location) { uni_location = location; }
void University::setARScore(double ar_score) { uni_ar_score = ar_score; }
void University::setARRank(Rank* ar_rank) { uni_ar_rank = ar_rank; }
void University::setERScore(double er_score) { uni_er_score = er_score; }
void University::setERRank(Rank* er_rank) { uni_er_rank = er_rank; }
void University::setFSRScore(double fsr_score) { uni_fsr_score = fsr_score; }
void University::setFSRRank(Rank* fsr_rank) { uni_fsr_rank = fsr_rank; }
void University::setCPFScore(double cpf_score) { uni_cpf_score = cpf_score; }
void University::setCPFRank(Rank* cpf_rank) { uni_cpf_rank = cpf_rank; }
void University::setIFRScore(double ifr_score) { uni_ifr_score = ifr_score; }
void University::setIFRRank(Rank* ifr_rank) { uni_ifr_rank = ifr_rank; }
void University::setISRScore(double isr_score) { uni_isr_score = isr_score; }
void University::setISRRank(Rank* isr_rank) { uni_isr_rank = isr_rank; }
void University::setIRNScore(double irn_score) { uni_irn_score = irn_score; }
void University::setIRNRank(Rank* irn_rank) { uni_irn_rank = irn_rank; }
void University::setGERSCore(double ger_score) { uni_ger_score = ger_score; }
void University::setGERRank(Rank* ger_rank) { uni_ger_rank = ger_rank; }
void University::setScoreScaled(double score_scale) { uni_score_scaled = score_scale; }

void University::printDetails() {
    // print all details of a university
    cout << "Rank: " << uni_rank << endl;
    cout << "Institution Name: " << uni_institution << endl;
    cout << "Uni Location Code: " << uni_location_code << endl;
    cout << "Uni Location: " << uni_location << endl;
    cout << "Academic Reputation Score: " << setprecision(2) << fixed << uni_ar_score << endl;
    cout << "Academic Reputation Rank: " << uni_ar_rank->getRank() << endl;
    cout << "Employer Reputation Score: " << setprecision(2) << fixed << uni_er_score << endl;
    cout << "Employer Reputation Rank: " << uni_er_rank->getRank() << endl;
    cout << "Faculty/Student Ratio Score: " << setprecision(2) << fixed << uni_fsr_score << endl;
    cout << "Faculty/Student Ratio Rank: " << uni_fsr_rank->getRank() << endl;
    cout << "Citations per Faculty Score: " << setprecision(2) << fixed << uni_cpf_score << endl;
    cout << "Citations per Faculty Rank: " << uni_cpf_rank->getRank() << endl;
    cout << "International Faculty Ratio Score: " << setprecision(2) << fixed << uni_ifr_score << endl;
    cout << "International Faculty Ratio Rank: " << uni_ifr_rank->getRank() << endl;
    cout << "International Student Ratio Score: " << setprecision(2) << fixed << uni_isr_score << endl;
    cout << "International Student Ratio Rank: " << uni_isr_rank->getRank() << endl;
    cout << "International Research Network Score: " << setprecision(2) << fixed << uni_irn_score << endl;
    cout << "International Research Network Rank: " << uni_irn_rank->getRank() << endl;
    cout << "Employment Outcome Score (GER Score): " << setprecision(2) << fixed << uni_ger_score << endl;
    cout << "Employment Outcome Rank (GER Rank): " << uni_ger_rank->getRank() << endl;
    cout << "Score scaled: " << setprecision(2) << fixed << uni_score_scaled << endl;
}

University::~University() {}