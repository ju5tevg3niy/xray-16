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
pcstr _GetItems(pcstr, int, int, xr_string&, char);
pcstr _SetPos(pcstr src, u32 pos, char separator = ',');
pcstr _CopyVal(pcstr src, pstr dst, char separator = ',');
pstr _Trim(pstr str, char whatToTrim = ' ');
pstr _TrimLeft(pstr str, char whatToTrim = ' ');
pstr _TrimRight(pstr str, char whatToTrim = ' ');
pstr _ChangeSymbol(pstr name, char src, char dest);
u32 _ParseItem(pcstr src, xr_token* token_list);
u32 _ParseItem(pstr src, int ind, xr_token* token_list);
pstr _ReplaceItem(pcstr src, int index, pcstr new_item, pstr dst, char separator);
xr_string& _ReplaceItem(pcstr src, int index, pcstr new_item, xr_string& dst, char separator);
pstr _ReplaceItems(pcstr src, int idx_start, int idx_end, pcstr new_items, pstr dst, char separator);
xr_string& _ReplaceItems(pcstr src, int idx_start, int idx_end, pcstr new_items, xr_string& dst, char separator);
void _SequenceToList(xr_vector<pstr>& lst, pcstr in, char separator = ',');
void _SequenceToList(xr_vector<shared_str>& lst, pcstr in, char separator = ',');
void _SequenceToList(xr_vector<xr_string>& lst, pcstr in, char separator = ',');

xr_string& _Trim(xr_string& src);
xr_string& _TrimLeft(xr_string& src);
xr_string& _TrimRight(xr_string& src);
xr_string& _ChangeSymbol(xr_string& name, char src, char dest);
pcstr _CopyVal(pcstr src, xr_string& dst, char separator = ',');
pcstr _GetItem(pcstr src, int, xr_string& p, char separator = ',', pcstr = "", bool trim = true);
xr_string _ListToSequence(const xr_vector<xr_string>& lst);
shared_str _ListToSequence(const xr_vector<shared_str>& lst);

