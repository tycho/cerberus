/*
** Lua binding: attribute
** Generated automatically by tolua++-1.0.92 on Sun Jul 17 20:15:41 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_attribute_open (lua_State* tolua_S);

#include "../../Entity/attribute.h"
#include "../../Entity/Attributes/attribute_color.h"
#include "../../Entity/Attributes/attribute_position.h"
#include "../../Entity/Attributes/attribute_sprite.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ColorAttribute");
 tolua_usertype(tolua_S,"Color32");
 tolua_usertype(tolua_S,"PositionAttribute");
 tolua_usertype(tolua_S,"SpriteAttribute");
 tolua_usertype(tolua_S,"Rect");
 tolua_usertype(tolua_S,"Attribute");
 tolua_usertype(tolua_S,"Component");
}

/* method: GetColor of class  ColorAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_ColorAttribute_GetColor00
static int tolua_attribute_ColorAttribute_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ColorAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ColorAttribute* self = (ColorAttribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   Color32& tolua_ret = (Color32&)  self->GetColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Color32");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  ColorAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_ColorAttribute_SetColor00
static int tolua_attribute_ColorAttribute_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ColorAttribute",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Color32",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ColorAttribute* self = (ColorAttribute*)  tolua_tousertype(tolua_S,1,0);
  Color32* _color = ((Color32*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(*_color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  PositionAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_PositionAttribute_GetPosition00
static int tolua_attribute_PositionAttribute_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PositionAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PositionAttribute* self = (PositionAttribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   Rect& tolua_ret = (Rect&)  self->GetPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Rect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  PositionAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_PositionAttribute_SetPosition00
static int tolua_attribute_PositionAttribute_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PositionAttribute",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PositionAttribute* self = (PositionAttribute*)  tolua_tousertype(tolua_S,1,0);
  Rect* _position = ((Rect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(*_position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpritePath of class  SpriteAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_SpriteAttribute_GetSpritePath00
static int tolua_attribute_SpriteAttribute_GetSpritePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteAttribute",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteAttribute* self = (SpriteAttribute*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpritePath'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetSpritePath();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpritePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpritePath of class  SpriteAttribute */
#ifndef TOLUA_DISABLE_tolua_attribute_SpriteAttribute_SetSpritePath00
static int tolua_attribute_SpriteAttribute_SetSpritePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteAttribute",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteAttribute* self = (SpriteAttribute*)  tolua_tousertype(tolua_S,1,0);
  const char* _spritePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpritePath'", NULL);
#endif
  {
   self->SetSpritePath(_spritePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpritePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_attribute_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Attribute","Attribute","Component",NULL);
  tolua_beginmodule(tolua_S,"Attribute");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ColorAttribute","ColorAttribute","Attribute",NULL);
  tolua_beginmodule(tolua_S,"ColorAttribute");
   tolua_function(tolua_S,"GetColor",tolua_attribute_ColorAttribute_GetColor00);
   tolua_function(tolua_S,"SetColor",tolua_attribute_ColorAttribute_SetColor00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PositionAttribute","PositionAttribute","Attribute",NULL);
  tolua_beginmodule(tolua_S,"PositionAttribute");
   tolua_function(tolua_S,"GetPosition",tolua_attribute_PositionAttribute_GetPosition00);
   tolua_function(tolua_S,"SetPosition",tolua_attribute_PositionAttribute_SetPosition00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SpriteAttribute","SpriteAttribute","Attribute",NULL);
  tolua_beginmodule(tolua_S,"SpriteAttribute");
   tolua_function(tolua_S,"GetSpritePath",tolua_attribute_SpriteAttribute_GetSpritePath00);
   tolua_function(tolua_S,"SetSpritePath",tolua_attribute_SpriteAttribute_SetSpritePath00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_attribute (lua_State* tolua_S) {
 return tolua_attribute_open(tolua_S);
};
#endif

