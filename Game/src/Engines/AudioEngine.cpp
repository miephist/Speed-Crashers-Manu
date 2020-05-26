#include "AudioEngine.h"

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

inline void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

// Parte Implementation
Implementation* sgpImplementation = nullptr;
CAudioEngine* CAudioEngine::instancia = nullptr;

Implementation::Implementation(){
    mpStudioSystem = NULL;
    ERRCHECK(FMOD_Studio_System_Create(&mpStudioSystem, FMOD_VERSION));
    ERRCHECK(FMOD_Studio_System_Initialize(mpStudioSystem, 32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

    mpSystem = NULL;
    ERRCHECK(FMOD_Studio_System_GetLowLevelSystem(mpStudioSystem, &mpSystem));
}

Implementation::~Implementation() {
    ERRCHECK(FMOD_Studio_System_UnloadAll(mpStudioSystem));
    ERRCHECK(FMOD_Studio_System_Release(mpStudioSystem));

    sgpImplementation = nullptr;
}

void Implementation::Update(){

    std::vector<ChannelMap::iterator> pStoppedChannels;

    for(auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it){
        FMOD_BOOL bIsPlaying = false;
        FMOD_Channel_IsPlaying(it->second, &bIsPlaying);
        //it->second->isPlaying(&bIsPlaying);

        if(!bIsPlaying){
            pStoppedChannels.push_back(it);
        }
    }

    for(auto &it : pStoppedChannels){
        mChannels.erase(it);
    }
    ERRCHECK(FMOD_Studio_System_Update(mpStudioSystem));
}


// Fin parte Implementation
void CAudioEngine::LoadAll(){
    // Inicializamos motor de audio y sus bancos
    //CAudioEngine* aEngine = CAudioEngine::getInstancia();
    LoadBank("media/Bancos/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    LoadBank("media/Bancos/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    LoadBank("media/Bancos/Dialogos.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    LoadBank("media/Bancos/Musica.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    LoadBank("media/Bancos/SFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    LoadBank("media/Bancos/Ambiente.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);

    // Prueba reproduccion de evento
    LoadEvent("event:/Musica/future_music");
    SetEventVolume("event:/Musica/future_music", 0.22f);
    
    
    LoadEvent("event:/Musica/arcade_music");
    SetEventVolume("event:/Musica/arcade_music", 0.22f);

    //SFX
    LoadEvent("event:/SFX/Coche/iniciar_nitro");
    LoadEvent("event:/SFX/Coche/clicknitro");
    SetEventVolume("event:/SFX/Coche/iniciar_nitro", 0.5f);

    LoadEvent("event:/SFX/Coche/ChoqueLeve");
    SetEventVolume("event:/SFX/Coche/ChoqueLeve", 1.f);

    LoadEvent("event:/SFX/Interfaz/Boton_menu");
    SetEventVolume("event:/SFX/Interfaz/Boton_menu", 4.f);

    LoadEvent("event:/SFX/Pelota/pelota_pared");
    LoadEvent("event:/SFX/Coche/salto_coche");

    LoadEvent("event:/SFX/Coche/Recogernitro");
     SetEventVolume("event:/SFX/Coche/Recogernitro", 0.5f);

    LoadEvent("event:/SFX/Interfaz/Boton_menu");
    SetEventVolume("event:/SFX/Interfaz/Boton_menu", 0.5f);

    //Poderes
    LoadEvent("event:/SFX/Powers/Congelar");
    LoadEvent("event:/SFX/Powers/Marear");
    LoadEvent("event:/SFX/Powers/maxnitroIn");

    ////////voces
    //selec
    LoadEvent("event:/Voces/Personaje3/CaraSuena");
    LoadEvent("event:/Voces/Personaje2/ListoFiesta");
    //elegir
    LoadEvent("event:/Voces/Personaje3/MejorHago");
    SetEventVolume("event:/Voces/Personaje3/MejorHago", 3.f);
    LoadEvent("event:/Voces/Personaje2/SinPiedad");
    SetEventVolume("event:/Voces/Personaje2/SinPiedad", 2.f);
    //gol
    LoadEvent("event:/SFX/Pelota/Gol");
    SetEventVolume("event:/Voces/Personaje3/GanarDivertido", 0.6f);

    //pnj1
    LoadEvent("event:/Voces/Personaje1/Wow");
    SetEventVolume("event:/Voces/Personaje1/Wow", 4.f);

    LoadEvent("event:/Voces/Personaje1/PorEstoVengoATrabajr");
    SetEventVolume("event:/Voces/Personaje1/PorEstoVengoATrabajr", 3.f);

    LoadEvent("event:/Voces/Personaje1/MenudoGol");
    SetEventVolume("event:/Voces/Personaje1/MenudoGol", 3.f);

    //pnj4
    LoadEvent("event:/Voces/Personaje4/DurarEsto");
    SetEventVolume("event:/Voces/Personaje4/DurarEsto",3.f);
    
    LoadEvent("event:/Voces/Personaje4/FacilJuego");
    SetEventVolume("event:/Voces/Personaje4/FacilJuego",3.f);
}

bool CAudioEngine::Silence(){
    if(!IsEventPlaying("event:/SFX/Pelota/Gol")){
        if(!IsEventPlaying("event:/SFX/Coche/Recogernitro"))
            return true;
    }
    return false;
}

void CAudioEngine::Randompnj(){
    srand(time(NULL));
    int voz = rand()%3;

    switch (voz){
        case 0:
            PlayEvent("event:/Voces/Personaje3/GanarDivertido");
        break; 
        case 1:
            PlayEvent("event:/Voces/Personaje3/Patetico");
        break;
        case 2:
            PlayEvent("event:/Voces/Personaje3/MejorHago");
        break;
    }
}
CAudioEngine *CAudioEngine::getInstancia(){

    if(instancia == nullptr)
        instancia = new CAudioEngine();

    return instancia;

}

CAudioEngine::CAudioEngine(){

    sgpImplementation = new Implementation;

    // Cargamos los bancos
    LoadAll();
}

CAudioEngine::~CAudioEngine(){

    delete sgpImplementation;
    
    instancia = nullptr;

}


void CAudioEngine::Update(){

    sgpImplementation->Update();

}

void CAudioEngine::Loadsound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream){

    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);

    if(tFoundIt != sgpImplementation->mSounds.end())
        return;

    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b3d ? FMOD_3D : FMOD_2D;
    eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

    FMOD_SOUND* pSound = nullptr;
    ERRCHECK(FMOD_System_CreateSound(sgpImplementation->mpSystem, strSoundName.c_str(), eMode, nullptr, &pSound));

    if(pSound){
        sgpImplementation->mSounds[strSoundName] = pSound;
    }
}


void CAudioEngine::UnLoadSound(const std::string& strSoundName){

    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
    
    if(tFoundIt == sgpImplementation->mSounds.end())
        return;

    ERRCHECK(FMOD_Sound_Release(tFoundIt->second));
    sgpImplementation->mSounds.erase(tFoundIt);

}

int CAudioEngine::PlaySounds(const std::string& strSoundName, const Vector3& vPosition, float fVolumedB){

    int nChannelId = sgpImplementation->mnNextChannelId++;
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);

    if(tFoundIt == sgpImplementation->mSounds.end()){

        Loadsound(strSoundName);
        tFoundIt = sgpImplementation->mSounds.find(strSoundName);

        if(tFoundIt == sgpImplementation->mSounds.end()){
            return nChannelId;
        }
    }

    FMOD_CHANNEL* pChannel = nullptr;
    ERRCHECK(FMOD_System_PlaySound(sgpImplementation->mpSystem, tFoundIt->second, nullptr, true, &pChannel));

    if(pChannel){

        FMOD_MODE currMode;
        FMOD_Sound_GetMode(tFoundIt->second, &currMode);

        if(currMode & FMOD_3D){
            FMOD_VECTOR position = VectorToFmod(vPosition);
            // Ultimo parametro definido por nosotros
            ERRCHECK(FMOD_Channel_Set3DAttributes(pChannel, &position, nullptr, nullptr));
        }

        ERRCHECK(FMOD_Channel_SetVolume(pChannel,dbToVolume(fVolumedB)));
        ERRCHECK(FMOD_Channel_SetPaused(pChannel, false));
        sgpImplementation->mChannels[nChannelId] = pChannel;

    }

    return nChannelId;

}

void CAudioEngine::SetChannel3dPosition(int nChannelId, const Vector3& vPosition){

    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);

    if(tFoundIt == sgpImplementation->mChannels.end())
        return;

    FMOD_VECTOR position = VectorToFmod(vPosition);
    // Ultimo parametro definido por nosotros
    ERRCHECK(FMOD_Channel_Set3DAttributes(tFoundIt->second, &position, NULL, NULL));

}

