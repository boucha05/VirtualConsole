// Warning: this file is generated automatically!!!

int lua_function_flip(lua_State* state)
{
    if(!check_stack_size(state, 0)) return lua_error(state);
    get_context(state).flip();
    return 0;
}

int lua_function_clip(lua_State* state)
{
    if(!check_stack_size(state, 4)) return lua_error(state);
    int arg_x; if(!read(state, 1, arg_x)) return lua_error(state);
    int arg_y; if(!read(state, 2, arg_y)) return lua_error(state);
    int arg_w; if(!read(state, 3, arg_w)) return lua_error(state);
    int arg_h; if(!read(state, 4, arg_h)) return lua_error(state);
    get_context(state).clip(arg_x, arg_y, arg_w, arg_h);
    return 0;
}

int lua_function_color(lua_State* state)
{
    if(!check_stack_size(state, 1)) return lua_error(state);
    int arg_value; if(!read(state, 1, arg_value)) return lua_error(state);
    get_context(state).color(arg_value);
    return 0;
}

int lua_function_colorcount(lua_State* state)
{
    if(!check_stack_size(state, 1)) return lua_error(state);
    int arg_value; if(!read(state, 1, arg_value)) return lua_error(state);
    get_context(state).colorcount(arg_value);
    return 0;
}

int lua_function_colortable(lua_State* state)
{
    if(!check_stack_size(state, 4)) return lua_error(state);
    int arg_index; if(!read(state, 1, arg_index)) return lua_error(state);
    int arg_r; if(!read(state, 2, arg_r)) return lua_error(state);
    int arg_g; if(!read(state, 3, arg_g)) return lua_error(state);
    int arg_b; if(!read(state, 4, arg_b)) return lua_error(state);
    get_context(state).colortable(arg_index, arg_r, arg_g, arg_b);
    return 0;
}

int lua_function_cls(lua_State* state)
{
    if(!check_stack_size(state, 0)) return lua_error(state);
    get_context(state).cls();
    return 0;
}

int lua_function_camera(lua_State* state)
{
    if(!check_stack_size(state, 2)) return lua_error(state);
    int arg_x; if(!read(state, 1, arg_x)) return lua_error(state);
    int arg_y; if(!read(state, 2, arg_y)) return lua_error(state);
    get_context(state).camera(arg_x, arg_y);
    return 0;
}

int lua_function_rect(lua_State* state)
{
    if(!check_stack_size(state, 4)) return lua_error(state);
    int arg_x; if(!read(state, 1, arg_x)) return lua_error(state);
    int arg_y; if(!read(state, 2, arg_y)) return lua_error(state);
    int arg_w; if(!read(state, 3, arg_w)) return lua_error(state);
    int arg_h; if(!read(state, 4, arg_h)) return lua_error(state);
    get_context(state).rect(arg_x, arg_y, arg_w, arg_h);
    return 0;
}

int lua_function_rectfill(lua_State* state)
{
    if(!check_stack_size(state, 4)) return lua_error(state);
    int arg_x; if(!read(state, 1, arg_x)) return lua_error(state);
    int arg_y; if(!read(state, 2, arg_y)) return lua_error(state);
    int arg_w; if(!read(state, 3, arg_w)) return lua_error(state);
    int arg_h; if(!read(state, 4, arg_h)) return lua_error(state);
    get_context(state).rectfill(arg_x, arg_y, arg_w, arg_h);
    return 0;
}

int lua_function_memsize(lua_State* state)
{
    if(!check_stack_size(state, 1)) return lua_error(state);
    int arg_size; if(!read(state, 1, arg_size)) return lua_error(state);
    get_context(state).memsize(arg_size);
    return 0;
}

int lua_function_memload(lua_State* state)
{
    if(!check_stack_size(state, 3)) return lua_error(state);
    int arg_offset; if(!read(state, 1, arg_offset)) return lua_error(state);
    const void* arg_src; if(!read(state, 2, arg_src)) return lua_error(state);
    int arg_size; if(!read(state, 3, arg_size)) return lua_error(state);
    get_context(state).memload(arg_offset, arg_src, arg_size);
    return 0;
}

int lua_function_bmpload(lua_State* state)
{
    if(!check_stack_size(state, 7)) return lua_error(state);
    int arg_offset; if(!read(state, 1, arg_offset)) return lua_error(state);
    int arg_stride; if(!read(state, 2, arg_stride)) return lua_error(state);
    int arg_bits; if(!read(state, 3, arg_bits)) return lua_error(state);
    int arg_shift; if(!read(state, 4, arg_shift)) return lua_error(state);
    const void* arg_src; if(!read(state, 5, arg_src)) return lua_error(state);
    int arg_sizex; if(!read(state, 6, arg_sizex)) return lua_error(state);
    int arg_sizey; if(!read(state, 7, arg_sizey)) return lua_error(state);
    get_context(state).bmpload(arg_offset, arg_stride, arg_bits, arg_shift, arg_src, arg_sizex, arg_sizey);
    return 0;
}

int lua_function_sprsheet(lua_State* state)
{
    if(!check_stack_size(state, 7)) return lua_error(state);
    int arg_offset; if(!read(state, 1, arg_offset)) return lua_error(state);
    int arg_bits; if(!read(state, 2, arg_bits)) return lua_error(state);
    int arg_shift; if(!read(state, 3, arg_shift)) return lua_error(state);
    int arg_sizex; if(!read(state, 4, arg_sizex)) return lua_error(state);
    int arg_sizey; if(!read(state, 5, arg_sizey)) return lua_error(state);
    int arg_countx; if(!read(state, 6, arg_countx)) return lua_error(state);
    int arg_county; if(!read(state, 7, arg_county)) return lua_error(state);
    get_context(state).sprsheet(arg_offset, arg_bits, arg_shift, arg_sizex, arg_sizey, arg_countx, arg_county);
    return 0;
}

int lua_function_spr(lua_State* state)
{
    if(!check_stack_range(state, 5, 7)) return lua_error(state);
    int arg_n; if(!read(state, 1, arg_n)) return lua_error(state);
    int arg_x; if(!read(state, 2, arg_x)) return lua_error(state);
    int arg_y; if(!read(state, 3, arg_y)) return lua_error(state);
    int arg_w; if(!read(state, 4, arg_w)) return lua_error(state);
    int arg_h; if(!read(state, 5, arg_h)) return lua_error(state);
    bool arg_flip_x = false; if(!read_opt(state, 6, arg_flip_x)) return lua_error(state);
    bool arg_flip_y = false; if(!read_opt(state, 7, arg_flip_y)) return lua_error(state);
    get_context(state).spr(arg_n, arg_x, arg_y, arg_w, arg_h, arg_flip_x, arg_flip_y);
    return 0;
}

const struct luaL_Reg lua_functions[] = {
    {"flip", lua_function_flip},
    {"clip", lua_function_clip},
    {"color", lua_function_color},
    {"colorcount", lua_function_colorcount},
    {"colortable", lua_function_colortable},
    {"cls", lua_function_cls},
    {"camera", lua_function_camera},
    {"rect", lua_function_rect},
    {"rectfill", lua_function_rectfill},
    {"memsize", lua_function_memsize},
    {"memload", lua_function_memload},
    {"bmpload", lua_function_bmpload},
    {"sprsheet", lua_function_sprsheet},
    {"spr", lua_function_spr},
    {NULL, NULL},
};

