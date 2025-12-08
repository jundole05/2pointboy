#include "AudioManager.h"
#include <iostream>
#include <cstdio>

bool AudioManager::isInitialized = false;
std::wstring AudioManager::currentMusic = L"";

void AudioManager::init()
{
    if (!isInitialized)
    {
        isInitialized = true;
        std::cout << "AudioManager initialized" << std::endl;
    }
}

// 파일 확장자로 MCI 타입 결정
static std::wstring getMediaType(const std::wstring& filename)
{
    size_t dotPos = filename.find_last_of(L'.');
    if (dotPos != std::wstring::npos)
    {
        std::wstring ext = filename.substr(dotPos + 1);
     // 소문자로 변환
        for (auto& c : ext)
      {
 c = towlower(c);
        }
     
        if (ext == L"wav")
            return L"waveaudio";
        else if (ext == L"mp3" || ext == L"mp4" || ext == L"avi")
     return L"mpegvideo";
        else if (ext == L"mid" || ext == L"midi")
          return L"sequencer";
    }
    return L"mpegvideo"; // 기본값
}

void AudioManager::playBackgroundMusic(const std::wstring& filename)
{
    stopMusic(); // 기존 음악 정지
  
    std::wstring mediaType = getMediaType(filename);
    
    std::wstring command = L"open \"" + filename + L"\" type " + mediaType + L" alias bgmusic";
 
  MCIERROR error = mciSendString(command.c_str(), NULL, 0, NULL);
    
    if (error != 0)
    {
        wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
        std::wcerr << L"ERROR opening background music: " << errorMsg << std::endl;
        std::wcerr << L"Error code: " << error << std::endl;
        
        // 파일 존재 여부 확인
        FILE* testFile = nullptr;
        _wfopen_s(&testFile, filename.c_str(), L"rb");
        if (testFile)
    {
   std::cout << "File exists and is readable" << std::endl;
 fclose(testFile);
        }
        else
  {
            std::cout << "ERROR: File does not exist or is not readable!" << std::endl;
            std::wcout << L"Looking for: " << filename << std::endl;
        }
        return;
    }
    
    // 볼륨 설정 (최대)
    mciSendString(L"setaudio bgmusic volume to 1000", NULL, 0, NULL);
    
    // 반복 재생
    error = mciSendString(L"play bgmusic repeat", NULL, 0, NULL);
    
    if (error != 0)
    {
        wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
    std::wcerr << L"ERROR playing background music: " << errorMsg << std::endl;
        std::wcerr << L"Error code: " << error << std::endl;
        
     // 반복 없이 재생 시도
        error = mciSendString(L"play bgmusic", NULL, 0, NULL);
    
        if (error != 0)
        {
       mciGetErrorString(error, errorMsg, 256);
     std::wcerr << L"ERROR playing (no repeat): " << errorMsg << std::endl;
        }
      else
        {
        currentMusic = L"bgmusic";
        }
    }
    else
    {
        currentMusic = L"bgmusic";
    }
}

void AudioManager::playGameOverMusic(const std::wstring& filename)
{
    stopMusic(); // 기존 음악 정지
    
    std::wstring mediaType = getMediaType(filename);
    
    std::wstring command = L"open \"" + filename + L"\" type " + mediaType + L" alias gameovermusic";
    MCIERROR error = mciSendString(command.c_str(), NULL, 0, NULL);
    
    if (error != 0)
    {
      wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
        std::wcerr << L"ERROR opening game over music: " << errorMsg << std::endl;
 std::wcerr << L"Error code: " << error << std::endl;
     
      // 파일 존재 여부 확인
        FILE* testFile = nullptr;
        _wfopen_s(&testFile, filename.c_str(), L"rb");
        if (testFile)
        {
        std::cout << "File exists and is readable" << std::endl;
         fclose(testFile);
  }
        else
        {
     std::cout << "ERROR: File does not exist or is not readable!" << std::endl;
        }
        return;
    }
    
    // 볼륨 설정
    mciSendString(L"setaudio gameovermusic volume to 1000", NULL, 0, NULL);
    
  // 한 번만 재생
    error = mciSendString(L"play gameovermusic", NULL, 0, NULL);
    if (error != 0)
    {
        wchar_t errorMsg[256];
   mciGetErrorString(error, errorMsg, 256);
        std::wcerr << L"ERROR playing game over music: " << errorMsg << std::endl;
    }
    else
    {
    currentMusic = L"gameovermusic";
    }
}

void AudioManager::playSoundEffect(const std::wstring& filename)
{
    std::wstring mediaType = getMediaType(filename);
    std::wstring command = L"open \"" + filename + L"\" type " + mediaType + L" alias sfx";
    MCIERROR error = mciSendString(command.c_str(), NULL, 0, NULL);
    
    if (error != 0)
    {
        wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
        std::wcerr << L"ERROR opening sound effect: " << errorMsg << std::endl;
        return;
    }
 
    // 볼륨 설정
    mciSendString(L"setaudio sfx volume to 1000", NULL, 0, NULL);
    
    error = mciSendString(L"play sfx", NULL, 0, NULL);
 if (error != 0)
    {
        wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
        std::wcerr << L"ERROR playing sound effect: " << errorMsg << std::endl;
    }
  
    // 효과음은 재생 후 자동으로 닫힘
    mciSendString(L"close sfx", NULL, 0, NULL);
}

