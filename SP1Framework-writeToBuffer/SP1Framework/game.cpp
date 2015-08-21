// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Framework\timer.h"
int monsterdelay = 0; 
int monster1delay = 0;
int whipdelay = 0;
int health = 3;
int ammo = 5;

GAMESTATES g_eGameState = SPLASH;
// Console object


Console console(75, 27, "SP1 Framework");


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

// Initial print map
int printMap[MAP_HEIGHT][MAP_WIDTH] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 9, 2, 0, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 2, 1, 1, 0, 1, 1, 2, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 0, 1, 1, 2, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 2, 0, 0, 2, 0, 2, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 9, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 1, 1, 3, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 2, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 2, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 9, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Game specific variables here
COORD charLocation;
COORD	g_cConsoleSize;
COORD	g_cChaserLoc;
COORD	g_cChaser1Loc;
COORD	g_cProjectile;
COORD CurentLocation;
// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;
    charLocation.X = 3;
    charLocation.Y = 14;
	g_cChaserLoc.X = 26;
    g_cChaserLoc.Y = 2;
	g_cChaser1Loc.X = 26;
	g_cChaser1Loc.Y = 24;


	//initial state
	g_eGameState = SPLASH;
	


    // sets the width, height and the font name to use in the console
    console.setConsoleFont(0, 16, L"Consolas");
}

// Do your clean up of memory here
// This is called once just before the game exits
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    console.clearBuffer();
}
/*
	This function checks if any key had been pressed since the last time we checked
	If a key is pressed, the value for that particular key will be true
	
	Add more keys to the enum in game.h if you need to detect more keys
	To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
	For Alphanumeric keys, the values are their ascii values (uppercase).
*/
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_W] = isKeyPressed('W');
	keyPressed[K_A] = isKeyPressed('A');
	keyPressed[K_S] = isKeyPressed('S');
	keyPressed[K_D] = isKeyPressed('D');
}

/*
	This is the update function
	double dt - This is the amount of time in seconds since the previous call was made

	Game logic should be done here.
	Such as collision checks, determining the position of your game characters, status updates, etc
	If there are any calls to write to the console here, then you are doing it wrong.

    If your game has multiple states, you should determine the current state, and call the relevant function here.
*/
void update(double dt)
{

    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;

	switch (g_eGameState){
	case GAME: gameplay();
		break;
	default: SPLASH : splashwait();
	}
}

void startrender(){
	clearScreen();
	switch (g_eGameState){
	case SPLASH: splash();
	case GAME: render();
		break;
	}
}
void splashwait(){
	if (elapsedTime > 3.0){
		g_eGameState = GAME;
	}
}
void gameplay(){

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    // sound can be played here too.
}

/*
    This is the render loop
    At this point, you should know exactly what to draw onto the screen.
    Just draw it!
    To get an idea of the values for colours, look at console.h and the URL listed there
*/
void render()
{
    clearScreen();  // clears the current screen and draw from scratch
	switch (g_eGameState) {
	case SPLASH: splash();
		break;
	case GAME: renderGame();
		break;
	}
	
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();// dump the contents of the buffer to the screen, one frame worth of game
}

void renderGame() {
	renderMap();        // renders the map to the buffer first
	moveMonster();		//moves the monsters
	moveMonster1();
	renderMap(); // renders the character into the buffer
	projectile();// renders the map to the buffer first
	renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    //Print Map
    COORD c;
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < MAP_HEIGHT; i++){
        c.Y = i;
        for (int j = 0; j < MAP_WIDTH; j++){
            c.X = j;
            if (printMap[i][j] == 1){
                console.writeToBuffer(c, (char)219, 0x03);
            }
            else if (printMap[i][j] == 2){
                console.writeToBuffer(c, (char)177, 0x0C);
            }
            else if (printMap[i][j] == 3){
                console.writeToBuffer(c, (char)240);
            }
            else if (printMap[i][j] == 9){
                console.writeToBuffer(c, (char)241);
            }
            else{
                console.writeToBuffer(c, " ");
            }
        }
        std::cout << std::endl;
    }
	minimap();
	HUD();
}





