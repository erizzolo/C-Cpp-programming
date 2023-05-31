/**
 * Gioco snake, an example
 */

#include "rlutil.h"
#include <ctime>

// // for precise timing
// #include <chrono>
// using Clock = std::chrono::steady_clock;
// using TimePoint = std::chrono::time_point<Clock>;
// using Duration = std::chrono::duration<double>;
// const Clock theClock;

using namespace std;
using namespace rlutil;

// a position on the screen/board
struct position
{
    int x, y;
};

// leave first 4 rows, 1 column and last 1 row, 1 col
#define X_MIN 2
#define Y_MIN 5
#define X_MAX (tcols() - 1)
#define Y_MAX (trows() - 1)
#define X_SCALE 3
#define Y_SCALE 2

struct space
{
    position scale;
    position dimension;
    bool toroidal;
};

using symbol = char; // maybe string ?!

struct object
{
    position where;
    symbol what;
};

// directions (should be an enum...)
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define DIRECTIONS 4

// chars for snake head
const char HEAD_CHARS[DIRECTIONS]{'>', '<', 'A', 'V'};

// change in position for a moving object
const position MOVEMENTS[DIRECTIONS]{{+1, 0}, {-1, 0}, {0, -1}, {0, +1}};

// a combination of colours
struct colour
{
    int foreground, background;
};

const int MAX_SNAKE_LENGTH = 100;
const int START_SNAKE_LENGTH = 5;

struct snake
{
    position body[MAX_SNAKE_LENGTH];
    int head, tail; // tail and head indexes
    int direction;  // current direction
    bool crashed{false};
};

struct configuration
{
    position scale;
    bool toroidal{true};
};

const size_t MAX_OBSTACLES = 100;

struct level
{
    int speed{5};
    int toBeEaten{5};
};

struct game
{
    space theSpace;
    snake cobra;
    object food;
    object obstacles[MAX_OBSTACLES]; // not used
    size_t numObstacles{0};          // not used
    // Duration elapsed;
    // TimePoint startTime;
    time_t elapsed{0};
    time_t startTime;
    bool paused{false};
    level lvl;
};

// general functions
void showWelcomeScreen();
void showFarewellScreen();
void configurate(configuration &config);
void statusMsg(const char *msg);
void showMainMenu();
void showGameMenu();

void play(const configuration &config);
game makeGame(const configuration &config);
void paintGame(const game &g);
void showTimer(game &g);

void paint(const position &p, const colour &c, const char s, position scale);
void move(position &o, const space &s, const position delta);
bool coincident(const position &first, const position &second);
snake makeSnake(const game &g);
object makeFood(const game &g);
void moveSnake(game &g);

#define DELAY 20
#define SNAKE_DELAY 5

const colour GRASS{WHITE, GREEN};
const colour HEAD_COLOUR{RED, GREEN};
const colour FOOD_COLOUR{RED, BLACK};

