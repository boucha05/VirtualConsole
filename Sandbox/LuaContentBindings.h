// Warning: this file is generated automatically!!!

int lua_function_importbinary(lua_State* state)
{
    if(!check_stack_size(state, 1)) return lua_error(state);
    const char* arg_filename; if(!read(state, 1, arg_filename)) return lua_error(state);
    void* result = get_context(state).importbinary(arg_filename);
    push(state, result);
    return 1;
}

const struct luaL_Reg lua_functions[] = {
    {"importbinary", lua_function_importbinary},
    {NULL, NULL},
};

