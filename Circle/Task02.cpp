#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 520

// Global variables
bool gameIsRunning = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int redColorCode = 255;
Uint32 startTime;
Uint32 currentTime;
int initialRadius = 50;  // Initial radius of the circle
int currentRadius = initialRadius;  // Current radius of the circle

// Function to get circle attributes
void getCircleAttr(int* x, int* y, int* radius) {
    // Define the attributes of the circle
    *x = SCREEN_WIDTH / 2;  // X-coordinate of the center
    *y = SCREEN_HEIGHT / 2; // Y-coordinate of the center
    *radius = currentRadius;  // Use the current radius
}

// Function to draw a circle
void drawCircle(SDL_Renderer *renderer, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    filledCircleColor(renderer, x, y, radius, r, g, b, a);
}

bool initializeWindow(void) {
    // Initialize SDL with video support
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Create an SDL window
    window = SDL_CreateWindow("SDL Introduction", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Create an SDL renderer for rendering graphics in the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    return true;
}

void process_input(void) {
    // Poll SDL events (e.g., window close)
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            gameIsRunning = false; // Exit the game loop
            break;

        default:
            break;
        }
    }
}

void drawRectangle(void) {
    SDL_Rect rectObj;
    // Calculate the position of the rectangle in the center of the window
    int rectWidth = 100;
    int rectHeight = 80;
    rectObj.x = (SCREEN_WIDTH - rectWidth) / 2;
    rectObj.y = (SCREEN_HEIGHT - rectHeight) / 2;
    rectObj.w = rectWidth;
    rectObj.h = rectHeight;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectObj);
}

void draw(void) {
    // Set the render draw color (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, redColorCode, 20, 205, 255);

    // Clear the renderer with the specified draw color
    SDL_RenderClear(renderer);

    // Get circle attributes
    int circleX, circleY, circleRadius;
    getCircleAttr(&circleX, &circleY, &circleRadius);

    // Draw the circle
    drawCircle(renderer, circleX, circleY, circleRadius, 255, 0, 0, 255); // Red circle

    // Increase the radius over time
    currentRadius++;
    if (circleX - currentRadius <= 0 || circleX + currentRadius >= SCREEN_WIDTH ||
        circleY - currentRadius <= 0 || circleY + currentRadius >= SCREEN_HEIGHT) {
        // Reset the radius when it collides with the window's boundaries
        currentRadius = initialRadius;
    }

    // Present the renderer (draw the frame to the window)
    SDL_RenderPresent(renderer);
}

void destroyWindow(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char **argv) {
    // The game loop control variable
    gameIsRunning = initializeWindow();
    startTime = SDL_GetTicks();

    // Game loop: keep the application running until 'running' is set to false
    while (gameIsRunning) {
        // Continuously polls for SDL events
        process_input();

        // Draw the rendered window
        draw();
    }

    // Clean up and exit the application
    destroyWindow();

    return 0;
}
