// MusicStream.h: interface for the CMusicStream class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

// refs
class CSoundStream;
class CInifile;

class CMusicStream
{
    xr_vector<CSoundStream*> streams;
    int FindEmptySlot();

public:
    CMusicStream();
    ~CMusicStream();

    CSoundStream* CreateSound(LPCSTR name);
    void DeleteSound(CSoundStream* pSnd);

    void OnMove();
    void Reload();
    void Update();
};
