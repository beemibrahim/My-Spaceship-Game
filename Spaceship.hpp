#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <vector>
#define ELAPSED chrono::duration_cast<chrono::milliseconds>
#define NOW std::chrono::high_resolution_clock::now()
#define SHOOTME                                                                \
  (status->bullpos[i].x == status->x && status->bullpos[i].y == status->y) ||  \
      (status->bullpos[i].x == status->x + 1 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 2 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 3 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 4 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 5 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 6 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 7 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 8 &&                                \
       status->bullpos[i].y == status->y) ||                                   \
      (status->bullpos[i].x == status->x + 1 &&                                \
       status->bullpos[i].y == status->y - 1) ||                               \
      (status->bullpos[i].x == status->x + 2 &&                                \
       status->bullpos[i].y == status->y - 1) ||                               \
      (status->bullpos[i].x == status->x + 3 &&                                \
       status->bullpos[i].y == status->y - 1) ||                               \
      (status->bullpos[i].x == status->x + 4 &&                                \
       status->bullpos[i].y == status->y - 1) ||                               \
      (status->bullpos[i].x == status->x + 1 &&                                \
       status->bullpos[i].y == status->y + 1) ||                               \
      (status->bullpos[i].x == status->x + 2 &&                                \
       status->bullpos[i].y == status->y + 1) ||                               \
      (status->bullpos[i].x == status->x + 3 &&                                \
       status->bullpos[i].y == status->y + 1) ||                               \
      (status->bullpos[i].x == status->x + 4 &&                                \
       status->bullpos[i].y == status->y + 1)

using namespace std;

class Bullet {
public:
  int x = 0;
  int y = 0;
};
class sizef {
public:
  int x = 0;
  int y = 0;
  int size = 0;
};

class Spaceship_Status {
public:
  int bullets;
  int kills;
  int x;
  bool hitself = false;
  bool bulletno;
  vector<Bullet> bullpos;
  int y;
};
class SpaceShip_Functions {
public:
  void printf_Spaceship(int x, int y);
  void remove_Spaceship(int x, int y);
  void left(int &x, int &y);
  void right(int &x, int &y);
  void up(int &x, int &y);
  void down(int &x, int &y);
  static void *Shoot(void *statuss);
  void print_pstatus(int bullets, int kills);
  static void alterbullet_pstatus(int bullets);
  void alterkill_pstatus(int kills);
};

class Level_Status {
public:
  static void *stars(void *statuss);
  bool controls;
  int level_im_on;
  int Enemy_Wave;
  bool bossfight;
};

class Star {
public:
  int x;
  int y;
  int speed;
};
