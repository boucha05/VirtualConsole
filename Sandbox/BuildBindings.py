import re
import sys

def importBindings(filename):
    bindings = []
    re_sections = re.compile("[\(\)]")
    with open(filename) as file:
        for line in file:
            sections = re_sections.split(line.rstrip())
            if len(sections) == 3:
                ret_type, name = [val.strip() for val in sections[0].rsplit(' ', 1)]
                if ret_type == "void":
                    ret_type = None
                args = [val.strip() for val in sections[1].split(',')] if sections[1] else []
                bindings.append((ret_type, name, args))
    return bindings

def exportLuaBindings(file, functions):
    file.write("// Warning: this file is generated automatically!!!\n\n")
    for binding in functions:
        ret, name, args = binding
        args_decl = []
        args_default = []
        first_default = None
        for index in range(len(args)):
            arg_index = index + 1
            arg_def_split = [val.strip() for val in args[index].split('=')]
            args_decl.append(arg_def_split[0])
            if len(arg_def_split) > 1:
                if not first_default: first_default = arg_index
                args_default.append(arg_def_split[1])
            else:
                args_default.append(None)

        file.write("int lua_function_%s(lua_State* state)\n{\n" % name)
        if first_default:
            file.write("    if(!check_stack_range(state, %d, %d)) return lua_error(state);\n" % (first_default - 1, len(args)))
        else:
            file.write("    if(!check_stack_size(state, %d)) return lua_error(state);\n" % len(args))
        arg_names = [];
        for index in range(len(args_decl)):
            arg_index = index + 1
            arg_type, arg_name = [val.strip() for val in args_decl[index].rsplit(' ', 1)]
            arg_name = "arg_" + arg_name
            arg_names.append(arg_name)
            file.write("    %s %s" % (arg_type, arg_name))
            if first_default and arg_index >= first_default:
                file.write(" = %s" % (args_default[index]))
                read_type = "read_opt"
            else:
                read_type = "read"
            file.write("; if(!%s(state, %d, %s)) return lua_error(state);\n" % (read_type, arg_index, arg_name))

        file.write("    ")
        if ret:
            file.write("%s result = " % ret)
        file.write("get_context(state).%s(%s);\n" %(name, ", ".join(arg_names)))
        if ret:
            file.write("    push(state, result);\n")
            file.write("    return 1;\n")
        else:
            file.write("    return 0;\n")
        file.write("}\n\n")

    file.write("const struct luaL_Reg lua_functions[] = {\n")
    for function in functions:
        ret, name, args = function
        file.write("    {\"%s\", lua_function_%s},\n" % (name, name))
    file.write("    {NULL, NULL},\n")
    file.write("};\n\n")

def buildBindings(input, output):
    bindings = importBindings(input)
    with open(output, "w") as file:
        exportLuaBindings(file, bindings)

def main():
    buildBindings("ConsoleBindings.h", "LuaConsoleBindings.h")
    buildBindings("ContentBindings.h", "LuaContentBindings.h")

if __name__ == '__main__':
    main()
