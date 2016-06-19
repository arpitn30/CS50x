//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//
 
// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
 
// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>
 
// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
 
// number of rows of bricks
#define ROWS 5
 
// number of columns of bricks
#define COLS 10
 
// radius of ball in pixels
#define RADIUS 15
 
// dimensions of paddle
#define PADX 68
#define PADY 10
 
// dimensions of bricks
#define BRKX 35.5
#define BRKY 12
 
// lives
#define LIVES 3
 
// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
 
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
 
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
 
    // instantiate bricks
    initBricks(window);
 
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
 
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
 
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
 
    // number of bricks initially
    int bricks = COLS * ROWS;
 
    // number of lives initially
    int lives = LIVES;
 
    // number of points initially
    int points = 0;
 
    // keep playing until game over
    double velx = 2 + drand48() * 3, vely = 2;
    int cntr = 0;
    
    //lives left
    GLabel lifeleft = newGLabel("Lives: ");
    setFont(lifeleft, "SansSerif-20");
    setColor(lifeleft, "BLACK");
    setLocation(lifeleft, 0, getHeight(lifeleft) + 5) ;
    add(window, lifeleft);
        
    waitForClick();
    while (lives > 0 && bricks > 0)
    {
        // Region Paddle Movements
        GEvent eventp = getNextEvent(MOUSE_EVENT);
        if (eventp != NULL)
        {
            if (getEventType(eventp) == MOUSE_MOVED)
            {
                double xp = getX(eventp) - PADX / 2;
                double yp = ((getHeight(window) - PADY) * 7.2) / 8;
                if(xp <= 0)
                    xp = 0;
                else if(xp >= getWidth(window) - PADX)
                    xp = getWidth(window) - PADX;
                setLocation(paddle, xp, yp);
            }
        }
        
        // Region Ball Movements
        
        move(ball, velx, vely);
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velx = -velx;
        }
        else if (getX(ball) <= 0)
        {
            velx = -velx;
        }
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            waitForClick();
            setLocation(ball, (getWidth(window) - RADIUS) / 2, (getHeight(window) - RADIUS) / 2);
            velx = -1 + drand48() * 4;
            continue;
        }
        else if (getY(ball) <= 0)
        {
            vely = -vely;            
        }
        
        // Region Object Collisions
        GObject object = detectCollision(window, ball);
        if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            vely = -vely;
            if(object != paddle)
            {
                removeGWindow(window, object);
                bricks--;   cntr++;
                updateScoreboard(window, label, cntr);               
            }
        }
        
        // Lives
        char s[4];
        sprintf(s, "Lives: %i", lives);
        setLabel(lifeleft, s);        
        
        pause(10);
    }
    
    // Winner
    if (cntr == 50)
    {
        GLabel label = newGLabel("YOU WON :)");
        setFont(label, "SansSerif-50");
        setColor(label, "GREEN");
        setLocation(label, (getWidth(window) - getWidth(label)) / 2, getHeight(window) / 2 + 70);
        add(window, label);
    }
    else
    {
        GLabel label = newGLabel("YOU LOST :(");
        setFont(label, "SansSerif-45");
        setColor(label, "RED");
        setLocation(label, (getWidth(window) - getWidth(label)) / 2, getHeight(window) / 2 + 70);
        add(window, label);
    }
 
    // wait for click before exiting
    waitForClick();
 
    // game over
    closeGWindow(window);
    return 0;
}
 
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    double y = (getHeight(window) - PADY) / 12;
    for(int i = 0; i < ROWS; i++)
    {
        double x = 0;
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(x, y, BRKX, BRKY);
            switch(i)
            {
                case 0: setColor(brick, "RED"); break;
                case 1: setColor(brick, "ORANGE"); break;
                case 2: setColor(brick, "YELLOW"); break;
                case 3: setColor(brick, "GREEN"); break;
                case 4: setColor(brick, "CYAN"); break;
            }
            setFilled(brick, true);
            add(window, brick);
            x = x + 5 + BRKX;
        }
        y = y + BRKY + 5;        
    }
}
 
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    double xb = (getWidth(window) - RADIUS) / 2;
    double yb = (getHeight(window) - RADIUS) / 2;
    GOval ball = newGOval(xb, yb, RADIUS, RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}
 
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    double x = (getWidth(window) - PADX) / 2;
    double y = ((getHeight(window) - PADY) * 7.2) / 8;
    GRect paddle = newGRect(x, y, PADX, PADY);
    setColor(paddle, "BLUE");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}
 
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-40");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y - RADIUS);
    return label;
}
 
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
 
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
 
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);
 
    // for checking for collisions
    GObject object;
 
    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
 
    // no collision
    return NULL;
}
