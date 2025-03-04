#pragma once
#ifndef AVATAR_ACTION_H
#define AVATAR_ACTION_H

#include "enums.h"
#include "optional.h"

class avatar;
class item;
class map;

struct point;
struct targeting_data;

namespace avatar_action
{
// Standard movement; handles attacks, traps, &c. Returns false if auto move
// should be canceled
bool move( avatar &you, map &m, int dx, int dy, int dz = 0 );
inline bool move( avatar &you, map &m, const tripoint &d )
{
    return move( you, m, d.x, d.y, d.z );
}
inline bool move( avatar &you, map &m, const point &d )
{
    return move( you, m, d.x, d.y );
}

// Handle moving from a ramp
bool ramp_move( avatar &you, map &m, const tripoint &dest );

/** Handles swimming by the player. Called by avatar_action::move(). */
void swim( map &m, avatar &you, const tripoint &p );

void autoattack( avatar &you, map &m );

/**
 * Returns true if the player is allowed to fire a given item, or false if otherwise.
 * reload_time is stored as a side effect of condition testing.
 * @param args Contains item data and targeting mode for the gun we want to fire.
 * @return True if all conditions are true, otherwise false.
 */
bool fire_check( avatar &you, const map &m, const targeting_data &args );

/**
 * Handles interactive parts of gun firing (target selection, etc.).
 * @return Whether an attack was actually performed.
 */
bool fire( avatar &you, map &m );
/**
 * Handles interactive parts of gun firing (target selection, etc.).
 * This version stores targeting parameters for weapon, used for calls to the nullary form.
 * @param weapon Reference to a weapon we want to start aiming.
 * @param bp_cost The amount by which the player's power reserve is decreased after firing.
 * @return Whether an attack was actually performed.
 */
bool fire( avatar &you, map &m, item &weapon, int bp_cost = 0 );
// Throw an item  't'
void plthrow( avatar &you, int pos = INT_MIN,
              const cata::optional<tripoint> &blind_throw_from_pos = cata::nullopt );
}

#endif // !AVATAR_MOVE_H
