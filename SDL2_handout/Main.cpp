#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

#include "../SDL2_Handout/SDL/include/SDL.h"
#pragma comment( lib, "../SDL2_Handout/SDL/libx86/SDL2.lib" )
#pragma comment( lib, "../SDL2_Handout/SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


int main(int argc, char* argv[])
{
	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = nullptr;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
			case MAIN_CREATION:
			{
				LOG("Application Creation --------------");
				App = new Application();
				state = MAIN_START;
			}	break;

			case MAIN_START:
			{
				LOG("Application Init --------------");
				if(App->Init() == false)
				{
					LOG("Application Init exits with error -----");
					state = MAIN_EXIT;
				}
				else
				{
					state = MAIN_UPDATE;
					LOG("Application Update --------------");
				}

			}	break;

			case MAIN_UPDATE:
			{
				int update_return = App->Update();

				if (update_return == UPDATE_ERROR)
				{
					LOG("Application Update exits with error -----");
					state = MAIN_EXIT;
				} else if (update_return == UPDATE_STOP)
					state = MAIN_FINISH;
			}
				break;

			case MAIN_FINISH:
			{
				LOG("Application CleanUp --------------");
				if(App->CleanUp() == false)
				{
					LOG("Application CleanUp exits with error -----");
				}
				else
					main_return = EXIT_SUCCESS;

				state = MAIN_EXIT;

			} break;

		}
	}

	delete App;
	LOG("Bye :)\n");
	return main_return;
}