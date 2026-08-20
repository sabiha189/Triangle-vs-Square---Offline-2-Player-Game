//Sabiha Sharker Piya(41230301530)
//Afsana Akter Mim(41230301565)

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// =====================================================
// WINDOW
// =====================================================

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

// =====================================================
// TRIANGLE POSITION
// =====================================================

float triangleX = 100.0f;
float triangleY = 400.0f;

// Triangle size
float triangleSize = 25.0f;

// =====================================================
// SQUARE POSITION
// =====================================================

float squareX = 400.0f;
float squareY = 100.0f;

// Square size
float squareSize = 30.0f;

// Square movement speed
float squareSpeed = 5.0f;

// =====================================================
// GAME VARIABLES
// =====================================================

// Game running status
bool gameRunning = true;

// Time when game started
clock_t gameStartTime;

// Time of last accepted mouse click
clock_t lastMouseClickTime;

// First click control
bool firstMouseClick = true;

// Game time = 2 minutes
const double GAME_TIME = 30.0;

// Mouse click interval = 2 seconds
const double MOUSE_INTERVAL = 2.0;


// =====================================================
// DRAW TEXT
// =====================================================

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


// =====================================================
// DRAW TRIANGLE
// =====================================================

void drawTriangle()
{
    // Orange color
    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_TRIANGLES);

        // Top
        glVertex2f(
            triangleX,
            triangleY + triangleSize
        );

        // Bottom-left
        glVertex2f(
            triangleX - triangleSize,
            triangleY - triangleSize
        );

        // Bottom-right
        glVertex2f(
            triangleX + triangleSize,
            triangleY - triangleSize
        );

    glEnd();
}


// =====================================================
// DRAW SQUARE
// =====================================================

void drawSquare()
{
    // Gray color
    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_QUADS);

        glVertex2f(
            squareX - squareSize,
            squareY - squareSize
        );

        glVertex2f(
            squareX + squareSize,
            squareY - squareSize
        );

        glVertex2f(
            squareX + squareSize,
            squareY + squareSize
        );

        glVertex2f(
            squareX - squareSize,
            squareY + squareSize
        );

    glEnd();
}


// =====================================================
// CHECK COLLISION
// =====================================================

bool checkCollision()
{
    // Approximate bounding box of triangle
    float triangleLeft = triangleX - triangleSize;
    float triangleRight = triangleX + triangleSize;

    float triangleBottom = triangleY - triangleSize;
    float triangleTop = triangleY + triangleSize;

    // Bounding box of square
    float squareLeft = squareX - squareSize;
    float squareRight = squareX + squareSize;

    float squareBottom = squareY - squareSize;
    float squareTop = squareY + squareSize;


    // Check overlap
    if (triangleRight >= squareLeft &&
        triangleLeft <= squareRight &&
        triangleTop >= squareBottom &&
        triangleBottom <= squareTop)
    {
        return true;
    }

    return false;
}


// =====================================================
// GET ELAPSED TIME
// =====================================================

double getGameTime()
{
    clock_t currentTime = clock();

    return (double)(currentTime - gameStartTime) / CLOCKS_PER_SEC;
}


// =====================================================
// DISPLAY
// =====================================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();


    // Draw triangle
    drawTriangle();


    // Draw square
    drawSquare();


    // Calculate elapsed time
    double elapsedTime = getGameTime();

    // Remaining time
    int remainingTime = (int)(GAME_TIME - elapsedTime);

    if (remainingTime < 0)
        remainingTime = 0;


    // ---------------------------------------------
    // Display timer
    // ---------------------------------------------

    glColor3f(1.0f, 1.0f, 1.0f);

    char timerText[50];

    sprintf(
        timerText,
        "Time Left: %d seconds",
        remainingTime
    );

    drawText(10, 475, timerText);


    // ---------------------------------------------
    // Display controls
    // ---------------------------------------------

    drawText(
        10,
        450,
        "Square: W A S D | Mouse: Move Triangle"
    );


    // ---------------------------------------------
    // Game Over Message
    // ---------------------------------------------

    if (!gameRunning)
    {
        glColor3f(1.0f, 1.0f, 1.0f);

        if (checkCollision())
        {
            drawText(
                160,
                270,
                "GAME OVER!"
            );

            drawText(
                130,
                240,
                "Triangle Caught!"
            );
        }
        else
        {
            drawText(
                160,
                270,
                "GAME OVER!"
            );

            drawText(
                135,
                240,
                "Time Up!"
            );
        }

        drawText(
            155,
            210,
            "Press R to Restart"
        );
    }


    glutSwapBuffers();
}


// =====================================================
// KEYBOARD FUNCTION
// =====================================================