void moveCharacter()
{
	monsterdelay++;
	monster1delay++;
        //PLAYER MOVEMENT
        // JUMP UP
        if (keyPressed[K_UP] && keyPressed[K_SPACE] && charLocation.Y > 0)
        {        
            if (printMap[charLocation.Y - 2][charLocation.X] == 1){

            }    
            else{
                Beep(1440, 30);
                charLocation.Y -= 2; 
            }
        }
        // JUMP LEFT
        else if (keyPressed[K_LEFT] && keyPressed[K_SPACE] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X - 2] == 1){

            }
            else{
                Beep(202, 30);
                charLocation.X -= 2;
            }
        }
        // JUMP DOWN
        else if (keyPressed[K_DOWN] && keyPressed[K_SPACE] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 2][charLocation.X] == 1){
            }
            else{
                Beep(1440, 30);
                charLocation.Y += 2;
            }
        }
        // JUMP RIGHT
        else if (keyPressed[K_RIGHT] && keyPressed[K_SPACE] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 2] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X += 2;
            }
        }
        //MOVE UP
        else if (keyPressed[K_UP] && charLocation.Y > 0)
        {
            if (printMap[charLocation.Y - 1][charLocation.X] == 1){
                
            }
            else{
                Beep(1440, 30);
                charLocation.Y -= 1;
            }
        }
        //MOVE LEFT
        else if (keyPressed[K_LEFT] && charLocation.X > 0)
        {
            if (printMap[charLocation.Y][charLocation.X -1] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X -= 1;
            }
        }
        //MOVE DOWN
        else if (keyPressed[K_DOWN] && charLocation.Y < console.getConsoleSize().Y - 1)
        {
            if (printMap[charLocation.Y + 1][charLocation.X] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.Y += 1;
            }
        }
        //MOVE RIGHT
        else if (keyPressed[K_RIGHT] && charLocation.X < console.getConsoleSize().X - 1)
        {
            if (printMap[charLocation.Y][charLocation.X + 1] == 1){

            }
            else{
                Beep(1440, 30);
                charLocation.X += 1;
            }
        }
        refill();
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x00);
}

void renderCharacter()
{
    // Draw the location of the character
    console.writeToBuffer(charLocation, (char)233, 0x0D);
	console.writeToBuffer(g_cChaserLoc, (char)5, 0x0C);
	console.writeToBuffer(g_cChaser1Loc, (char)5, 0x0C);
}

