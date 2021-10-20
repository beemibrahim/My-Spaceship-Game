#include "Spaceship.hpp"

int levelchk = 0;
void default_gamefile() {
  std::fstream gamefile;
  gamefile.open("GameData.txt");
  gamefile.seekg(0, ios::end);   // put the "cursor" at the end of the file
  int length = gamefile.tellg(); // find the position of the cursor
  if (length > 1) {
    return;
  }
  gamefile.close();
  gamefile.open("GameData.txt");
  gamefile << "false \n ";
  gamefile << "1 \n";
  gamefile.close();
}

int Game_Mech(Level_Status gameset) {
RESTART:
  pthread_t thread;
  pthread_t ster;
  Spaceship_Status *status = new Spaceship_Status;
  int sters = 0;
  sters = pthread_create(&ster, NULL, Level_Status::stars, (void *)status);
  auto then = NOW;
  SpaceShip_Functions spaceship;
  spaceship.print_pstatus(16, 0);
  spaceship.printf_Spaceship(0, 16);
  status->x = 0;
  status->y = 16;
  status->bullets = 16;
  int count = 0;
  int bullet;
  int i;
  for (;;) {
    string user_input;
    refresh();
    if (status->hitself == true) {
      clear();
      delete status;
      status = new Spaceship_Status;
      refresh();
      move(14, 37);
      addstr(
          "0   0   0000000  0    0     0000    0000000  000000   0000       ");
      move(15, 37);
      addstr(
          " 0 0    0     0  0    0     0   0      0     0_____   0   0       ");
      move(16, 37);
      addstr(
          "  0     0     0  0    0     0  0       0     0        0  0        ");
      move(17, 37);
      addstr(
          "  0     0000000  000000     000     0000000  000000   000        ");
      refresh();

      move(13, 32);
      addstr("-----------------------------------------------------------------"
             "-----");
      for (int io = 1; io < 5; io++) {
        move(13 + io, 32);
        addch('-');
      }
      move(18, 32);
      addstr("-----------------------------------------------------------------"
             "-----");
      for (int iu = 1; iu < 5; iu++) {
        move(13 + iu, 101);
        addch('-');
      }
      refresh();
      move(25, 60);
      addstr("-------");
      move(26, 60);
      addstr("|leave|");
      move(27, 60);
      addstr("-------");
      move(21, 59);
      addstr("---------");
      move(22, 59);
      addstr("|restart|");
      move(23, 59);
      addstr("---------");
      refresh();
      bool onres = true;
      move(22, 50);
      addstr("*********");
      move(22, 68);
      addstr("*********");
      for (;;) {
        int input;
        input = getch();
        if (input == KEY_DOWN && onres == true) {
          move(22, 50);
          addstr("         ");
          move(22, 68);
          addstr("         ");
          onres = false;
          move(26, 51);
          addstr("*********");
          move(26, 67);
          addstr("*********");
        }
        if (input == KEY_UP && onres == false) {
          move(22, 50);
          addstr("*********");
          move(22, 68);
          addstr("*********");
          onres = true;
          move(26, 51);
          addstr("         ");
          move(26, 67);
          addstr("         ");
        }
        if (input == '\n' && onres == true) {
          clear();
          goto RESTART;
        }
        if (input == '\n' && onres == false) {
          clear();
          return 1;
        }
      }
    }
    user_input = getch();
    if (user_input == "w") {
      spaceship.up(status->x, status->y);
    } else if (user_input == "s") {
      spaceship.down(status->x, status->y);
    } else if (user_input == "a") {
      spaceship.left(status->x, status->y);
    } else if (user_input == "d") {
      spaceship.right(status->x, status->y);
    } else if (user_input == " " && ELAPSED(NOW - then).count() >= 150) {
      if (status->bullets == 0) {
        continue;
      }
      status->bullets--;
      spaceship.alterbullet_pstatus(status->bullets);
      then = NOW;
      if (status->bulletno == false) {
        status->bulletno = true;
        Bullet add;
        add.x = status->x + 9;
        add.y = status->y;
        status->bullpos.push_back(add);
        bullet = pthread_create(&thread, NULL, SpaceShip_Functions::Shoot,
                                (void *)status);
        // Timer variables starts here
      } else if (status->bulletno == true) {

        Bullet add;
        add.x = status->x + 9;
        add.y = status->y;
        status->bullpos.push_back(add);
      }

    } else {
    }
  }
  exit(0);
}

