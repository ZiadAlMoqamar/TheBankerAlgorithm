#include <bits/stdc++.h>;

using namespace std;

int choiceList() {
	int choiceListNum;
	cout << "Choose from the following:" << endl;
	cout << "1- Safety State Check." << endl;
	cout << "2- Request Grant Check." << endl;
	cout << "3- Enter New Matrices." << endl;
	cout << "4- Exit From The Program." << endl;
	cout << "Enter The Corresponding Number: ";
	cin >> choiceListNum;
	return choiceListNum;
}

bool compareMatrix(vector <int> need, vector <int> work) {
	bool ans = true;
	for (int i = 0; i < need.size(); i++) {
		if (need[i] > work[i]) {
			ans = false;
			break;
		}
	}
	return ans;
}

bool allFinishIsTrue(vector <bool> finish) {
	bool ans = true;
	for (int i = 0; i < finish.size(); i++) {
		if (finish[i] == false) {
			ans = false;
			break;
		}
	}
	return ans;
}

int main() {
	cout << "Hello To Banker Algorithm Program" << endl;
	int choiceListNum = 3;
	int numProcesses;
	int numResources;
	vector <vector <int> > allocationMatrix;
	vector <vector <int> > maxMatrix;
	vector <int> availableMatrix;
	vector <vector <int> > needMatrix;
	while (choiceListNum != 4) {
		switch (choiceListNum)
		{
		case 1: {
			vector <vector <int>> need(needMatrix.begin(), needMatrix.end());
			vector <int> work(availableMatrix.begin(), availableMatrix.end());
			vector <bool> finish;
			vector <string> safetySequence;
			//initialize finish matrix with false
			for (int i = 0; i < numProcesses; i++) {
				finish.push_back(false);
			}
			for (int i = 0; i < numProcesses; i++) {
				if (finish[i] == false && compareMatrix(need[i], work)) {
					for (int k = 0; k < numResources; k++) {
						work[k] += allocationMatrix[i][k];
					}
					finish[i] = true;
					safetySequence.push_back("P" + to_string(i));
				}
				if (i == numProcesses - 1) {
					for (int j = 0; j < numProcesses; j++) {
						if (finish[j] == false && compareMatrix(need[j], work)) {
							i = -1;
							break;
						}
					}
				}
			}
			if (allFinishIsTrue(finish)) {
				cout << "The System is in A Safe State." << endl;
				cout << "Safe Sequence: <";
				for (int i = 0; i < safetySequence.size(); i++) {
					cout << safetySequence[i];
					if (i != safetySequence.size() - 1) {
						cout << ",";
					}
				}
				cout << ">" << endl << endl;
			}
			else {
				cout << "The System is NOT in a Safe State." << endl << endl;
			}
			choiceListNum = choiceList();
			break;
		}
		case 2: {
			int processRequestNumber;
			vector <int> requestMatrix;
			cout << "Enter the number of P sending this Request: ";
			cin >> processRequestNumber;
			if (processRequestNumber >= numProcesses) {
				cout << "Invalid Process Number." << endl;
			}
			else {
				cout << "Enter The Request:" << endl;
				for (int i = 0; i < numResources; i++) {
					int entry;
					cin >> entry;
					requestMatrix.push_back(entry);
				}
				if (!compareMatrix(requestMatrix, needMatrix[processRequestNumber])) {
					cout << "ERROR, Process has exceeded its maximum claim." << endl;
				}
				else {
					if (!compareMatrix(requestMatrix, availableMatrix)) {
						cout << "Process must wait since resources are not available." << endl;
					}
					else {
						vector <int> availableRequestMatrix(availableMatrix.begin(), availableMatrix.end());
						vector <vector <int>> allocationRequestMatrix(allocationMatrix.begin(), allocationMatrix.end());
						vector <vector <int>> needRequestMatrix(needMatrix.begin(), needMatrix.end());
						for (int i = 0; i < requestMatrix.size(); i++) {
							availableRequestMatrix[i] -= requestMatrix[i];
						}
						for (int i = 0; i < requestMatrix.size(); i++) {
							allocationRequestMatrix[processRequestNumber][i] += requestMatrix[i];
						}
						for (int i = 0; i < requestMatrix.size(); i++) {
							needRequestMatrix[processRequestNumber][i] -= requestMatrix[i];
						}
						vector <vector <int>> need(needRequestMatrix.begin(), needRequestMatrix.end());
						vector <int> work(availableRequestMatrix.begin(), availableRequestMatrix.end());
						vector <bool> finish;
						vector <string> safetySequence;
						//initialize finish matrix with false
						for (int i = 0; i < numProcesses; i++) {
							finish.push_back(false);
						}
						safetySequence.push_back("P" + to_string(processRequestNumber) + "req");
						for (int i = 0; i < numProcesses; i++) {
							if (finish[i] == false && compareMatrix(need[i], work)) {
								for (int k = 0; k < numResources; k++) {
									work[k] += allocationRequestMatrix[i][k];
								}
								finish[i] = true;
								safetySequence.push_back("P" + to_string(i));
							}
							if (i == numProcesses - 1) {
								for (int j = 0; j < numProcesses; j++) {
									if (finish[j] == false && compareMatrix(need[j], work)) {
										i = -1;
										break;
									}
								}
							}
						}
						if (allFinishIsTrue(finish)) {
							cout << "The System is in A Safe State." << endl;
							cout << "Safe Sequence: <";
							for (int i = 0; i < safetySequence.size(); i++) {
								cout << safetySequence[i];
								if (i != safetySequence.size() - 1) {
									cout << ",";
								}
							}
							cout << ">" << endl << endl;
						}
						else {
							cout << "Reqest is not Granted, The System will NOT be in a Safe State." << endl << endl;
						}

					}
				}
			}
			choiceListNum = choiceList();
			break;
		}
		case 3:
		{
			allocationMatrix.clear();
			maxMatrix.clear();
			availableMatrix.clear();
			needMatrix.clear();
			cout << "Enter Number of Processes: ";
			cin >> numProcesses;
			cout << "Enter Number of resources: ";
			cin >> numResources;
			cout << "Enter Allocation Matrix:" << endl;
			for (int i = 0; i < numProcesses; i++) {
				vector <int> entryMatrix;
				for (int j = 0; j < numResources; j++) {
					int entry;
					cin >> entry;
					entryMatrix.push_back(entry);
				}
				allocationMatrix.push_back(entryMatrix);
			}
			cout << "Enter Max Matrix:" << endl;
			for (int i = 0; i < numProcesses; i++) {
				vector <int> entryMatrix;
				for (int j = 0; j < numResources; j++) {
					int entry;
					cin >> entry;
					entryMatrix.push_back(entry);
				}
				maxMatrix.push_back(entryMatrix);
			}
			cout << "Enter Available Matrix:" << endl;
			for (int i = 0; i < numResources; i++) {
				int entry;
				cin >> entry;
				availableMatrix.push_back(entry);
			}
			//calculate need matrix
			for (int i = 0; i < numProcesses; i++) {
				vector <int> calculatedMatrix;
				for (int j = 0; j < numResources; j++) {
					calculatedMatrix.push_back(maxMatrix[i][j] - allocationMatrix[i][j]);
				}
				needMatrix.push_back(calculatedMatrix);
			}
			//printing need matrix
			cout << "Need Matrix:" << endl;
			for (int i = 0; i < numProcesses; i++) {
				for (int j = 0; j < numResources; j++) {
					cout << needMatrix[i][j] << " ";
				}
				cout << endl;
			}
			choiceListNum = choiceList();
			break;
		}
		case 4:
			break;

		default:
			cout << "Not in The Choice List!" << endl;
			choiceListNum = choiceList();
		}

	}
	cout << "Good Bye ^_^" << endl;
	return 0;
}


