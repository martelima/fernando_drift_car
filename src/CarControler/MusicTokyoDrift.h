// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

const int MusicMelody[] = {
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_F5, REST,
  NOTE_F5, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  REST
};

const int MusicDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  1
};

const int MusicSize = sizeof(MusicDurations) / sizeof(int) -1;
