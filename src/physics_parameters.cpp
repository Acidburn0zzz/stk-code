//  $Id$
//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "physics_parameters.hpp"

PhysicsParameters* physicsParameters=0;

// -----------------------------------------------------------------------------
void PhysicsParameters::load(const std::string filename) {

  KartProperties::load(filename, "physics");

  // Check that all necessary values are indeed set physics.data file


#define CHECK_NEG(  a,strA) if(a<-99) {                                    \
             fprintf(stderr,"Missing default value for '%s' in '%s'.\n",   \
		     strA,filename);exit(-1);                       \
             }

  CHECK_NEG(corn_r,   "corn_r"   );CHECK_NEG(wheel_base,     "wheel-base"     );
  CHECK_NEG(heightCOG,"heightCOG");CHECK_NEG(engine_power,   "engine-power"   );
  CHECK_NEG(mass,     "mass"     );CHECK_NEG(air_resistance, "air-resistance" );
  CHECK_NEG(tire_grip,"tire-grip");CHECK_NEG(max_steer_angle,"max-steer-angle");
  CHECK_NEG(corn_f,   "corn_f"   );CHECK_NEG(roll_resistance,"roll-resistance");
  CHECK_NEG(inertia,  "inertia"  );CHECK_NEG(magnetRangeSQ,  "magnet-range"   );
  CHECK_NEG(brake_factor,        "brake-factor"           );
  CHECK_NEG(jumpImpulse,         "jump-impulse"           );
  CHECK_NEG(airResReduce[1],     "reduce-air-resistance-driver");
  CHECK_NEG(airResReduce[2],     "reduce-air-resistance-racer" );
  CHECK_NEG(wheelieMaxSpeedRatio,"wheelie-max-speed-ratio");
  CHECK_NEG(wheelieMaxPitch,     "wheelie-max-pitch"      );
  CHECK_NEG(wheeliePitchRate,    "wheelie-pitch-rate"     );
  CHECK_NEG(wheelieRestoreRate,  "wheelie-restore-rate"   );
  CHECK_NEG(wheelieSpeedBoost,   "wheelie-speed-boost"    );
  CHECK_NEG(magnetMinRangeSQ,    "magnet-min-range"       );
  CHECK_NEG(parachuteFriction,   "parachute-friction"     );
  CHECK_NEG(time_full_steer,     "time-full-steer"        );

  // Precompute some handy values to reduce work later
  magnetRangeSQ    = magnetRangeSQ   *magnetRangeSQ;
  magnetMinRangeSQ = magnetMinRangeSQ*magnetMinRangeSQ;
}   // load

// -----------------------------------------------------------------------------
// Init all values with invalid defaults, which are tested later. This 
// guarantees that all parameters will indeed be initialised, and helps
// finding typos.
void PhysicsParameters::init_defaults() {
  wheel_base         = heightCOG         = magnetMinRangeSQ  = roll_resistance = 
    mass             = corn_r            =
    air_resistance   = tire_grip         = max_steer_angle   = corn_f          = 
    inertia          = anvilWeight       = parachuteFriction = engine_power    =
    magnetRangeSQ    = jumpImpulse       = brake_factor      = anvilSpeedFactor=
    time_full_steer  = wheelieMaxPitch   = wheelieMaxSpeedRatio                =
    wheeliePitchRate = wheelieRestoreRate= wheelieSpeedBoost = airResReduce[2] =
    airResReduce[1]  = -99.9f;
  airResReduce[0]    = 1.0f;
}   // init_defaults

// -----------------------------------------------------------------------------
void PhysicsParameters::getAllData(const lisp::Lisp* lisp) {

  // Get the values which are not part of the default KartProperties
  // ---------------------------------------------------------------
  lisp->get("anvil-weight",                 anvilWeight         );
  lisp->get("anvil-speed-factor",           anvilSpeedFactor    );
  lisp->get("parachute-friction",           parachuteFriction   );
  lisp->get("magnet-range",                 magnetRangeSQ       );
  lisp->get("magnet-min-range",             magnetMinRangeSQ    );
  lisp->get("jump-impulse",                 jumpImpulse         );
  lisp->get("reduce-air-resistance-racer",  airResReduce[2]     );
  lisp->get("reduce-air-resistance-driver", airResReduce[1]     );

  // Get the default KartProperties
  // ------------------------------
  KartProperties::getAllData(lisp->getLisp("kart-defaults"));
}   // getAllData
