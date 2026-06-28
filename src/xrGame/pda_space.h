#include "xrCore/log.h"
#include "Common/types.hpp"
#pragma once

//типы сообщений PDA
enum EPdaMsg : u32
{
    ePdaMsgDialog, //диалог
    ePdaMsgInfo, //сообщение передает некоторую информацию
    ePdaMsgMax
};
