#include "Spaceship.hpp"

bool Onme(int x, int y, int xx, int yy) {
  if (x == xx && y == yy) {
    return true;
  }
  for (int i = 1; i < 9; i++) {
    if (x == xx + i && y == yy) {
      return true;
    }
  }
  for (int i = 1; i < 5; i++) {
    if (x == xx + i && y == yy - 1) {
      return true;
    }
  }
  for (int i = 1; i < 5; i++) {
    if (x == xx + i && y == yy + 1) {
      return true;
    }
  }
  return false;
}

void SpaceShip_Functions::printf_Spaceship(int x, int y) {
  move(y - 1, x + 1);
  addch('\\');
  addch('\\');
  addch('\\');
  addch('\\');
  move(y, x);
  addch('{');
  addch('|');
  addch('|');
  addch('|');
  addch('|');
  addch('|');
  addch(')');
  addch(']');
  addch('>');
  move(y + 1, x + 1);
  addch('/');
  addch('/');
  addch('/');
  addch('/');
  refresh();
};
void SpaceShip_Functions::up(int &x, int &y) {
  if (y == 2) {
    remove_Spaceship(x, y);
    y -= 1;
    printf_Spaceship(x, y);
    return;
  }
  if (y - 2 < 1) {
    return;
  }
  remove_Spaceship(x, y);
  y -= 2;
  printf_Spaceship(x, y);
  refresh();
}
void SpaceShip_Functions::down(int &x, int &y) {
  if (y == 32) {
    remove_Spaceship(x, y);
    y += 1;
    printf_Spaceship(x, y);
    refresh();
    return;
  }
  if (y + 2 > 33) {
    return;
  }
  remove_Spaceship(x, y);
  y += 2;
  printf_Spaceship(x, y);
  refresh();
}

void SpaceShip_Functions::left(int &x, int &y) {
  if (x == 2) {
    remove_Spaceship(x, y);
    x -= 1;
    printf_Spaceship(x, y);
    refresh();
    return;
  }
  if (x - 2 < 1) {
    return;
  }
  remove_Spaceship(x, y);
  x -= 2;
  printf_Spaceship(x, y);
  refresh();
}

void SpaceShip_Functions::right(int &x, int &y) {
  if (x == 115) {
    remove_Spaceship(x, y);
    x += 1;
    printf_Spaceship(x, y);
    return;
  }
  if (x + 2 > 116) {
    return;
  }
  remove_Spaceship(x, y);
  x += 2;
  printf_Spaceship(x, y);
  refresh();
}

void SpaceShip_Functions::print_pstatus(int bullets, int kills) {
  int x = 135;
  int y = 34;
  move(y, x);
  for (int i = 0; i < 9; x--, i++) {
    move(y, x);
    refresh();
    addch('-');
    refresh();
  }
  refresh();
  for (int i = 0; i < 3; i++, y--) {
    move(y, x);
    addch('-');
    refresh();
  }
  for (int i = 0; i < 9; x++, i++) {
    move(y, x);
    addch('-');
  }
  for (int i = 0; i < 3; i++, y++) {
    move(y, x);
    refresh();
    addch('-');
  }

  move(y - 2, x - 6);
  x -= 6;
  y -= 2;
  addch('D');
  move(y + 1, x);
  y += 1;
  addch('>');
  move(y, x + 2);
  x += 2;
  printw("%d", bullets);
  move(y - 1, x);
  y -= 1;
  printw("%d", kills);
  refresh();
}

void *SpaceShip_Functions::Shoot(void *statuss) {
  Spaceship_Status *status;
  status = (Spaceship_Status *)statuss;
  int lat = 0;
  for (;;) {
    if (lat == status->bullpos.size()) {
      break;
    }
    for (int i = lat; i < status->bullpos.size(); i++) {
      move(status->bullpos[i].y, status->bullpos[i].x);
      addch('-');
      refresh();
    }
    int size = status->bullpos.size();
    usleep(13500);
    refresh();
    for (int i = lat; i < size; i++) {
      move(status->bullpos[i].y, status->bullpos[i].x);
      addch(' ');
      refresh();
      if (status->bullpos[i].x == 116) {
        lat++;
      }
      if (SHOOTME) {
        status->hitself = true;
        pthread_exit(NULL);
      }
      status->bullpos[i].x++;
    }
  }
  vector<Bullet> empty;
  status->bullpos = empty;
  status->bulletno = false;
  pthread_exit(NULL);
}

void SpaceShip_Functions::remove_Spaceship(int x, int y) {
  // body
  move(y, x);
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  move(y - 1, x + 1);
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  move(y + 1, x + 1);
  // lower wing
  addch(' ');
  addch(' ');
  addch(' ');
  addch(' ');
  refresh();
}

void SpaceShip_Functions::alterbullet_pstatus(int bullets) {
  // x = 130
  // y = 33
  if ((bullets + 1) - 10 >= 0) {
    move(33, 131);
    delch();
    delch();
    printw("%d", bullets);
    mvdelch(33, 133);
    mvprintw(33, 135, "-");
    if (bullets < 10) {
      printw(" ");
    }
    refresh();
  }
  if ((bullets + 1) - 10 < 0) {
    mvdelch(33, 131);
    printw("%d", bullets);
    mvdelch(33, 134);
    mvprintw(33, 135, "-");
    refresh();
  }
}

void *Level_Status::stars(void *statuss) {
  int lat = 0;
  auto begin = NOW;
  bool once = false;
  bool set = false;
  Spaceship_Status *status = (Spaceship_Status *)statuss;
  map<int, vector<int>> stars;
  vector<int> speeds;
  for (;;) {
    sort(speeds.begin(), speeds.end());
    bool onetime = false;
    for (int i = 0; i < speeds.size(); i++) {
      if (onetime == false) {
        usleep(speeds[i]);
        onetime = true;
      } else {
        usleep(speeds[i] - speeds[i - 1]);
      }
      move(stars[speeds[i]][1], stars[speeds[i]][0]);
      if (inch() == '.') {
        addch(' ');
      }
      refresh();
      stars[speeds[i]][0] -= 1;
      if (stars[speeds[i]][0] == 0) {
        stars.erase(speeds[i]);
        speeds.erase(speeds.begin() + i);
        if (inch() == '.') {
          addch(' ');
        }
        refresh();
        continue;
      }
      move(stars[speeds[i]][1], stars[speeds[i]][0]);
      if (inch() == ' ') {
        addch('.');
      }
      refresh();
    }
    if (ELAPSED(NOW - begin).count() >= 300 || set == false) {
      begin = NOW;
      set = true;
      Star star;
      int y = rand() % 33;
      int x = 0;
      if (y < 30) {
        x = 135;
      } else {
        x = 124;
      }
      move(y, x);
      if (inch() == ' ') {
        addch('.');
      }
      int rando = 21000 + rand() % (31000 - 21000);
      stars[rando].push_back(x);
      stars[rando].push_back(y);
      speeds.push_back(rando);
      refresh();
      once = true;
    }
  }
  return statuss;
}
