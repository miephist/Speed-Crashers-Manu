#pragma once
#include "structs.h"

struct Vector3 {

    float x;
    float y;
    float z;

};

struct Implementation{

    Implementation();
    ~Implementation();

    void Update();

    FMOD_STUDIO_SYSTEM* mpStudioSystem;
    FMOD_SYSTEM* mpSystem;

    int mnNextChannelId;

    typedef std::map<std::string, FMOD_SOUND*> SoundMap;
    typedef std::map<int, FMOD_CHANNEL*> ChannelMap;
    typedef std::map<std::string, FMOD_STUDIO_EVENTINSTANCE*> EventMap;
    typedef std::map<std::string, FMOD_STUDIO_BANK*> BankMap;

    BankMap mBanks;
    EventMap mEvents;
    SoundMap mSounds;
    ChannelMap mChannels;

};


class CAudioEngine {
public:

    CAudioEngine();
    ~CAudioEngine();

    static void Update();

    void LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
    void LoadEvent(const std::string& strEventName);
    void Loadsound(const std::string &strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
    void UnLoadSound(const std::string &strSoundName);
    int PlaySounds(const std::string &strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
    void PlayEvent(const std::string &strEventName);

    void StopEvent(const std::string &strEventName, bool bImmediate = false);
    void GeteventParameter(const std::string &strEventName, const std::string &strEventParameter, float* parameter);
    void SetEventParameter(const std::string &strEventName, const std::string &strParameterName, float fValue);
    void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
    void SetChannelvolume(int nChannelId, float fVolumedB);
    void SetEventVolume(const std::string& strEventName, float fVolumedB);
    bool IsPlaying(int nChannelId) const;
    bool IsEventPlaying(const std::string &strEventName) const;
    void Mute();
    void Unmute();
    float dbToVolume(float db);
    float VolumeTodB(float volume);
    FMOD_VECTOR VectorToFmod(const Vector3& vPosition);

    static CAudioEngine* getInstancia();

    void LoadAll();

    void Randompnj();
    bool Silence();

private:

    //Instancia
    static CAudioEngine* instancia;

};