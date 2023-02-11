#include <stdio.h>

#pragma output REGISTER_SP = 0xFFFF

#define R 6
#define C 7

void write_board();
int is_full();
int get_move(int player);
int valid_move(int column);
void make_move(int player, int column);
int win(int move);
int turn(int player);
void cls();
void go_to_home();
void set_colour(int, int);
void reset_attributes();
void set_attribute(int);

int board[R][C];
char name[2][20];

int main(void)
{
  int i;
  int j;
  int move;
  int player;
  int winner = 0;

  printf("Player 1 Name ");
  scanf("%s", name[0]);
  printf("Player 2 Name ");
  scanf("%s", name[1]);

  for (i = 0; i < R; i++)
  {
    for (j = 0; j < C; j++)
      board[i][j] = '.';
  }

  do
  {
    player = 1;
    if (turn(player))
    {
      winner = player;
      break;
    }

    player = 2;
    if (turn(player))
    {
      winner = player;
      break;
    }

  } while (is_full() == 0);

  if (winner != 0)
    printf("\n%s has won!\n", name[winner - 1]);

  else
    printf("\nIt's Draw!\n");

  return 0;
}

int turn(int player)
{
  int move;
  write_board();
  do
  {
    move = get_move(player);
  } while (valid_move(move) == 0);

  move -= 1;

  make_move(player, move);

  if (win(move) == 1)
  {
    printf("\n");
    write_board();
    return 1;
  }

  printf("\n");
  return 0;
}

void write_board()
{
  int i;
  int j;
  cls();
  go_to_home();

  for (i = 0; i < R; i++)
  {
    for (j = 0; j < C; j++)
    {
      switch (board[i][j])
      {
      case 'X':
        set_colour(63, 60);
        putchar('#');
        break;
      case 'O':
        set_colour(61, 60);
        putchar('#');
        break;
      default:
        set_colour(60, 60);
        putchar(' ');
        break;
      }
      putchar(' ');
      reset_attributes();
    }
    printf("\n");
  }
  for (i = 0; i < C; i++)
    printf("%d ", i + 1);
  printf("\n");
}

int is_full()
{
  int i;
  int j;

  for (i = 0; i < R; i++)
  {
    for (j = 0; j < C; j++)
      if (board[i][j] == '.')
        return 0;
  }

  return 1;
}

int get_move(int player)
{
  int out;
  if (player == 1)
  {
    set_attribute(91);
  }
  else
  {
    set_attribute(93);
  }
  printf("%s> ", name[player - 1]);
  scanf("%d", &out);
  reset_attributes();
  return out;
}

int valid_move(int column)
{
  if (column > C || column < 1 || board[0][column - 1] != '.')
  {
    printf("\nInvalid move\n");
    return 0;
  }
  return 1;
}

void make_move(int player, int column)
{
  int i;
  char ch;

  if (player == 1)
    ch = 'O';
  else
    ch = 'X';

  for (i = R; i >= 0; i--)
  {
    if (board[i][column] == '.')
    {
      board[i][column] = ch;
      break;
    }
  }
}

int checkRight(int depth, int col, int row, char player)
{
  col++;
  if (col > C || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkRight(depth, col, row, player);
}

int checkLeft(int depth, int col, int row, char player)
{
  col--;
  if (col < 0 || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkLeft(depth, col, row, player);
}

int checkDown(int depth, int col, int row, char player)
{
  row++;
  if (row > R || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkDown(depth, col, row, player);
}

int checkDownRight(int depth, int col, int row, char player)
{
  row++;
  col++;
  if (row > R || col > C || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkDownRight(depth, col, row, player);
}

int checkDownLeft(int depth, int col, int row, char player)
{
  row++;
  col--;
  if (row > R || col < 0 || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkDownLeft(depth, col, row, player);
}

int checkUpRight(int depth, int col, int row, char player)
{
  row--;
  col++;
  if (row < 0 || col > C || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkUpRight(depth, col, row, player);
}

int checkUpLeft(int depth, int col, int row, char player)
{
  row--;
  col--;
  if (row < 0 || col < 0 || board[row][col] != player)
  {
    return depth;
  }
  depth++;
  return checkUpLeft(depth, col, row, player);
}

int win(int column)
{
  int row;
  char player = '\0';

  // Find the last played counter
  for (row = 0; row < R; row++)
  {
    if (board[row][column] != '.')
    {
      player = board[row][column];
      break;
    }
  }

  return checkDown(0, column, row, player) + 1 >= 4 ||
         checkLeft(0, column, row, player) + checkRight(0, column, row, player) + 1 >= 4 ||
         checkDownLeft(0, column, row, player) + checkUpRight(0, column, row, player) + 1 >= 4 ||
         checkDownRight(0, column, row, player) + checkUpLeft(0, column, row, player) + 1 >= 4;
}

void cls()
{
  printf("\033[2J");
}

void go_to_home()
{
  printf("\033[H");
}

void set_colour(int forground, int background)
{
  forground = forground + 30;
  background = background + 40;
  printf("\033[%d;%dm", forground, background);
}

void set_attribute(int attribute)
{
  printf("\033[%dm", attribute);
}

void reset_attributes()
{
  printf("\033[0m");
}