void CAudioEngine::SetChannelvolume(int nChannelId, float fVolumedB){

    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);

    if(tFoundIt == sgpImplementation->mChannels.end())
        return;

    ERRCHECK(FMOD_Channel_SetVolume(tFoundIt->second, dbToVolume(fVolumedB)));

}

void CAudioEngine::SetEventVolume(const std::string& strEventName, float fVolumedB){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    ERRCHECK(FMOD_Studio_EventInstance_SetVolume(tFoundIt->second, fVolumedB));    

}

void CAudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){

    auto tFoundIt = sgpImplementation->mBanks.find(strBankName);

    if(tFoundIt != sgpImplementation->mBanks.end())
        return;

    FMOD_STUDIO_BANK* pBank;
    ERRCHECK(FMOD_Studio_System_LoadBankFile(sgpImplementation->mpStudioSystem, strBankName.c_str(), flags, &pBank));

    if(pBank){
        sgpImplementation->mBanks[strBankName] = pBank;
    }
}

void CAudioEngine::LoadEvent(const std::string& strEventName){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt != sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_EVENTDESCRIPTION* pEventDescription = NULL;
    
    ERRCHECK(FMOD_Studio_System_GetEvent(sgpImplementation->mpStudioSystem, strEventName.c_str(), &pEventDescription));

    if(pEventDescription){

        FMOD_STUDIO_EVENTINSTANCE* pEventInstance = NULL;
        ERRCHECK(FMOD_Studio_EventDescription_CreateInstance(pEventDescription, &pEventInstance));

        if(pEventInstance){
            sgpImplementation->mEvents[strEventName] = pEventInstance;
        }
    }
}