void GameMainPart() {

  fstream reader;
  reader.open("GameData.txt");
  string controls;
  string controls2;
  string level_num;
  string level_num2;
  getline(reader, controls);
  getline(reader, level_num);
  for (int i = 0; i < controls.size(); i++) {
    if (controls[i] != ' ') {
      controls2.push_back(controls[i]);
    }
  }
  for (int i = 0; i < level_num.size(); i++) {
    if (level_num[i] != ' ') {
      level_num2.push_back(level_num[i]);
    }
  }
  bool status;
  if (controls2 == "true") {
    status = true;
  }
  if (controls2 == "false") {
    status = false;
  }
  int level_im_on = stoi(level_num2);
  Level_Status gameset;
  gameset.controls = status;
  gameset.level_im_on = level_im_on;
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
REPRINTT:
  move(9, 37);
  addstr("000000  000000   000000  000000  000000  0   0  000000");
  move(10, 37);
  addstr("0       0    0   0    0  0       0        0 0   0     ");
  move(11, 37);
  addstr("000000  000000   000000  0       000000    0    000000");
  move(12, 37);
  addstr("     0  0        0    0  0       0        0 0   0     ");
  move(13, 37);
  addstr("000000  0        0    0  000000  000000  0   0  000000");
  move(16, 57);
  addstr("------------");
  move(17, 48);
  addstr("*********- continue -*********");
  move(18, 57);
  addstr("------------");
  move(20, 58);
  addstr("----------");
  move(21, 58);
  addstr("- levels -");
  move(22, 58);
  addstr("----------");
  move(24, 57);
  addstr("------------");
  move(25, 57);
  addstr("- settings -");
  move(26, 57);
  addstr("------------");
  move(28, 59);
  addstr("--------");
  move(29, 59);
  addstr("- exit -");
  move(30, 59);
  addstr("--------");
  refresh();
  int on = 1;
  for (;;) {
    int input;
    input = getch();
    if (input == KEY_DOWN) {
      if (on == 4) {
        continue;
      }
      if (on == 1) {
        on += 1;
        move(17, 48);
        addstr("         ");
        move(17, 69);
        addstr("         ");
        move(21, 49);
        addstr("*********");
        move(21, 68);
        addstr("*********");
      } else if (on == 2) {
        on += 1;
        move(21, 49);
        addstr("         ");
        move(21, 68);
        addstr("         ");
        move(25, 69);
        addstr("*********");
        move(25, 48);
        addstr("*********");
      } else if (on == 3) {
        on += 1;
        move(25, 69);
        addstr("         ");
        move(25, 48);
        addstr("         ");
        move(29, 50);
        addstr("*********");
        move(29, 67);
        addstr("*********");
      }
    }
    if (input == KEY_UP) {
      if (on == 1) {
        continue;
      }
      if (on == 2) {
        on -= 1;
        move(17, 48);
        addstr("*********");
        move(17, 69);
        addstr("*********");
        move(21, 49);
        addstr("         ");
        move(21, 68);
        addstr("         ");
      }
      if (on == 3) {
        on -= 1;
        move(21, 49);
        addstr("*********");
        move(21, 68);
        addstr("*********");
        move(25, 69);
        addstr("         ");
        move(25, 48);
        addstr("         ");
      }
      if (on == 4) {
        on -= 1;
        move(25, 69);
        addstr("*********");
        move(25, 48);
        addstr("*********");
        move(29, 50);
        addstr("         ");
        move(29, 67);
        addstr("         ");
      }
    }
    if (input == '\n') {
      if (on == 1) {
        clear();
        Game_Mech(gameset);
      }
      if (on == 4) {
        endwin();
        return;
      }
      int a = 0;
      int b = 37;
      int c = 9;
      if (on == 2) {
      LEAVE:
        clear();
        for (int i = 1; i <= level_im_on; i++) {
          move(c, b + a);
          printw("-------");
          move(c + 1, b + a);
          if (i == level_im_on) {
            printw("-**%d**-", i);
          } else {
            printw("-  %d  -", i);
          }
          move(c + 2, b + a);
          printw("-------");
          a += 5;
          if (i == 5) {
            c += 7;
          }
        }
        for (;;) {
          int input4 = getch();
          if (input4 == '\n') {
            clear();
            levelchk = 1;
            int exit_or_success = Game_Mech(gameset);
            if (exit_or_success == 1) {
              goto LEAVE;
            }
          }
          if (input4 == KEY_DOWN) {
          }
          if (input4 == KEY_UP) {
          }
          if (input4 == KEY_LEFT) {
          }
          if (input4 == KEY_RIGHT) {
          }
          if (input4 == 127) {
            clear();
            goto REPRINTT;
          }
        }
      }
      if (on == 3) {
      REPRINT:
        int onn = 1;
        clear();
        move(9, 50);
        addstr("--------------------------");
        if (status == false) {
          move(10, 41);
          addstr("*********-WASD      or      arrows-*********         WASD");
        }
        if (status == true) {
          move(10, 41);
          addstr("*********-WASD      or      arrows-*********         arrows");
        }
        move(11, 50);
        addstr("--------------------------");
        move(15, 50);
        addstr("--------------------------");
        move(16, 50);
        addstr("-  DELETE GAME PROGRESS  -");
        move(17, 50);
        addstr("--------------------------");
        for (;;) {
          int input2 = 0;
          input2 = getch();
          if (input2 == 127) {
            clear();
            goto REPRINTT;
          }
          if (input2 == KEY_UP && onn == 2) {
            onn--;
            move(16, 41);
            addstr("         ");
            move(16, 76);
            addstr("         ");
            move(10, 76);
            addstr("*********");
            move(10, 41);
            addstr("*********");
          } else if (input2 == KEY_DOWN && onn == 1) {
            onn++;
            move(16, 41);
            addstr("*********");
            move(16, 76);
            addstr("*********");
            move(10, 76);
            addstr("         ");
            move(10, 41);
            addstr("         ");
          } else if (input2 == '\n') {
            if (onn == 1) {
              if (status == false) {
                status = true;
                move(10, 94);
                addstr("arrows");
                refresh();
                std::fstream gamefile;
                gamefile.open("GameData.txt");
                gamefile << "true ";
                gamefile.close();

              } else if (status == true) {
                status = false;
                move(10, 94);
                addstr("WASD  ");
                refresh();
                std::fstream gamefile;
                gamefile.open("GameData.txt");
                gamefile << "false";
                gamefile.close();
              }
            }
            if (onn == 2) {
              clear();
              move(15, 43);
              addstr("------------------------------------");
              move(16, 43);
              addstr("- Are You Sure About This  (y/n)   -");
              move(17, 43);
              addstr("------------------------------------");
              for (;;) {
                string input3;
                input3 = getch();
                if (input3 == "y") {
                  level_im_on = 1;
                  goto REPRINT;
                } else if (input3 == "n") {
                  goto REPRINT;
                }
                refresh();
              }
            }
          }
        }
      }
    }
  }
}

/*
int exit_success = 0;
for (;;) {
  exit_success = GameMainPart();


}
*/
int main() {
  /* GameMainPart();*/
  default_gamefile();
  GameMainPart();
}
/*
int mx = 0, my = 0;

initscr();
getmaxyx(stdscr, mx, my);
endwin();

printf("%d %d", mx, my);

return 0;
*/

// ---------
// - ☠  0  -
// - >  16 -
// ---------

/* Bullet Thread :
int time_before;
int i = 0;
vector <Bullet> bullets_in_stock;
  for(;;){

}
*/

/*












*/