void setEcho(bool echo)
{
#ifndef _WIN32
    static struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    if (echo)
    {
        oldt.c_lflag |= ECHO;
    }
    else
    {
        oldt.c_lflag &= ~ECHO;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

int main(int argc, char *argv[])
{
    saveDefaultColor();
    setConsoleTitle("Gioco snake");
    hidecursor();
    setEcho(false);

    showWelcomeScreen();

    srand(time(nullptr));

    configuration config;
    config.scale = {X_SCALE, Y_SCALE};
    bool running = true;
    do
    {
        showMainMenu();
        int k = getkey();
        statusMsg("");
        switch (k)
        {
        case 'C':
        case 'c':
            configurate(config);
            break;
        case 'N':
        case 'n':
            play(config);
            break;
        case 'X':
        case 'x':
            running = false;
            break;
        default:
            break;
        }
    } while (running);

    showFarewellScreen();
    setEcho(true);
    resetColor();

    return 0;
}

bool playLevel(game &g)
{
    paintGame(g);
    statusMsg("Press any key to start");
    anykey("");
    g.startTime = time(NULL);

    bool running = true;
    int animationSpeed = 0;
    do
    {
        if (kbhit())
        {
            switch (getkey())
            {
            case KEY_LEFT:
                g.cobra.direction = LEFT;
                break;
            case KEY_RIGHT:
                g.cobra.direction = RIGHT;
                break;
            case KEY_UP:
                g.cobra.direction = UP;
                break;
            case KEY_DOWN:
                g.cobra.direction = DOWN;
                break;
            case KEY_ESCAPE:
                running = false;
                break;
            case KEY_SPACE:
                if (g.paused)
                    g.startTime = time(NULL);
                else
                    g.elapsed += time(NULL) - g.startTime;
                g.paused = !g.paused;
                break;
            }
        }
        if (!g.paused)
        {
            if (animationSpeed == 0)
            {
                moveSnake(g);
                showTimer(g);
                animationSpeed = g.lvl.speed;
            }
            animationSpeed--;
        }
        msleep(DELAY);
    } while (running && !g.cobra.crashed && g.lvl.toBeEaten > 0);
    if (g.cobra.crashed)
    {
        statusMsg("Sorry, you have crashed! ");
        msleep(2000);
    }
    return running && !g.cobra.crashed; // level completed or not
}

void play(const configuration &config)
{
    showGameMenu();
    game g = makeGame(config);
    while (playLevel(g))
    {
        // next level
        g.lvl.speed--;
        g.lvl.toBeEaten = 10 - g.lvl.speed;
    }
}

void paint(const position &p, const colour &c, const char s, position scale)
{
    int sx = X_MIN + p.x * scale.x, sy = Y_MIN + p.y * scale.y;
    setColor(c.foreground);
    setBackgroundColor(c.background);
    for (int x = 0; x < scale.x; ++x)
    {
        for (int y = 0; y < scale.y; ++y)
        {
            gotoxy(sx + x, sy + y);
            cout << s;
        }
    }
    cout.flush();
}

void updateCoord(int &coord, int amount, int limit, bool toroidal)
{
    coord += amount;
    if (toroidal)
    {
        if (coord < 0)
        {
            coord = limit - 1;
        }
        else if (coord >= limit)
        {
            coord = 0;
        }
    }
}

void move(position &o, const space &s, const position delta)
{
    updateCoord(o.x, delta.x, s.dimension.x, s.toroidal);
    updateCoord(o.y, delta.y, s.dimension.y, s.toroidal);
}

bool coincident(const position &first, const position &second)
{
    return first.x == second.x && first.y == second.y;
}

snake makeSnake(const game &g)
{
    snake result;
    result.head = 0, result.tail = START_SNAKE_LENGTH - 1;
    result.direction = RIGHT;
    position start{g.theSpace.dimension.x / 2, g.theSpace.dimension.y / 2};
    for (int i = result.head; i < result.tail; ++i)
    {
        result.body[i] = start;
        move(start, g.theSpace, MOVEMENTS[LEFT]);
    }
    return result;
}

colour bodyColour(int pos)
{
    return {BLACK, BLUE};
    // if (pos % 2 == 0)
    //     return {BLACK, YELLOW};
    // else
    //     return {WHITE, BLACK};
}

bool hitSnake(const position &p, const snake &s)
{
    for (int i = s.head; i != s.tail; i = (i + 1) % MAX_SNAKE_LENGTH)
        if (coincident(s.body[i], p))
            return true;
    return false;
}

position randPosition(const space &s)
{
    position result;
    result.x = rand() % s.dimension.x;
    result.y = rand() % s.dimension.y;
    return result;
}

object makeFood(const game &g)
{
    object result{randPosition(g.theSpace), '*'};
    while (hitSnake(result.where, g.cobra))
    {
        result.where = randPosition(g.theSpace);
    }
    return result;
}

bool isOutOfRange(int x, int min, int max)
{
    return x < min || x >= max;
}

bool outOfSpace(const position &p, const space &s)
{
    return isOutOfRange(p.x, 0, s.dimension.x) ||
           isOutOfRange(p.y, 0, s.dimension.y);
}

void moveSnake(game &g)
{
    position newHead = g.cobra.body[g.cobra.head];                     // copy head
    move(newHead, g.theSpace, MOVEMENTS[g.cobra.direction]);           // move new head
    if (hitSnake(newHead, g.cobra) || outOfSpace(newHead, g.theSpace)) // check bounds
    {
        g.cobra.crashed = true;
    }
    else
    {
        paint(g.cobra.body[g.cobra.head], bodyColour(g.cobra.head), ' ', g.theSpace.scale); // old head is body now
        if (g.cobra.head-- == 0)                                                            // move insertion point
            g.cobra.head = MAX_SNAKE_LENGTH - 1;
        g.cobra.body[g.cobra.head] = newHead;
        if (coincident(newHead, g.food.where)) // has eaten
        {
            g.food = makeFood(g);
            paint(g.food.where, FOOD_COLOUR, g.food.what, g.theSpace.scale);
            g.lvl.toBeEaten--;
        }
        else
        {
            if (g.cobra.tail-- == 0) // move removal point
                g.cobra.tail = MAX_SNAKE_LENGTH - 1;
            paint(g.cobra.body[g.cobra.tail], GRASS, ' ', g.theSpace.scale);
        }
        paint(newHead, HEAD_COLOUR, HEAD_CHARS[g.cobra.direction], g.theSpace.scale);
    }
}
void showWelcomeScreen()
{
    cls();
    // gotoxy(1, 1);
    cout << "Welcome" << endl;
    statusMsg("Press any key to proceed...");
    anykey("");
}

void showFarewellScreen()
{
    cls();
    // gotoxy(1, 1);
    cout << "Bye bye " << endl;
    msleep(1000);
}

void showMainMenu()
{
    resetColor();
    cls();
    // gotoxy(1, 1);
    cout << "C: configuration" << endl;
    cout << "N: new game" << endl;
    cout << "X: exit" << endl;
    statusMsg("Choose an option");
}

void showConfigMenu(const configuration &config)
{
    resetColor();
    cls();
    // gotoxy(1, 1);
    cout << "Current scale " << config.scale.x << ", " << config.scale.y;
    cout << "; space " << (config.toroidal ? "toroidal" : "flat") << endl;
    cout << "T: toroidal space" << endl;
    cout << "F: flat space" << endl;
    cout << "Arrow keys: change horizontal/vertical scale" << endl;
    cout << "X: exit" << endl;
    statusMsg("Choose an option");
}

void showGameMenu()
{
    resetColor();
    cls();
    // gotoxy(1, 1);
    cout << "Arrow keys: change snake direction" << endl;
    cout << "Space bar: pause/resume game" << endl;
    cout << "Escape: exit game" << endl;
}

void statusMsg(const char *msg)
{
    resetColor();
    gotoxy(1, trows());
    for (int c = 0; c < tcols(); ++c)
        cout << " ";
    gotoxy(1, trows());
    cout << msg;
    cout.flush();
}

void showTimer(game &g)
{
    if (!g.paused)
    {
        resetColor();
        gotoxy(2, 4);
        int seconds = g.elapsed + time(NULL) - g.startTime;
        int hours = seconds / 3'600;
        seconds -= hours * 3'600;
        int minutes = seconds / 60;
        seconds -= minutes * 60;
        printf("Time: %02d:%02d:%02d", hours, minutes, seconds);
        cout.flush();
    }
}

void configurate(configuration &config)
{

    bool running = true;
    statusMsg("");
    showConfigMenu(config);
    do
    {
        if (kbhit())
        {

            switch (getkey())
            {
            case 'T':
            case 't':
                config.toroidal = true;
                break;
            case 'F':
            case 'f':
                config.toroidal = false;
                break;
            case KEY_LEFT:
                if (config.scale.x > 1)
                    config.scale.x--;
                break;
            case KEY_RIGHT:
                if (config.scale.x < 3)
                    config.scale.x++;
                break;
            case KEY_UP:
                if (config.scale.y < 3)
                    config.scale.y++;
                break;
            case KEY_DOWN:
                if (config.scale.y > 1)
                    config.scale.y--;
                break;
            case 'X':
            case 'x':
                running = false;
                break;
            default:
                break;
            }
            showConfigMenu(config);
        }
    } while (running);

    statusMsg("Configuration saved!");
}

space makeSpace(const configuration &config)
{
    space result;
    result.scale = config.scale;
    result.dimension = {(X_MAX - X_MIN + 1) / config.scale.x, (Y_MAX - Y_MIN + 1) / config.scale.y};
    result.toroidal = config.toroidal;
    return result;
}

game makeGame(const configuration &config)
{
    game result;
    result.theSpace = makeSpace(config);
    result.cobra = makeSnake(result);
    result.food = makeFood(result);
    return result;
}

void paintGame(const game &g)
{
    // paint background
    for (int row = 0; row < g.theSpace.dimension.y; ++row)
        for (int col = 0; col < g.theSpace.dimension.x; ++col)
            paint({col, row}, GRASS, ' ', g.theSpace.scale);
    for (int i = g.cobra.head; i != g.cobra.tail; i = (i + 1) % MAX_SNAKE_LENGTH)
    {
        paint(g.cobra.body[i], bodyColour(i), ' ', g.theSpace.scale);
    }
    paint(g.cobra.body[g.cobra.head], HEAD_COLOUR, HEAD_CHARS[g.cobra.direction], g.theSpace.scale);
    paint(g.food.where, FOOD_COLOUR, g.food.what, g.theSpace.scale);
}
