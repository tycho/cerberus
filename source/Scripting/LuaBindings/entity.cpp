/*
** Lua binding: entity
** Generated automatically by tolua++-1.0.92 on Sat Jul 16 23:04:36 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_entity_open (lua_State* tolua_S);

#include "../../Entity/entity.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Behavior");
 tolua_usertype(tolua_S,"Attribute");
 tolua_usertype(tolua_S,"Entity");
}

/* method: GetName of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_GetName00
static int tolua_entity_Entity_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasBehavior of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_HasBehavior00
static int tolua_entity_Entity_HasBehavior00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasBehavior'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasBehavior(_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasBehavior'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBehavior of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_GetBehavior00
static int tolua_entity_Entity_GetBehavior00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBehavior'", NULL);
#endif
  {
   Behavior* tolua_ret = (Behavior*)  self->GetBehavior(_name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Behavior");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBehavior'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBehavior of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_AddBehavior00
static int tolua_entity_Entity_AddBehavior00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Behavior",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
  Behavior* _behavior = ((Behavior*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBehavior'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddBehavior(_name,_behavior);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBehavior'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveBehavior of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_RemoveBehavior00
static int tolua_entity_Entity_RemoveBehavior00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveBehavior'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveBehavior(_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveBehavior'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasAttribute of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_HasAttribute00
static int tolua_entity_Entity_HasAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasAttribute(_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttribute of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_GetAttribute00
static int tolua_entity_Entity_GetAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttribute'", NULL);
#endif
  {
   Attribute* tolua_ret = (Attribute*)  self->GetAttribute(_name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Attribute");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAttribute of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_AddAttribute00
static int tolua_entity_Entity_AddAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Attribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
  Attribute* _attribute = ((Attribute*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddAttribute(_name,_attribute);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAttribute of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_RemoveAttribute00
static int tolua_entity_Entity_RemoveAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveAttribute(_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_GetParent00
static int tolua_entity_Entity_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   Entity* tolua_ret = (Entity*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Entity");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_GetChild00
static int tolua_entity_Entity_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  int _index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   Entity* tolua_ret = (Entity*)  self->GetChild(_index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Entity");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AttachChild of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_AttachChild00
static int tolua_entity_Entity_AttachChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  Entity* _child = ((Entity*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttachChild'", NULL);
#endif
  {
   self->AttachChild(_child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttachChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  Entity */
#ifndef TOLUA_DISABLE_tolua_entity_Entity_RemoveChild00
static int tolua_entity_Entity_RemoveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  Entity* _child = ((Entity*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'", NULL);
#endif
  {
   self->RemoveChild(_child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_entity_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Entity","Entity","",NULL);
  tolua_beginmodule(tolua_S,"Entity");
   tolua_function(tolua_S,"GetName",tolua_entity_Entity_GetName00);
   tolua_function(tolua_S,"HasBehavior",tolua_entity_Entity_HasBehavior00);
   tolua_function(tolua_S,"GetBehavior",tolua_entity_Entity_GetBehavior00);
   tolua_function(tolua_S,"AddBehavior",tolua_entity_Entity_AddBehavior00);
   tolua_function(tolua_S,"RemoveBehavior",tolua_entity_Entity_RemoveBehavior00);
   tolua_function(tolua_S,"HasAttribute",tolua_entity_Entity_HasAttribute00);
   tolua_function(tolua_S,"GetAttribute",tolua_entity_Entity_GetAttribute00);
   tolua_function(tolua_S,"AddAttribute",tolua_entity_Entity_AddAttribute00);
   tolua_function(tolua_S,"RemoveAttribute",tolua_entity_Entity_RemoveAttribute00);
   tolua_function(tolua_S,"GetParent",tolua_entity_Entity_GetParent00);
   tolua_function(tolua_S,"GetChild",tolua_entity_Entity_GetChild00);
   tolua_function(tolua_S,"AttachChild",tolua_entity_Entity_AttachChild00);
   tolua_function(tolua_S,"RemoveChild",tolua_entity_Entity_RemoveChild00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_entity (lua_State* tolua_S) {
 return tolua_entity_open(tolua_S);
};
#endif

