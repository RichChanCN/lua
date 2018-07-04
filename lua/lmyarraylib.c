/*
** 自定义数组类型 Rich Cheng
*/

#define lmyarraylib_c
#define LUA_LIB

#include "lprefix.h"


#include <stdlib.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


typedef struct NumArray{
    int size;
    double values[1];
} NumArray;

static int newarray(lua_State* L){
    int n = luaL_checkinteger(L, 1);
    size_t nbytes = sizeof(NumArray)+(n - 1)*sizeof(double);
    NumArray *a = (NumArray *)lua_newuserdata(L, nbytes);
    a->size = n;
    return 1;
}

static int setarray(lua_State *L){
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkinteger(L, 2);
    double value = luaL_checknumber(L, 3);

    luaL_argcheck(L, a != NULL, 1, "'arry' expected");

    luaL_argcheck(L, 1 <= index&&index <= a->size, 2, "index out of range");

    a->values[index - 1] = value;
    
    return 0;
}

static int getarray(lua_State* L){
    NumArray *a = (NumArray *)lua_touserdata(L, 1);
    int index = luaL_checkinteger(L, 2);
    
    luaL_argcheck(L, a != NULL, 1, "'arry' expected");

    luaL_argcheck(L, 1 <= index&&index <= a->size, 2, "index out of range");

    lua_pushnumber(L, a->values[index - 1]);
    
    return 1;
}

static int getsize(lua_State *L){
    NumArray* a = (NumArray *)lua_touserdata(L, 1);

    luaL_argcheck(L, a != NULL, 1, "'arry' expected");
    lua_pushnumber(L, a->size);

    return 1;
}

static const struct luaL_Reg myarraylib[] = {
    { "new", newarray },
    { "set", setarray },
    { "get", getarray },
    { "size",getsize },
    { NULL,NULL }
};

int luaopen_myarray(lua_State *L){

    luaL_newlib(L, myarraylib);

    return 1;
}

