//
//  activity.cpp
//  HW3
//
//  Created by Nils Streedain on 4/29/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

void merge(std::deque<std::deque<int>>& v, int const l, int const m, int const r) {
	std::deque<std::deque<int>> temp;
	
	int i = l, j = m + 1;
	while (i <= m || j <= r)
		temp.push_back(v[i <= m && (j > r || v[i][1] > v[j][1]) ? i++ : j++]);
	
	for (int k = l; k <= r; k++)
		v[k] = temp[k - l];
}

void mergeSort(std::deque<std::deque<int>>& v, int const l, int const r) {
	if (l >= r)
		return;
	
	int m = (l + r) / 2;
	mergeSort(v, l, m);
	mergeSort(v, m + 1, r);
	merge(v, l, m, r);
}

int main(int argc, const char * argv[]) {
	// Create input stream from file
	std::ifstream is("act.txt");
	int set = 0;
	int n;
	// Loop while file stream is open
	while (is >> n) {
		set++;
		
//		std::vector<std::vector<int>> activities(n - 1, std::vector<int>(3));
		std::deque<std::deque<int>> activities;
		for (int i = 0; i < n; i++) {
			int curr;
			std::deque<int> temp;
			for (int j = 0; j < 3; j++) {
				is >> curr;
				temp.push_back(curr);
			}
			activities.push_back(temp);
		}
		
		// sort
		mergeSort(activities, 0, (int)activities.size() - 1);
		
		// find solution
		std::deque<std::deque<int>> finals;
		while (activities.size() > 0) {
			finals.push_back(activities[0]);
			activities.pop_front();
			
			int size = finals.size() - 1;
			if (size > 0 && finals[size][2] > finals[size - 1][1])
				finals.pop_back();
		}
		
		printf("Set %i\nMaximum number of activities = %i\n", set, (int)finals.size());
		for (int i = (int)finals.size() - 1; i >= 0; i--)
			printf(" %i", finals[i][0]);
		printf("\n\n");
	}
	// Close file after while loop
   is.close();
}
