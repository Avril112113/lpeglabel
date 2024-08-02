#include "lua.h"
#include "lpltypes.h"


#if (LUA_VERSION_NUM == 501)
const char *luaL_tolstring (lua_State *L, int idx, size_t *len) {
  if (!luaL_callmeta(L, idx, "__tostring")) {
    int t = lua_type(L, idx);
    switch (t) {
      case LUA_TNIL:
        lua_pushliteral(L, "nil");
        break;
      case LUA_TSTRING:
      case LUA_TNUMBER:
        lua_pushvalue(L, idx);
        break;
      case LUA_TBOOLEAN:
        if (lua_toboolean(L, idx))
          lua_pushliteral(L, "true");
        else
          lua_pushliteral(L, "false");
        break;
      default:
        lua_pushfstring(L, "%s: %p", lua_typename(L, t),
                                     lua_topointer(L, idx));
        break;
    }
  }
  return lua_tolstring(L, -1, len);
}
#endif
