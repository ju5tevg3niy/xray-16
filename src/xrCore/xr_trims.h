#pragma once
#include "xrCore/xrstring.h"

// refs
struct xr_token;

int _GetItemCount(pcstr, char separator = ',');
pstr _GetItem(pcstr, int, pstr, u32 const dst_size, char separator = ',', pcstr = "", bool trim = true);

template <int count>
inline pstr _GetItem(
    pcstr src, int index, char (&dst)[count], char separator = ',', pcstr def = "", bool trim = true)
{
    return _GetItem(src, index, dst, count, separator, def, trim);
}

pstr _GetItems(pcstr, int, int, pstr, char separator = ',');
pcstr _GetItems(pcstr, int, int, std::string&, char);
pcstr _SetPos(pcstr src, u32 pos, char separator = ',');
pcstr _CopyVal(pcstr src, pstr dst, char separator = ',');
pstr _Trim(pstr str, char whatToTrim = ' ');
pstr _TrimLeft(pstr str, char whatToTrim = ' ');
pstr _TrimRight(pstr str, char whatToTrim = ' ');
pstr _ChangeSymbol(pstr name, char src, char dest);
u32 _ParseItem(pcstr src, xr_token* token_list);
u32 _ParseItem(pstr src, int ind, xr_token* token_list);
pstr _ReplaceItem(pcstr src, int index, pcstr new_item, pstr dst, char separator);
std::string& _ReplaceItem(pcstr src, int index, pcstr new_item, std::string& dst, char separator);
pstr _ReplaceItems(pcstr src, int idx_start, int idx_end, pcstr new_items, pstr dst, char separator);
std::string& _ReplaceItems(pcstr src, int idx_start, int idx_end, pcstr new_items, std::string& dst, char separator);
void _SequenceToList(std::vector<pstr>& lst, pcstr in, char separator = ',');
void _SequenceToList(std::vector<shared_str>& lst, pcstr in, char separator = ',');
void _SequenceToList(std::vector<std::string>& lst, pcstr in, char separator = ',');

std::string& _Trim(std::string& src);
std::string& _TrimLeft(std::string& src);
std::string& _TrimRight(std::string& src);
std::string& _ChangeSymbol(std::string& name, char src, char dest);
pcstr _CopyVal(pcstr src, std::string& dst, char separator = ',');
pcstr _GetItem(pcstr src, int, std::string& p, char separator = ',', pcstr = "", bool trim = true);
std::string _ListToSequence(const std::vector<std::string>& lst);
shared_str _ListToSequence(const std::vector<shared_str>& lst);

