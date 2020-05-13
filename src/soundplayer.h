#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "iostream"
#include "stdio.h"
#include <memory>
#include <string>

const std::string path_BackgroundSong{"../media/snake_jazz.wav"};
const std::string path_GameOverSong{"../media/game_over.wav"};

class SoundPlayer{
 public:
  SoundPlayer();
  ~SoundPlayer();
  bool PlayBackgroundMusic();
  bool HaltBackgroundMusic();

 private:
  class Song{
    public:
      Song(std::string path);
      ~Song();

      bool PlaySong();
      bool HaltSong();
      bool PauseSong();
      bool ResumeSong();
    
    private:
      struct DestroyerMixMusic{
        void operator()(Mix_Music* m) const{
          Mix_FreeMusic(m);
        }
      };

    private:
      std::unique_ptr<Mix_Music, DestroyerMixMusic> _mix_music;
  };
  Song _backgroundSong;
  static bool _isAudioInit;
};

