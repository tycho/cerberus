/*
** Lua binding: vector
** Generated automatically by tolua++-1.0.92 on Sun Jul 17 20:15:41 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_vector_open (lua_State* tolua_S);

#include "../../Graphics/vector.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Vector (lua_State* tolua_S)
{
 Vector* self = (Vector*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Vector");
}

/* get function: x of class  Vector */
#ifndef TOLUA_DISABLE_tolua_get_Vector_x
static int tolua_get_Vector_x(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  Vector */
#ifndef TOLUA_DISABLE_tolua_set_Vector_x
static int tolua_set_Vector_x(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  Vector */
#ifndef TOLUA_DISABLE_tolua_get_Vector_y
static int tolua_get_Vector_y(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  Vector */
#ifndef TOLUA_DISABLE_tolua_set_Vector_y
static int tolua_set_Vector_y(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  Vector */
#ifndef TOLUA_DISABLE_tolua_get_Vector_z
static int tolua_get_Vector_z(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  Vector */
#ifndef TOLUA_DISABLE_tolua_set_Vector_z
static int tolua_set_Vector_z(lua_State* tolua_S)
{
  Vector* self = (Vector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new00
static int tolua_vector_Vector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new00_local
static int tolua_vector_Vector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new01
static int tolua_vector_Vector_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)(_x,_y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_vector_Vector_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new01_local
static int tolua_vector_Vector_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)(_x,_y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_vector_Vector_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new02
static int tolua_vector_Vector_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  float _z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)(_x,_y,_z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_vector_Vector_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Vector */
#ifndef TOLUA_DISABLE_tolua_vector_Vector_new02_local
static int tolua_vector_Vector_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Vector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
  float _z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   Vector* tolua_ret = (Vector*)  Mtolua_new((Vector)(_x,_y,_z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Vector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_vector_Vector_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_vector_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Vector","Vector","",tolua_collect_Vector);
  #else
  tolua_cclass(tolua_S,"Vector","Vector","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Vector");
   tolua_variable(tolua_S,"x",tolua_get_Vector_x,tolua_set_Vector_x);
   tolua_variable(tolua_S,"y",tolua_get_Vector_y,tolua_set_Vector_y);
   tolua_variable(tolua_S,"z",tolua_get_Vector_z,tolua_set_Vector_z);
   tolua_function(tolua_S,"new",tolua_vector_Vector_new00);
   tolua_function(tolua_S,"new_local",tolua_vector_Vector_new00_local);
   tolua_function(tolua_S,".call",tolua_vector_Vector_new00_local);
   tolua_function(tolua_S,"new",tolua_vector_Vector_new01);
   tolua_function(tolua_S,"new_local",tolua_vector_Vector_new01_local);
   tolua_function(tolua_S,".call",tolua_vector_Vector_new01_local);
   tolua_function(tolua_S,"new",tolua_vector_Vector_new02);
   tolua_function(tolua_S,"new_local",tolua_vector_Vector_new02_local);
   tolua_function(tolua_S,".call",tolua_vector_Vector_new02_local);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_vector (lua_State* tolua_S) {
 return tolua_vector_open(tolua_S);
};
#endif

