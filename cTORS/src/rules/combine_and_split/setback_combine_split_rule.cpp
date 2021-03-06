#include "BusinessRules.h"

/**
 * Validates a SplitAction or CombineAction for the given state. 
 * The SplitAction or CombineAction is invalid iff
 * 1. The ShuntingUnit's current Track does not allow for set back operations.
 * @return A pair describing 1) whether the action is valid, and 2) if not, why
 */
pair<bool, string> setback_combine_split_rule::IsValid(const State* state, const Action* action) const {
	if(!instanceof<SplitAction>(action) && !instanceof<CombineAction>(action)) return make_pair(true, "");
	auto su = action->GetShuntingUnit();
	auto track = state->GetPosition(su);
	if(!track->sawMovementAllowed)
		return make_pair(false, "Shunting unit " + su->toString() + " is not allowed to combine/split on track "
			+ track->toString() + " because it is not a setback track.");
	return make_pair(true, "");
}