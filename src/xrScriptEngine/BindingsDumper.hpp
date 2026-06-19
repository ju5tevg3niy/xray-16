#pragma once

#include <stack>

#include "xrScriptEngine.hpp"

class BindingsDumper
{
public:
    struct Options
    {
        int ShiftWidth;
        bool IgnoreDerived;
        bool StripThis;
    };

private:
    IWriter* writer;
    lua_State* ls;
    Options options;
    int shiftLevel;
    std::stack<luabind::iterator> functions;
    std::stack<luabind::iterator> classes;
    std::stack<luabind::iterator> namespaces;
    std::map<luabind::string, const char*> operatorSubst;

private:
    struct SignatureFormatterParams
    {
        luabind::detail::function_object* Function;
        const void* Context;
    };

    using SignatureFormatter = void (BindingsDumper::*)(const SignatureFormatterParams& params);

    int GetIdentSize() const;
    void Print(const char* s);
    void Print(const char* s, int len);
    void Printf(const char* format, ...);
    void PrintIndented(const char* s);
    void PrintfIndented(const char* format, ...);
    void PrintFunction(SignatureFormatter formatter, const void* fcontext = nullptr);
    void FormatStaticFunction(const SignatureFormatterParams& params);
    void PrintStaticFunction();
    void FormatMemberFunction(const SignatureFormatterParams& params);
    void PrintMemberFunction(const char* className);
    void PrintFunction();
    void PrintIntConstant(const char* name, int value);
    void PrintClass();
    void PrintNamespace(luabind::object& namesp);

public:
    BindingsDumper();
    void Dump(lua_State* luaState, IWriter* outStream, const Options& opt);
};
