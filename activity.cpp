//
//  activity.cpp
//  HW3
//
//  Created by Nils Streedain on 4/29/22.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <vector>

// Last To Start comparitor for the priority queue in main. Sorts based on the
// last of two activities to start.
struct lastToStart {
	bool operator()(const std::vector<int>& l, const std::vector<int>& r) const {
		return l[1] < r[1];
	}
};

// Main function for homework 3, activity.cpp
int main(int argc, const char * argv[]) {
	// Open file and loop while not at end
	std::ifstream is("act.txt");
	int n;
	for (int set = 1; is >> n; set++) {
		// Create priority queue of vectors, containing integers.
		std::priority_queue<std::vector<int>,
			std::deque<std::vector<int>>, lastToStart> activities;
		
		// Loop over the number of activities, parsing values for each.
		for (int i = 0, curr; i < n; i++) {
			std::vector<int> temp;						// create temp vector
			for (int j = 0; j < 3 && is >> curr; j++)	// populate the elements
				temp.push_back(curr);						// of vector
			activities.push(temp);						// push vector to queue
		}
		
		// Deque to store activity selection last to start final results
		std::deque<std::vector<int>> finals;
		
		// Loop over each activity
		while (activities.size() > 0) {
			// Move activity to deque
			finals.push_back(activities.top());
			activities.pop();
			
			// Remove from deque if not compatible
			int size = (int)finals.size() - 1;
			if (size > 0 && finals[size][2] > finals[size - 1][1])
				finals.pop_back();
		}
		
		// Print final results
		printf("Set %i\nMaximum number of activities = %i\n",
			   set, (int)finals.size());
		for (int i = (int)finals.size() - 1; i >= 0; i--)
			printf(" %i", finals[i][0]);
		printf("\n\n");
	}
	// Close file after while loop
   is.close();
}