void CAudioEngine::PlayEvent(const std::string &strEventName){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end()){

        LoadEvent(strEventName);
        tFoundIt = sgpImplementation->mEvents.find(strEventName);

        if(tFoundIt == sgpImplementation->mEvents.end())
            return;
    }

    FMOD_Studio_EventInstance_Start(tFoundIt->second);
}

void CAudioEngine::StopEvent(const std::string &strEventName, bool bImmediate){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_STOP_MODE eMode;
    eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
    ERRCHECK(FMOD_Studio_EventInstance_Stop(tFoundIt->second, eMode));

}

bool CAudioEngine::IsEventPlaying(const std::string &strEventName) const{

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end())
        return false;

    FMOD_STUDIO_PLAYBACK_STATE state;

    ERRCHECK(FMOD_Studio_EventInstance_GetPlaybackState(tFoundIt->second, &state));
    
    if(state != FMOD_STUDIO_PLAYBACK_STOPPED){
        return true;
    }

    return false;

}

void CAudioEngine::GeteventParameter(const std::string &strEventName, const std::string &strParameterName, float* parameter){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_PARAMETERINSTANCE* pParameter = NULL;
    ERRCHECK(FMOD_Studio_EventInstance_GetParameter(tFoundIt->second, strParameterName.c_str(), &pParameter));
    ERRCHECK(FMOD_Studio_ParameterInstance_GetValue(pParameter, parameter));

}

void CAudioEngine::SetEventParameter(const std::string &strEventName, const std::string &strParameterName, float fValue){

    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);

    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_PARAMETERINSTANCE* pParameter = NULL;
    ERRCHECK(FMOD_Studio_EventInstance_GetParameter(tFoundIt->second, strParameterName.c_str(), &pParameter));
    ERRCHECK(FMOD_Studio_ParameterInstance_SetValue(pParameter, fValue));

}

void CAudioEngine::Mute(){
    for(auto i = sgpImplementation->mEvents.begin(); i != sgpImplementation->mEvents.end(); i++){
        ERRCHECK(FMOD_Studio_EventInstance_SetVolume(i->second, 0.0f));
    }
}

void CAudioEngine::Unmute(){
    for(auto i = sgpImplementation->mEvents.begin(); i != sgpImplementation->mEvents.end(); i++){
        ERRCHECK(FMOD_Studio_EventInstance_SetVolume(i->second, 1.0f));
    }
}

FMOD_VECTOR CAudioEngine::VectorToFmod(const Vector3& vPosition){
    FMOD_VECTOR fVec;
    fVec.x = vPosition.x;
    fVec.y = vPosition.y;
    fVec.z = vPosition.z;
    return fVec;
}

float CAudioEngine::dbToVolume(float dB){
    return powf(10.0f, 0.05f * dB);
}

float  CAudioEngine::VolumeTodB(float volume){
    return 20.0f * log10f(volume);
}