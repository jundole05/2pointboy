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
    std::cout << "\n=== Attempting to play background music ===" << std::endl;
    std::wcout << L"File: " << filename << std::endl;
 
    stopMusic(); // 기존 음악 정지
  
    std::wstring mediaType = getMediaType(filename);
    std::wcout << L"Media type: " << mediaType << std::endl;
    
    std::wstring command = L"open \"" + filename + L"\" type " + mediaType + L" alias bgmusic";
    std::wcout << L"MCI Command: " << command << std::endl;
 
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
    
    std::cout << "File opened successfully!" << std::endl;
    
    // 볼륨 설정 (최대)
    mciSendString(L"setaudio bgmusic volume to 1000", NULL, 0, NULL);
    
    // 반복 재생
    std::cout << "Attempting to play..." << std::endl;
    error = mciSendString(L"play bgmusic repeat", NULL, 0, NULL);
    
    if (error != 0)
    {
        wchar_t errorMsg[256];
        mciGetErrorString(error, errorMsg, 256);
    std::wcerr << L"ERROR playing background music: " << errorMsg << std::endl;
        std::wcerr << L"Error code: " << error << std::endl;
        
     // 반복 없이 재생 시도
        std::cout << "Trying to play without repeat..." << std::endl;
   error = mciSendString(L"play bgmusic", NULL, 0, NULL);
    
        if (error != 0)
        {
       mciGetErrorString(error, errorMsg, 256);
     std::wcerr << L"ERROR playing (no repeat): " << errorMsg << std::endl;
        }
      else
        {
        currentMusic = L"bgmusic";
   std::cout << "SUCCESS: Background music playing (no repeat)!" << std::endl;
        }
    }
    else
    {
        currentMusic = L"bgmusic";
     std::cout << "SUCCESS: Background music is now playing (repeat)!" << std::endl;
    }
}

void AudioManager::playGameOverMusic(const std::wstring& filename)
{
    std::cout << "\n=== Attempting to play game over music ===" << std::endl;
    std::wcout << L"File: " << filename << std::endl;
    
    stopMusic(); // 기존 음악 정지
    
    std::wstring mediaType = getMediaType(filename);
    std::wcout << L"Media type: " << mediaType << std::endl;
    
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
    
    std::cout << "File opened successfully!" << std::endl;
    
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
        std::cout << "SUCCESS: Game over music is now playing!" << std::endl;
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
std::wcout << L"Stopping MCI music: " << currentMusic << std::endl;
        
        std::wstring command = L"stop " + currentMusic;
 mciSendString(command.c_str(), NULL, 0, NULL);
      
command = L"close " + currentMusic;
        mciSendString(command.c_str(), NULL, 0, NULL);
        
    currentMusic = L"";
    }
    
    // PlaySound 음악도 정지
    std::cout << "Stopping PlaySound music" << std::endl;
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
    std::cout << "\n=== Using PlaySound API (Loop) ===" << std::endl;
    std::wcout << L"File: " << filename << std::endl;
  
    // 기존 재생 중지
 PlaySound(NULL, NULL, 0);
    
    // 파일 존재 확인
    FILE* testFile = nullptr;
    _wfopen_s(&testFile, filename.c_str(), L"rb");
  if (!testFile)
    {
        std::cout << "ERROR: File not found!" << std::endl;
        return;
 }
    fclose(testFile);
    
    // 비동기 반복 재생
    BOOL result = PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
    if (result)
    {
        std::cout << "SUCCESS: Music playing with PlaySound API (looping)!" << std::endl;
    }
  else
    {
    std::cout << "ERROR: PlaySound failed! Error code: " << GetLastError() << std::endl;
    }
}

// PlaySound API를 사용한 게임 오버 음악 (한 번만 재생)
void AudioManager::playGameOverMusicSimple(const std::wstring& filename)
{
    std::cout << "\n=== Using PlaySound API for Game Over ===" << std::endl;
    std::wcout << L"File: " << filename << std::endl;
  
    // 기존 재생 완전히 중지
    PlaySound(NULL, NULL, 0);
    
    // 약간의 딜레이 (이전 사운드가 완전히 정지되도록)
    Sleep(50);
    
 // 파일 존재 확인
    FILE* testFile = nullptr;
    _wfopen_s(&testFile, filename.c_str(), L"rb");
    if (!testFile)
    {
        std::cout << "ERROR: File not found!" << std::endl;
        return;
    }
    fclose(testFile);

    // 비동기 재생 (반복 없음)
    BOOL result = PlaySound(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    
    if (result)
    {
        std::cout << "SUCCESS: Game Over music playing!" << std::endl;
    }
    else
    {
        std::cout << "ERROR: PlaySound failed! Error code: " << GetLastError() << std::endl;
    }
}
