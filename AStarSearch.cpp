//Bruno Clemente e Thyago Stall
#include "AStarSearch.hpp"
#include <algorithm>

std::vector<State> AStarSearch::find() {
	std::vector<State> path;
	std::vector<State*> open_states;
	open_states.push_back(&start_state);
	State *cursor_state = open_states[0];

	bool path_found = false;
	while(!path_found) {
		for(auto s: cursor_state->expand()) {
			if (!(s == open_states)) {
				addState(open_states, cursor_state, s);
				continue;
			}
			auto old_state = *std::find(open_states.begin(), open_states.end(), s);
			if (s.getCost() < old_state->getCost()) {
				old_state->setCost(s.getCost());
				old_state->setMother(cursor_state);
			}
		}
		open_states.erase(open_states.begin());
		std::sort(open_states.begin(), open_states.end());
		cursor_state = open_states[0];
		if (*cursor_state == end_states)
			path_found = true;
	}

	return createVector(cursor_state);
}

void AStarSearch::addState(std::vector<State *> &open_states, State *cursor_state, const State &s) const {
	auto state = new State(s);
	state->setMother(cursor_state);
	open_states.push_back(state);
}

std::vector<State> AStarSearch::createVector(State *state) {
	std::vector<State> returner;
	State *cursor = state;
	while (cursor != NULL) {
		returner.push_back(State(*cursor));
		cursor = cursor->getMother();
	}

	std::reverse(returner.begin(), returner.end());
	return returner;
}
