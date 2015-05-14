//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine 
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <types.h>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////
//////  DATA STRUCTURES
//////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//
// Possible statuses of an animation
//
typedef enum {
   as_play,    // Playing till the last frame
   as_cycle,   // Playing continuosly
   as_pause,   // Paused, waiting to continue
   as_end      // Animation has ended
} TAnimStatus;

//
// Description of an animation frame
//
typedef struct {
   u8* sprite;        // Sprite associated to this frame
   u8  width, height; // Sprite dimensions in bytes
   u8  time;          // Time that the sprite should be shown
} TAnimFrame;

//
// Describes an Animation as a secuence of sprites, controlled by time
//   Time is measured in main loop cycles
//
typedef struct {
   TAnimFrame**  frames;    // Vector containing all the frames of the animation
   u8            frame_id;  // Index of the current frame
   u8            time;      // Remaining time for this frame
   TAnimStatus   status;    // Status of the animation
} TAnimation;

//
// Possible statuses of an entity
//
typedef enum {
   es_static = 0, // Entity that does not move
   es_walk,       // Entity walking
   es_jump,       // Entity jumping
   es_hit,        // Entity is being hit
   es_NUMSTATUSES // Total amount of statuses available
} TCharacterStatus;

//
// Entities can be heading both sides
//
typedef enum { s_left = 0, s_right, s_NUMSIDES } TCharacterSide;

//
// Describes physical behaviour for an object
//
typedef struct {
   u16   x,  y;  // X, Y coordinates of entity in a subpixel world (in pixels*SCALE)
   i16  vx, vy;  // Velocity vector controlling entity movement (In pixels*SCALE)
   u16  bounce;  // Bounce coefficient (In pixels*SCALE. < SCALE absorves energy, > SCALE gives energy)
} TPhysics;

//
// Information for solid objects that occupy a rectangular space in the screen
//
typedef struct {
   u8   w, h;   // Width and height in bytes
   u8 colour;   // Colour pattern use for drawing
} TBlock;

//
// Describes a game entity
//
typedef struct {
   // Entities have an animation or a solid rectangular block 
   union {
      TAnimation  anim;    // Animation currently associated with this entity
      TBlock      block;   // Definition of a rectangular block in the screen
   } graph;

   u8        *pscreen;  // Pointer to Screen Video memory location where entity will be drawn
   u8           x,  y;  // X, Y coordinates of entity in the screen (in bytes)
   u8          nx, ny;  // Next X, Y coordinates of entity in the screen (in bytes)
   TPhysics      phys;  // Values for entities that have Physical components
} TEntity;

//
// Describes a game character (the main character, for instance)
//
typedef struct {
   TEntity           entity;  // Entity model for this character
   TCharacterStatus  status;  // Present status of the character
   TCharacterSide    side;    // Side the character is facing
} TCharacter;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////
//////  UTILITY FUNCTIONS
//////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

    void initializeEntities();
    void setEntityLocation(TEntity *e, u8 x, u8 y, u8 vx, u8 vy);
    void setAnimation (TEntity *ent, TAnimFrame** animation, TAnimStatus status);
    void setCharacterAnim(TCharacter *ch, TCharacterStatus newstatus, TCharacterSide newside);
    void updateEntity (TEntity *ent);
    void drawEntity   (TEntity *ent);
    void drawAll      ();
TEntity* newSolidBlock(u8 x, u8 y, u8 width, u8 height, u8 colour);
