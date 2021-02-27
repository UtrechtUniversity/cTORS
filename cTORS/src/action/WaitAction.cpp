#include "Action.h"
#include "State.h"

void WaitAction::Start(State* state) const {
	state->SetWaiting(GetShuntingUnit(), true);
}

void WaitAction::Finish(State* state) const {
	auto su = GetShuntingUnit();
	if(state->HasShuntingUnit(su))
		state->SetWaiting(su, false);
}

const string WaitAction::toString() const {
	return "Wait " + su->toString() + " for " + to_string(duration) + " seconds";
}

const Action* WaitActionGenerator::Generate(const State* state, const SimpleAction& action) const {
	auto su = action.GetShuntingUnit();
	auto e = state->PeekEvent();
	if (!state->HasShuntingUnit(su)) throw InvalidActionException("The shuntingUnit does not exist.");
	if (state->IsWaiting(su)) throw InvalidActionException("The ShuntingUnit is already waiting.");
	if (state->HasActiveAction(su)) throw InvalidActionException("The ShuntingUnit is already executing an action.");
	if(e == nullptr || e->GetTime() == state->GetTime()) throw InvalidActionException("There is nothing to wait for.");
	int dif = e->GetTime() - state->GetTime();
	//if (dif > 30) dif = 30;
	return new WaitAction(su, dif);
}

void WaitActionGenerator::Generate(const State* state, list<const Action*>& out) const {
	if(state->GetTime()==state->GetEndTime()) return;
	auto& sus = state->GetShuntingUnits();
	auto e = state->PeekEvent();
	if (e == nullptr || e->GetTime() == state->GetTime()) return;
	for (auto su : sus) {
		if (state->IsWaiting(su) || state->HasActiveAction(su)) continue;
		out.push_back(Generate(state, Wait(su)));
	}
}