void renderFramerate()
{
    //COORD c;
    //// displays the framerate
    //std::ostringstream ss;
    //ss << std::fixed << std::setprecision(3);
    //ss << 1.0 / deltaTime << "fps";
    //c.X = console.getConsoleSize().X - 9;
    //c.Y = 0;
    //console.writeToBuffer(c, ss.str(), 0x59);

    //// displays the elapsed time
    //ss.str("");
    //ss << elapsedTime << "secs";
    //c.X = 0;
    //c.Y = 0;
    //console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    console.flushBufferToConsole();
}
//collision check/damage calculation
void collision(){
    if (charLocation.X - 1 == g_cChaserLoc.X && charLocation.Y + 1 == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;
	} // Top left
	else if (charLocation.X == g_cChaserLoc.X && charLocation.Y + 1 == g_cChaserLoc.Y){
		g_cChaserLoc.X = 26;
		monsterDeath();
		health -= 1;
	} // Top Middle
	else if (charLocation.X + 1 == g_cChaserLoc.X && charLocation.Y + 1 == g_cChaserLoc.Y){
		g_cChaserLoc.X = 26;
		monsterDeath();
		health -= 1;
	} // Top Right
	else if (charLocation.X - 1 == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;
	} // Left
	else if (charLocation.X == g_cChaserLoc.X  && charLocation.Y == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;

	} // Middle
	else if (charLocation.X + 1 == g_cChaserLoc.X && charLocation.Y == g_cChaserLoc.Y){
		g_cChaserLoc.X = 26;
		monsterDeath();
		health -= 1;
	} // Right

	else if (charLocation.X - 1 == g_cChaserLoc.X && charLocation.Y - 1 == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;
	} // Btm Left
	else if (charLocation.X == g_cChaserLoc.X && charLocation.Y - 1 == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;
	} // Btm Middle
	else if (charLocation.X + 1 == g_cChaserLoc.X && charLocation.Y - 1 == g_cChaserLoc.Y){
		monsterDeath();
		health -= 1;
	} // Btm Right 
}
// PROJECTILE
void projectile() {
    if (ammo >= 0){
        if (keyPressed[K_W]) {
            ammo -= 1;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y - 1;
            for (int i = 0; i < 2; ++i) {
                if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                    console.writeToBuffer(g_cProjectile, (char)30, 0x0B);
                    projKill();
                    projKill1();
                    g_cProjectile.Y -= 1;
                }
                else{
                    break;
                }
            }
        }
        else if (keyPressed[K_A]) {
            ammo -= 1;
            g_cProjectile.X = charLocation.X - 1;
            g_cProjectile.Y = charLocation.Y;
            for (int i = 0; i < 2; ++i) {
                if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                    console.writeToBuffer(g_cProjectile, (char)17, 0x0B);
                    projKill();
                    projKill1();
                    g_cProjectile.X -= 1;
                }
                else{
                    break;
                }
            }
        }
        else if (keyPressed[K_S]) {
            ammo -= 1;
            whipdelay = 0;
            g_cProjectile.X = charLocation.X;
            g_cProjectile.Y = charLocation.Y + 1;
            for (int i = 0; i < 2; ++i) {
                if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                    console.writeToBuffer(g_cProjectile, (char)31, 0x0B);
                    projKill();
                    projKill1();
                    g_cProjectile.Y += 1;
                }
                else{
                    break;
                }
            }
        }
        else if (keyPressed[K_D]) {
            ammo -= 1;
            g_cProjectile.X = charLocation.X + 1;
            g_cProjectile.Y = charLocation.Y;
            for (int i = 0; i < 2; ++i) {
                if (printMap[g_cProjectile.Y][g_cProjectile.X] != 1){
                    console.writeToBuffer(g_cProjectile, (char)16, 0x0B);
                    projKill();
                    projKill1();
                    g_cProjectile.X += 1;
                }
                else{
                    break;
                }
            }
        }
    }
}


void minimap() {
	COORD c;
	#define MINIMAP_WIDTH 22
	#define MINIMAP_HEIGHT 10

	for (int i = 0; i < MINIMAP_HEIGHT; i++) {
		c.Y = i;
		console.writeToBuffer(c, '#');
		for (int j = 0; j < MINIMAP_WIDTH; j++) {
			c.X = console.getConsoleSize().X + j - 22;
			console.writeToBuffer(c, ' ');
		}
	}

	for (int k = 0; k < MINIMAP_WIDTH; k++) {
		for (int i = 0; i < 3; i++){
			c.X = console.getConsoleSize().X + k - 22;
			console.writeToBuffer(c, '_');
		}
	}

}

