/*
** Lua binding: behavior
** Generated automatically by tolua++-1.0.92 on Sun Jul 17 20:15:41 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_behavior_open (lua_State* tolua_S);

#include "../../Entity/behavior.h"
#include "../../Entity/Behaviors/behavior_input.h"
#include "../../Entity/Behaviors/behavior_physics.h"
#include "../../Entity/Behaviors/behavior_render.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"Vector");
 tolua_usertype(tolua_S,"PhysicsBehavior");
 tolua_usertype(tolua_S,"Behavior");
}

/* method: IsCollidable of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_IsCollidable00
static int tolua_behavior_PhysicsBehavior_IsCollidable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCollidable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsCollidable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCollidable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGravity of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_GetGravity00
static int tolua_behavior_PhysicsBehavior_GetGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGravity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetGravity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVelocity of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_GetVelocity00
static int tolua_behavior_PhysicsBehavior_GetVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVelocity'", NULL);
#endif
  {
   Vector& tolua_ret = (Vector&)  self->GetVelocity();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAcceleration of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_GetAcceleration00
static int tolua_behavior_PhysicsBehavior_GetAcceleration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAcceleration'", NULL);
#endif
  {
   Vector& tolua_ret = (Vector&)  self->GetAcceleration();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Vector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAcceleration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCollidable of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_SetCollidable00
static int tolua_behavior_PhysicsBehavior_SetCollidable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
  bool _collidable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCollidable'", NULL);
#endif
  {
   self->SetCollidable(_collidable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCollidable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGravity of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_SetGravity00
static int tolua_behavior_PhysicsBehavior_SetGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
  float _gravity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGravity'", NULL);
#endif
  {
   self->SetGravity(_gravity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVelocity of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_SetVelocity00
static int tolua_behavior_PhysicsBehavior_SetVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
  Vector* _velocity = ((Vector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVelocity'", NULL);
#endif
  {
   self->SetVelocity(*_velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAcceleration of class  PhysicsBehavior */
#ifndef TOLUA_DISABLE_tolua_behavior_PhysicsBehavior_SetAcceleration00
static int tolua_behavior_PhysicsBehavior_SetAcceleration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBehavior",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBehavior* self = (PhysicsBehavior*)  tolua_tousertype(tolua_S,1,0);
  Vector* _acceleration = ((Vector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAcceleration'", NULL);
#endif
  {
   self->SetAcceleration(*_acceleration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAcceleration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_behavior_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Behavior","Behavior","Component",NULL);
  tolua_beginmodule(tolua_S,"Behavior");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PhysicsBehavior","PhysicsBehavior","Behavior",NULL);
  tolua_beginmodule(tolua_S,"PhysicsBehavior");
   tolua_function(tolua_S,"IsCollidable",tolua_behavior_PhysicsBehavior_IsCollidable00);
   tolua_function(tolua_S,"GetGravity",tolua_behavior_PhysicsBehavior_GetGravity00);
   tolua_function(tolua_S,"GetVelocity",tolua_behavior_PhysicsBehavior_GetVelocity00);
   tolua_function(tolua_S,"GetAcceleration",tolua_behavior_PhysicsBehavior_GetAcceleration00);
   tolua_function(tolua_S,"SetCollidable",tolua_behavior_PhysicsBehavior_SetCollidable00);
   tolua_function(tolua_S,"SetGravity",tolua_behavior_PhysicsBehavior_SetGravity00);
   tolua_function(tolua_S,"SetVelocity",tolua_behavior_PhysicsBehavior_SetVelocity00);
   tolua_function(tolua_S,"SetAcceleration",tolua_behavior_PhysicsBehavior_SetAcceleration00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_behavior (lua_State* tolua_S) {
 return tolua_behavior_open(tolua_S);
};
#endif