void AudioManager::stopMusic()
{
    // MCI 음악 정지
    if (!currentMusic.empty())
  {
        
        std::wstring command = L"stop " + currentMusic;
 mciSendString(command.c_str(), NULL, 0, NULL);
      
command = L"close " + currentMusic;
        mciSendString(command.c_str(), NULL, 0, NULL);
        
    currentMusic = L"";
    }
    
    // PlaySound 음악도 정지
    PlaySound(NULL, NULL, 0);
}

void AudioManager::cleanup()
{
    stopMusic();
    isInitialized = false;
    std::cout << "AudioManager cleaned up" << std::endl;
}

// PlaySound API를 사용한 간단한 재생 방법 (반복)
void AudioManager::playBackgroundMusicSimple(const std::wstring& filename)
{
    // 기존 배경음악 정지 (PlaySound 방식만)
    PlaySound(NULL, NULL, 0);
  
    // MCI로 기존 배경음악 정지
    if (!currentMusic.empty())
    {
        std::wstring stopCmd = L"stop " + currentMusic;
      mciSendString(stopCmd.c_str(), NULL, 0, NULL);
        std::wstring closeCmd = L"close " + currentMusic;
     mciSendString(closeCmd.c_str(), NULL, 0, NULL);
        currentMusic = L"";
  }
    
    // 파일 존재 확인
    FILE* testFile = nullptr;
 _wfopen_s(&testFile, filename.c_str(), L"rb");
 if (!testFile)
{
        return;
    }
    fclose(testFile);
    
    // PlaySound로 간단하게 반복 재생 (가장 확실한 방법)
    BOOL result = PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
  
    if (result)
    {
        currentMusic = L"playsound_bg";  // PlaySound 사용 중임을 표시
    }
}

// PlaySound API를 사용한 게임 오버 음악 (한 번만 재생)
void AudioManager::playGameOverMusicSimple(const std::wstring& filename)
{
    // 기존 배경음악 정지
    PlaySound(NULL, NULL, 0);
 
    if (!currentMusic.empty())
    {
        std::wstring stopCmd = L"stop " + currentMusic;
        mciSendString(stopCmd.c_str(), NULL, 0, NULL);
        std::wstring closeCmd = L"close " + currentMusic;
        mciSendString(closeCmd.c_str(), NULL, 0, NULL);
        currentMusic = L"";
    }
    
    Sleep(50);
    
    // 파일 존재 확인
    FILE* testFile = nullptr;
    _wfopen_s(&testFile, filename.c_str(), L"rb");
  if (!testFile)
    {
        return;
    }
  fclose(testFile);

    // PlaySound로 한 번만 재생
    BOOL result = PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    
    if (result)
    {
      currentMusic = L"playsound_go";
    }
}

// 효과음 재생 (배경음악과 별개로 재생 - MCI 사용)
void AudioManager::playSoundEffectSimple(const std::wstring& filename)
{
  // 현재 작업 디렉토리 확인
    wchar_t currentDir[MAX_PATH];
  GetCurrentDirectoryW(MAX_PATH, currentDir);
  
    // 파일 존재 확인 및 절대 경로 생성
    std::wstring fullPath = filename;
    FILE* testFile = nullptr;
    _wfopen_s(&testFile, filename.c_str(), L"rb");
    
    if (!testFile)
    {
    // 상대 경로로 실패하면 절대 경로 시도
      fullPath = std::wstring(currentDir) + L"\\" + filename;
        _wfopen_s(&testFile, fullPath.c_str(), L"rb");
        
        if (!testFile)
        {
            return;
        }
  }
    fclose(testFile);
    
    // MCI를 사용하여 효과음 재생 (배경음악과 완전히 분리)
    // 고유한 alias 생성 (타임스탬프 + 카운터)
    static int soundCounter = 0;
    soundCounter++;
    std::wstring alias = L"sfx_" + std::to_wstring(GetTickCount()) + L"_" + std::to_wstring(soundCounter);
    
    // 1. 효과음 파일 열기
    std::wstring openCmd = L"open \"" + fullPath + L"\" type waveaudio alias " + alias;
    MCIERROR error = mciSendString(openCmd.c_str(), NULL, 0, NULL);
    
    if (error != 0)
    {
        return;
    }
 
    // 2. 볼륨 설정
    std::wstring volumeCmd = L"setaudio " + alias + L" volume to 1000";
    mciSendString(volumeCmd.c_str(), NULL, 0, NULL);
    
    // 3. 효과음 재생
    std::wstring playCmd = L"play " + alias;
    error = mciSendString(playCmd.c_str(), NULL, 0, NULL);
    
    if (error != 0)
    {
        // 실패 시 닫기
std::wstring closeCmd = L"close " + alias;
        mciSendString(closeCmd.c_str(), NULL, 0, NULL);
        return;
    }
}
