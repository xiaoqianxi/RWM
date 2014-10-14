#include <Box2D/Box2D.h>
#include <stdio.h>
#include <SDL.h>


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The window renderer
SDL_Renderer* gRenderer = NULL;


b2Vec2 gravity(0.0f, 10.0f);
b2World world(gravity);


b2Body* body;
SDL_Rect pos = {100,100,0,0};
void createGroundBody(){
	

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 500.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//create polygon
	b2PolygonShape groundBox;
	groundBox.SetAsBox(200.0f, 10.0f);

	//creating the shape fixture
	groundBody->CreateFixture(&groundBox, 0.0f);
	//groundBody
}


void createDynamicBody(){
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 100.0f);
    body = world.CreateBody(&bodyDef);

	//create and attach a polygon shape using a fixture definition
	b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(50.0f, 50.0f);

	//Fixture definition
	b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

}

void simulateWorld(){
	float32 timeStep = 0.1f / 60.0f;

	int32 velocityIterations = 6;
    int32 positionIterations = 2;

	for (int32 i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

}

int main( int argc, char* args[] ){
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	SDL_Event event;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Surface* enemy, *temp;
	temp = SDL_LoadBMP( "enemy.bmp" );
	enemy = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		bool done = false;
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Get window surface
			    screenSurface = SDL_GetWindowSurface( window );

			}
			

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			createGroundBody();
			createDynamicBody();
			
			
			while(!done)
			{
				//Update the surface
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//Fill the surface
			    SDL_FillRect( screenSurface, NULL, 0xFFFFFF );

				simulateWorld();

				b2Vec2 position = body->GetPosition();
				SDL_Rect posImg = {position.x, position.y,0,0};
				
				SDL_BlitSurface( enemy, NULL, screenSurface, &posImg );			
                
				SDL_UpdateWindowSurface( window );

				while(SDL_PollEvent(&event))
				{
					if(event.type == SDL_QUIT)
					{
						done = true;
					}
				}
            }

			//SDL_Delay( 2000 );
		}
	}

	SDL_FreeSurface(enemy);
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}