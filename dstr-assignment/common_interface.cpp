#include "common_interface.h"

void systemHeading() {
    cout << "          UNIVERSITY RECOMMENDATION SYSTEM          " << endl;
    cout << "====================================================" << endl;
}

string promptUserSearchField() {
	// a utility function that converts integer (selection by users) into sort/search fields in string format
	// the string returned is in format "sortType|sortField" so the value returned need to be parsed

	int selection = 0;

	cout << "Which field do you want to search the universities by?" << endl;
	cout << "1. General Rank" << endl;
	cout << "2. Institution Name" << endl;
	cout << "3. Location Code" << endl;
	cout << "4. Location" << endl;
	cout << "5. Academic Reputation Score" << endl;
	cout << "6. Academic Reputation Rank" << endl;
	cout << "7. Employer Reputation Score" << endl;
	cout << "8. Employer Reputation Rank" << endl;
	cout << "9. Faculty/Student Ratio Score" << endl;
	cout << "10. Faculty/Student Ratio Rank" << endl;
	cout << "11. Citations per Faculty Score" << endl;
	cout << "12. Citations per Faculty Rank" << endl;
	cout << "13. International Faculty Ratio Score" << endl;
	cout << "14. International Faculty Ratio Rank" << endl;
	cout << "15. International Student Ratio Score" << endl;
	cout << "16. International Student Ratio Rank" << endl;
	cout << "17. International Research Network Score" << endl;
	cout << "18. International Research Network Rank" << endl;
	cout << "19. Employment Outcome Score (GER Score)" << endl;
	cout << "20. Employment Outcome Rank (GER Rank)" << endl;
	cout << "21. Score Scaled" << endl;
	cout << "22. Exit" << endl;
	cout << "Enter your selection here >> ";
	cin >> selection;

	// clear string elements
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch (selection) {
	case 1:
		return "uni_rank|uni_rank";
	case 2:
		return "text|uni_institution";
	case 3:
		return "text|uni_location_code";
	case 4:
		return "text|uni_location";
	case 5:
		return "score|uni_ar_score";
	case 6:
		return "rank_obj|uni_ar_rank";
	case 7:
		return "score|uni_er_score";
	case 8:
		return "rank_obj|uni_er_rank";
	case 9:
		return "score|uni_fsr_score";
	case 10:
		return "rank_obj|uni_fsr_rank";
	case 11:
		return "score|uni_cpf_score";
	case 12:
		return "rank_obj|uni_cpf_rank";
	case 13:
		return "score|uni_ifr_score";
	case 14:
		return "rank_obj|uni_ifr_rank";
	case 15:
		return "score|uni_isr_score";
	case 16:
		return "rank_obj|uni_isr_rank";
	case 17:
		return "score|uni_irn_score";
	case 18:
		return "rank_obj|uni_irn_rank";
	case 19:
		return "score|uni_ger_score";
	case 20:
		return "rank_obj|uni_ger_rank";
	case 21:
		return "score|uni_scored_scaled";
	case 22:
		return "";
	default:
		cout << "Invalid input!" << endl;
		system("pause");
		return promptUserSearchField();
	}
}