void keyboardFunc(unsigned char key, int x, int y)
{
    // Restart game
    if (key == 'r' || key == 'R')
    {
        triangleX = 100.0f;
        triangleY = 400.0f;

        squareX = 400.0f;
        squareY = 100.0f;

        gameStartTime = clock();

        lastMouseClickTime = clock();

        firstMouseClick = true;

        gameRunning = true;

        glutPostRedisplay();

        return;
    }


    // If game is over, don't move square
    if (!gameRunning)
        return;


    // Move square UP
    if (key == 'w' || key == 'W')
    {
        squareY += squareSpeed;
    }


    // Move square DOWN
    else if (key == 's' || key == 'S')
    {
        squareY -= squareSpeed;
    }


    // Move square LEFT
    else if (key == 'a' || key == 'A')
    {
        squareX -= squareSpeed;
    }


    // Move square RIGHT
    else if (key == 'd' || key == 'D')
    {
        squareX += squareSpeed;
    }


    // Keep square inside window
    if (squareX - squareSize < 0)
        squareX = squareSize;

    if (squareX + squareSize > WINDOW_WIDTH)
        squareX = WINDOW_WIDTH - squareSize;

    if (squareY - squareSize < 0)
        squareY = squareSize;

    if (squareY + squareSize > WINDOW_HEIGHT)
        squareY = WINDOW_HEIGHT - squareSize;


    // Check collision
    if (checkCollision())
    {
        gameRunning = false;
    }


    glutPostRedisplay();
}


// =====================================================
// MOUSE FUNCTION
// =====================================================

void mouseFunc(int button, int state, int x, int y)
{
    // Only left mouse button
    if (button != GLUT_LEFT_BUTTON)
        return;

    // Only when mouse button is released
    if (state != GLUT_UP)
        return;

    // Don't accept mouse click after game over
    if (!gameRunning)
        return;


    clock_t currentTime = clock();


    // ---------------------------------------------
    // First mouse click
    // ---------------------------------------------

    if (firstMouseClick)
    {
        firstMouseClick = false;

        lastMouseClickTime = currentTime;

        // Convert mouse Y coordinate
        int oglY = WINDOW_HEIGHT - y;

        triangleX = (float)x;
        triangleY = (float)oglY;

        // Keep triangle inside window
        if (triangleX - triangleSize < 0)
            triangleX = triangleSize;

        if (triangleX + triangleSize > WINDOW_WIDTH)
            triangleX = WINDOW_WIDTH - triangleSize;

        if (triangleY - triangleSize < 0)
            triangleY = triangleSize;

        if (triangleY + triangleSize > WINDOW_HEIGHT)
            triangleY = WINDOW_HEIGHT - triangleSize;

        glutPostRedisplay();

        return;
    }


    // ---------------------------------------------
    // Calculate time since last click
    // ---------------------------------------------

    double timeSinceLastClick =
        (double)(currentTime - lastMouseClickTime)
        / CLOCKS_PER_SEC;


    // Accept click only after 2 seconds
    if (timeSinceLastClick >= MOUSE_INTERVAL)
    {
        lastMouseClickTime = currentTime;


        // Convert mouse Y coordinate
        int oglY = WINDOW_HEIGHT - y;


        // Move triangle to mouse position
        triangleX = (float)x;
        triangleY = (float)oglY;


        // Keep triangle inside window

        if (triangleX - triangleSize < 0)
            triangleX = triangleSize;

        if (triangleX + triangleSize > WINDOW_WIDTH)
            triangleX = WINDOW_WIDTH - triangleSize;

        if (triangleY - triangleSize < 0)
            triangleY = triangleSize;

        if (triangleY + triangleSize > WINDOW_HEIGHT)
            triangleY = WINDOW_HEIGHT - triangleSize;


        // Check collision
        if (checkCollision())
        {
            gameRunning = false;
        }


        glutPostRedisplay();
    }
}


// =====================================================
// TIMER FUNCTION
// =====================================================

void timerFunc(int value)
{
    if (gameRunning)
    {
        double elapsedTime = getGameTime();


        // Check 2 minute limit
        if (elapsedTime >= GAME_TIME)
        {
            gameRunning = false;
        }


        // Check collision
        if (checkCollision())
        {
            gameRunning = false;
        }
    }


    glutPostRedisplay();


    // Call timer again after 100 milliseconds
    glutTimerFunc(100, timerFunc, 0);
}


// =====================================================
// RESHAPE FUNCTION
// =====================================================

void reshape(int w, int h)
{
    glViewport(
        0,
        0,
        (GLsizei)w,
        (GLsizei)h
    );


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    glOrtho(
        0,
        WINDOW_WIDTH,
        0,
        WINDOW_HEIGHT,
        -1,
        1
    );


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}


// =====================================================
// INITIALIZATION
// =====================================================

void initialization()
{
    // Black background
    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );


    // Start game timer
    gameStartTime = clock();

    lastMouseClickTime = clock();
}


// =====================================================
// MAIN FUNCTION
// =====================================================

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);


    // RGB + Double Buffer
    glutInitDisplayMode(
        GLUT_RGB | GLUT_DOUBLE
    );


    // Window position
    glutInitWindowPosition(
        100,
        50
    );


    // Window size
    glutInitWindowSize(
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );


    // Create window
    glutCreateWindow(
        "Triangle Catch Game"
    );


    // Register functions
    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboardFunc);

    glutMouseFunc(mouseFunc);


    // Initialization
    initialization();


    // Start timer
    glutTimerFunc(
        100,
        timerFunc,
        0
    );


    // Start OpenGL loop
    glutMainLoop();


    return 0;
}
