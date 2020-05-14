#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "iostream"
#include "stdio.h"
#include <memory>
#include <string>

const std::string path_BackgroundSong{"../media/snake_jazz_compressed.wav"};
const std::string path_GameOverSong{"../media/game_over_8bit_compressed.wav"};
const std::string path_eatingChunk{"../media/success.wav"};
const std::string path_collisionChunk{"../media/wrong_buzzer.wav"};

class SoundPlayer {
public:
  SoundPlayer();
  ~SoundPlayer();
  void PlayBackgroundMusic();
  void HaltBackgroundMusic();
  void PlayGameOverMusic();
  void HaltGameOverMusic();
  void PlayEatingChunk();
  void PlayCollisionChunk();

private:
  class Song {
  public:
    Song(std::string path);
    ~Song();

    void PlaySong();
    void HaltSong();
    void PauseSong();
    void ResumeSong();

  private:
    struct DestroyerMixMusic {
      void operator()(Mix_Music *m) const { Mix_FreeMusic(m); }
    };
    std::unique_ptr<Mix_Music, DestroyerMixMusic> _mix_music;
  };
  class Chunk {
  public:
    Chunk(std::string path);

    void PlayChunk();

  private:
    struct DestroyerMixChunk {
      void operator()(Mix_Chunk *c) const { Mix_FreeChunk(c); }
    };
    std::unique_ptr<Mix_Chunk, DestroyerMixChunk> _mix_chunk;
  };

  static bool _isAudioInit;
  Song _backgroundSong;
  Song _gameOverSong;
  Chunk _eatingChunk;
  Chunk _collisionChunk;
};

#endif