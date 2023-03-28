#include "UniversityNode.h"

UniversityNode::UniversityNode(University* newUniversity) {
	// address pointing to next node
	next = NULL;
    data = newUniversity;
    previous = NULL;
}

// getters
University* UniversityNode::getData() { return data; }
UniversityNode* UniversityNode::getNextAddress() { return next; }
UniversityNode* UniversityNode::getPreviousAddress() { return previous;  }

// setters
void UniversityNode::setData(University* newUniversity) { data = newUniversity; }
void UniversityNode::setNextAddress(UniversityNode* nextAddress) { next = nextAddress;}
void UniversityNode::setPreviousAddress(UniversityNode* previousAddress) { previous = previousAddress; }

//void loadCSVFile() {
//    string rank, ar_rank, er_rank, fsr_rank, cpf_rank, ifr_rank, isr_rank, irn_rank, ger_rank;
//    string institution, location_code, location;
//    string ar_score, er_score, fsr_score, cpf_score, ifr_score, isr_score, irn_score, ger_score, score_scaled;
//    ifstream file("2023 QS World University Rankings.csv");
//
//    while (file.good()) {
//
//        string test[21];
//
//        getline(file, rank, ',');
//        getline(file, institution, ',');
//        getline(file, location_code, ',');
//        getline(file, location, ',');
//        getline(file, ar_score, ',');
//        getline(file, ar_rank, ',');
//        getline(file, er_score, ',');
//        getline(file, er_rank, ',');
//        getline(file, fsr_score, ',');
//        getline(file, fsr_rank, ',');
//        getline(file, cpf_score, ',');
//        getline(file, cpf_rank, ',');
//        getline(file, ifr_score, ',');
//        getline(file, ifr_rank, ',');
//        getline(file, isr_score, ',');
//        getline(file, isr_rank, ',');
//        getline(file, irn_score, ',');
//        getline(file, irn_rank, ',');
//        getline(file, ger_score, ',');
//        getline(file, ger_rank, ',');
//        getline(file, score_scaled, '\n');
//
//        if (institution == "") {
//            break;
//        }
//        else if (institution == "Institution") {
//            // skip first row
//            continue;
//        }
//
//        cout << "Institution --> " << institution << endl;
//        cout << "Rank --> " << rank << endl;
//        cout << "AR Rank --> " << ar_rank << endl << endl;
//
//        
//    }
//
//    return;
//}