void HUD() {
	COORD c;
	#define HUD_WIDTH 22
	#define HUD_HEIGHT 17

	c.X = console.getConsoleSize().X - 21;
	c.Y = console.getConsoleSize().Y - 16;

	for (int m = 0; m < 4; m++){
		console.writeToBuffer(c, "HEALTH");
	}
	
	for (int m = 0; m < health; m++){
		c.X = console.getConsoleSize().X - 21 + m;
		c.Y = console.getConsoleSize().Y - 15;
		console.writeToBuffer(c, (char)235);
	}
}
void randomSeed(){
    int seed = 1;
    srand(seed);
}
void moveMonster(){
    // CHASER MOVEMENT
    if (monsterdelay == 10){
        if (charLocation.Y < g_cChaserLoc.Y){
            g_cChaserLoc.Y -= 1;
            Beep(1440, 30);
        } // up
        if (charLocation.X < g_cChaserLoc.X){
            g_cChaserLoc.X -= 1;
            Beep(1440, 30);
        } // left
        if (charLocation.X > g_cChaserLoc.X){
            g_cChaserLoc.X += 1;
            Beep(1440, 30);
        } // right
        if (charLocation.Y > g_cChaserLoc.Y){
            g_cChaserLoc.Y += 1;
            Beep(1440, 30);
        } // down
        monsterdelay = 0;
    }
    collision();
}
void moveMonster1(){
	// CHASER MOVEMENT
	if (monster1delay == 10){
		if (charLocation.Y < g_cChaser1Loc.Y){
			g_cChaser1Loc.Y -= 1;
			Beep(1440, 30);
		} // up
		if (charLocation.X < g_cChaser1Loc.X){
			g_cChaser1Loc.X -= 1;
			Beep(1440, 30);
		} // left
		if (charLocation.X > g_cChaser1Loc.X){
			g_cChaser1Loc.X += 1;
			Beep(1440, 30);
		} // right
		if (charLocation.Y > g_cChaser1Loc.Y){
			g_cChaser1Loc.Y += 1;
			Beep(1440, 30);
		} // down
		monster1delay = 0;
	}
	collision1();
}
// check if monster gets shot
void projKill(){
	if (g_cChaserLoc.X == g_cProjectile.X && g_cChaserLoc.Y == g_cProjectile.Y){
		monsterDeath();
	}
}
void projKill1(){
	if (g_cChaser1Loc.X == g_cProjectile.X && g_cChaser1Loc.Y == g_cProjectile.Y){
		monster1Death();
	}
}
void monsterDeath(){
	int spawnLocation = rand() % 3;
	g_cChaserLoc.X = 26;
	if (spawnLocation == 0){
		g_cChaserLoc.Y = 2;
	}
	else if (spawnLocation == 1){
		g_cChaserLoc.Y = 14;
	}
	else{
		g_cChaserLoc.Y = 24;
	}
}
void monster1Death(){
	int spawnLocation = rand() % 3;
	g_cChaser1Loc.X = 26;
	if (spawnLocation == 0){
		g_cChaser1Loc.Y = 14;
	}
	else if (spawnLocation == 1){
		g_cChaser1Loc.Y = 24;
	}
	else{
		g_cChaser1Loc.Y = 2;
	}
}
void collision1(){
	if (charLocation.X - 1 == g_cChaser1Loc.X && charLocation.Y + 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Top left
	else if (charLocation.X == g_cChaser1Loc.X && charLocation.Y + 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Top Middle
	else if (charLocation.X + 1 == g_cChaser1Loc.X && charLocation.Y + 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Top Right
	else if (charLocation.X - 1 == g_cChaser1Loc.X && charLocation.Y == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Left
	else if (charLocation.X == g_cChaser1Loc.X  && charLocation.Y == g_cChaser1Loc.Y){
		monster1Death();
	} // Middle
	else if (charLocation.X + 1 == g_cChaser1Loc.X && charLocation.Y == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Right

	else if (charLocation.X - 1 == g_cChaser1Loc.X && charLocation.Y - 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Btm Left
	else if (charLocation.X == g_cChaser1Loc.X && charLocation.Y - 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Btm Middle
	else if (charLocation.X + 1 == g_cChaser1Loc.X && charLocation.Y - 1 == g_cChaser1Loc.Y){
		monster1Death();
		health -= 1;
	} // Btm Right 
}
void refill(){
	if (printMap[charLocation.Y][charLocation.X] == 3){
		printMap[charLocation.Y][charLocation.X] = 0;
		ammo += 10;
	}
}

void splash(){
	std::string gamesplash;
	COORD c = console.getConsoleSize();
	c.Y /= 5;
	c.X /= 9;
	std::ifstream myfile;
	FILE * pFile;
	myfile.open("Spooky.txt");
	for (int i = 0; myfile.good(); i++){
		std::getline(myfile, gamesplash);
		console.writeToBuffer(c, gamesplash, 0x0E);
		c.Y += 1;
	}
}
