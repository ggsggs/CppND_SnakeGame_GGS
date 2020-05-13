#include "soundplayer.h"


bool SoundPlayer::_isAudioInit =
 Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0;

SoundPlayer::SoundPlayer() : 
  _backgroundSong(path_BackgroundSong), _eatingChunk(path_eatingChunk) {
  if (!_isAudioInit) {
    printf("Error initializing SDL2_mixer: %s\n", Mix_GetError());
  }
}

SoundPlayer::~SoundPlayer() {
  Mix_Quit();
}

bool SoundPlayer::PlayBackgroundMusic() {
  _backgroundSong.PlaySong();    
}

bool SoundPlayer::HaltBackgroundMusic() {
  _backgroundSong.HaltSong();
}

void SoundPlayer::PlayEatingChunk() {
  _eatingChunk.PlayChunk();
}
SoundPlayer::Song::Song(std::string path) {
  _mix_music.reset(Mix_LoadMUS(path.c_str()));
  if (_mix_music == nullptr) {
    printf("Error reading audio file at %s. Error: %s\n",
     path.c_str(), Mix_GetError());
  }
}

SoundPlayer::Song::~Song() {
  HaltSong();
}

bool SoundPlayer::Song::PlaySong() {
  if (Mix_PlayingMusic() == 0) {
    Mix_PlayMusic(_mix_music.get(), -1); // infinite loop
  }
  else{
    ResumeSong();
  }
}

bool SoundPlayer::Song::HaltSong() {
  Mix_HaltMusic();  
}

bool SoundPlayer::Song::PauseSong() {
  Mix_PauseMusic();
}

bool SoundPlayer::Song::ResumeSong() {
   if (Mix_PausedMusic() == 1) {
     Mix_ResumeMusic();
   } 
}


SoundPlayer::Chunk::Chunk(std::string path) {
  _mix_chunk.reset(Mix_LoadWAV(path.c_str()));
  if (_mix_chunk == nullptr) {
    printf("Error reading audio file at %s. Error: %s\n",
     path.c_str(), Mix_GetError());
  }
}

void SoundPlayer::Chunk::PlayChunk() {
  Mix_PlayChannel(-1, _mix_chunk.get(), 0);
}
