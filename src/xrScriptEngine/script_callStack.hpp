#include "Common/types.hpp"
#include "Common/types_paths.hpp"
#include <vector>
#pragma once

#include "xrScriptEngine.hpp"

class CScriptDebugger;

struct SPath
{
    string_path path;
};

class XRSCRIPTENGINE_API CScriptCallStack
{
public:
    CScriptDebugger* m_debugger;
    void GotoStackTraceLevel(int nLevel);
    void Add(const char* szDesc, const char* szFile, int nLine);
    void Clear();
    CScriptCallStack(CScriptDebugger* d);
    ~CScriptCallStack();

    int GetLevel() { return m_nCurrentLevel; }
    void SetStackTraceLevel(int);

protected:
    int m_nCurrentLevel;
    std::vector<u32> m_levels;
    std::vector<u32> m_lines;
    std::vector<SPath> m_files;
};
