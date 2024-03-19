#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "Sphere.h"
#include "Vector3D.h"
#include "ViewPort.h"
#include "Ray.h"
#include "Rgb.h"
#include "Triangle.h"
#include "Object.h"
#include "Scene.h"
#include "ViewDriver.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

void set_pixel(SDL_Surface* surface, int x, int y, Rgb& color)
{
	if (x >= 0 && x < surface->w && y >= 0 && y < surface->h) {
		Uint32* pixels = (Uint32*)surface->pixels;
		Uint32 pixelColor = SDL_MapRGB(
			surface->format,
			color.getRed(),
			color.getGreen(),
			color.getBlue()
		);

		pixels[(y * surface->w) + x] = pixelColor;
	}
}

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			Uint32 staticColor = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
			Scene* scene = new Scene();

			//Object* object = new Object();
			//object->addSurface(new Sphere(Vector3D(0, 0, 5.15), 0.3));
			//object->setColour(Rgb(255, 0, 0));

			//Object* triangle = new Object();
			//triangle->setColour(Rgb(0, 255, 64));
			//triangle->addSurface(new Triangle(
			//	Vector3D(2.47, -0.87, 7.47),
			//	Vector3D(-0.47, 2.13, 4.47),
			//	Vector3D(-0.47, -0.87, 4.47)
			//));

			//scene->addObject(object);
			//scene->addObject(triangle);
			//scene->addLight(new Light(Vector3D(-4, 0, 5)));
			
			//

			// Create a sphere object and set its colour to red
			Object* sphere = new Object();
			sphere->addSurface(new Sphere(Vector3D(-0.2, -0.3, 2), 0.3)); // Position the sphere above the origin in the positive Z direction
			sphere->setColour(Rgb(255, 0, 0)); // Red color

			// Create a triangle object and set its colour to green
			Object* triangle = new Object();
			triangle->setColour(Rgb(0, 255, 64)); // Green color
			// Define the triangle vertices to form a base for the sphere
			triangle->addSurface(new Triangle(
				Vector3D(1, -1, 1.5), // Vertex 1
				Vector3D(-1, -1, 1.5), // Vertex 2
				Vector3D(0, 1, 1.5) // Vertex 3, ensuring all vertices are in the positive Z space
			));

			scene->addObject(sphere);
			scene->addObject(triangle);

			scene->addLight(new Light(Vector3D(-6, 0, 5))); // Position the light source to illuminate the objects

			ViewPort viewPort = ViewPort(SCREEN_WIDTH, SCREEN_HEIGHT);

			ViewDriver viewDriver = ViewDriver(scene, viewPort);
			vector<vector<Rgb>> rgbValues = viewDriver.processFrame();

			for (int y = 0; y < SCREEN_HEIGHT; ++y)
			{
				for (int x = 0; x < SCREEN_WIDTH; ++x)
				{
					set_pixel(screenSurface, x, y, rgbValues.at(y).at(x));
				}
			}

			SDL_UpdateWindowSurface(window);

			SDL_Event e;
			bool quit = false;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
