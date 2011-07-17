/*
** Lua binding: color
** Generated automatically by tolua++-1.0.92 on Sat Jul 16 23:04:36 2011.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_color_open (lua_State* tolua_S);

#include "../../Graphics/color.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Uint32 (lua_State* tolua_S)
{
 Uint32* self = (Uint32*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Color32 (lua_State* tolua_S)
{
 Color32* self = (Color32*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"const");
 tolua_usertype(tolua_S,"Color32");
 tolua_usertype(tolua_S,"Uint32");
 tolua_usertype(tolua_S,"Uint8");
}

/* method: R of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_R00
static int tolua_color_Color32_R00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Color32* self = (const Color32*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'R'", NULL);
#endif
  {
   float tolua_ret = (float)  self->R();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'R'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: G of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_G00
static int tolua_color_Color32_G00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Color32* self = (const Color32*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'G'", NULL);
#endif
  {
   float tolua_ret = (float)  self->G();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'G'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: B of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_B00
static int tolua_color_Color32_B00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Color32* self = (const Color32*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'B'", NULL);
#endif
  {
   float tolua_ret = (float)  self->B();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'B'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: A of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_A00
static int tolua_color_Color32_A00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Color32* self = (const Color32*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'A'", NULL);
#endif
  {
   float tolua_ret = (float)  self->A();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'A'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new00
static int tolua_color_Color32_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
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

/* method: new_local of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new00_local
static int tolua_color_Color32_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
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

/* method: new of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new01
static int tolua_color_Color32_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint32",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Uint32 _rgba = *((Uint32*)  tolua_tousertype(tolua_S,2,0));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(_rgba));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new01_local
static int tolua_color_Color32_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint32",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Uint32 _rgba = *((Uint32*)  tolua_tousertype(tolua_S,2,0));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(_rgba));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new02
static int tolua_color_Color32_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"Uint8",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Uint8 _r = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
  Uint8 _g = *((Uint8*)  tolua_tousertype(tolua_S,3,0));
  Uint8 _b = *((Uint8*)  tolua_tousertype(tolua_S,4,0));
  int _a = ((int)  tolua_tonumber(tolua_S,5,255));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(_r,_g,_b,_a));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new02_local
static int tolua_color_Color32_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"Uint8",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Uint8 _r = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
  Uint8 _g = *((Uint8*)  tolua_tousertype(tolua_S,3,0));
  Uint8 _b = *((Uint8*)  tolua_tousertype(tolua_S,4,0));
  int _a = ((int)  tolua_tonumber(tolua_S,5,255));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(_r,_g,_b,_a));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new03
static int tolua_color_Color32_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Color32 const* _copy = ((Color32 const*)  tolua_tousertype(tolua_S,2,0));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(*_copy));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_new03_local
static int tolua_color_Color32_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Color32 const* _copy = ((Color32 const*)  tolua_tousertype(tolua_S,2,0));
  {
   Color32* tolua_ret = (Color32*)  Mtolua_new((Color32)(*_copy));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Color32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_color_Color32_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_Set00
static int tolua_color_Color32_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"Uint8",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"Uint8",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
  Uint8 _r = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
  Uint8 _g = *((Uint8*)  tolua_tousertype(tolua_S,3,0));
  Uint8 _b = *((Uint8*)  tolua_tousertype(tolua_S,4,0));
  int _a = ((int)  tolua_tonumber(tolua_S,5,255));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(_r,_g,_b,_a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetR of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_SetR00
static int tolua_color_Color32_SetR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
  Uint8 _r = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetR'", NULL);
#endif
  {
   self->SetR(_r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetB of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_SetB00
static int tolua_color_Color32_SetB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
  Uint8 _b = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetB'", NULL);
#endif
  {
   self->SetB(_b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetG of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_SetG00
static int tolua_color_Color32_SetG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
  Uint8 _g = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetG'", NULL);
#endif
  {
   self->SetG(_g);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetG'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetA of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_SetA00
static int tolua_color_Color32_SetA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Uint8",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
  Uint8 _a = *((Uint8*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetA'", NULL);
#endif
  {
   self->SetA(_a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRGBA of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32_GetRGBA00
static int tolua_color_Color32_GetRGBA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Color32",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Color32* self = (Color32*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRGBA'", NULL);
#endif
  {
   Uint32 tolua_ret = (Uint32)  self->GetRGBA();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Uint32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Uint32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Uint32));
     tolua_pushusertype(tolua_S,tolua_obj,"Uint32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRGBA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Color32 */
#ifndef TOLUA_DISABLE_tolua_color_Color32__eq00
static int tolua_color_Color32__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Color32",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Color32* self = (const Color32*)  tolua_tousertype(tolua_S,1,0);
  Color32 const* _rhs = ((Color32 const*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*_rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_color_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Color32","Color32","",tolua_collect_Color32);
  #else
  tolua_cclass(tolua_S,"Color32","Color32","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Color32");
   tolua_function(tolua_S,"R",tolua_color_Color32_R00);
   tolua_function(tolua_S,"G",tolua_color_Color32_G00);
   tolua_function(tolua_S,"B",tolua_color_Color32_B00);
   tolua_function(tolua_S,"A",tolua_color_Color32_A00);
   tolua_function(tolua_S,"new",tolua_color_Color32_new00);
   tolua_function(tolua_S,"new_local",tolua_color_Color32_new00_local);
   tolua_function(tolua_S,".call",tolua_color_Color32_new00_local);
   tolua_function(tolua_S,"new",tolua_color_Color32_new01);
   tolua_function(tolua_S,"new_local",tolua_color_Color32_new01_local);
   tolua_function(tolua_S,".call",tolua_color_Color32_new01_local);
   tolua_function(tolua_S,"new",tolua_color_Color32_new02);
   tolua_function(tolua_S,"new_local",tolua_color_Color32_new02_local);
   tolua_function(tolua_S,".call",tolua_color_Color32_new02_local);
   tolua_function(tolua_S,"new",tolua_color_Color32_new03);
   tolua_function(tolua_S,"new_local",tolua_color_Color32_new03_local);
   tolua_function(tolua_S,".call",tolua_color_Color32_new03_local);
   tolua_function(tolua_S,"Set",tolua_color_Color32_Set00);
   tolua_function(tolua_S,"SetR",tolua_color_Color32_SetR00);
   tolua_function(tolua_S,"SetB",tolua_color_Color32_SetB00);
   tolua_function(tolua_S,"SetG",tolua_color_Color32_SetG00);
   tolua_function(tolua_S,"SetA",tolua_color_Color32_SetA00);
   tolua_function(tolua_S,"GetRGBA",tolua_color_Color32_GetRGBA00);
   tolua_function(tolua_S,".eq",tolua_color_Color32__eq00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_color (lua_State* tolua_S) {
 return tolua_color_open(tolua_S);
};
#endif

