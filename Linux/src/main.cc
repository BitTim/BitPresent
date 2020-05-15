#include <iostream>
#include <SDL2/SDL_image.h>

#include "lib/globals.hh"
#include "lib/presentCreator.hh"
#include "lib/gui.hh"

//Initialize all global variables
std::string Global::_VERSIONSTRING = "BitPresent v1.2.0";

int Global::_WIDTH = 1920;
int Global::_HEIGHT = 1080;
int Global::_BORDERS = 20;
int Global::_INDENT = 40;

Presentation* Global::_PRESENT = nullptr;
int Global::_CSLIDE = -1;
int Global::_CPOINT = -1;

std::map<std::string, TTF_Font*> Global::_FONT;
std::map<std::string, TTF_Font*> Global::_DEFAULTFONT;
SDL_Color* Global::_TEXTCOLOR = nullptr;
SDL_Color* Global::_DEFAULTTEXTCOLOR = nullptr;
std::string Global::_BACKGROUND = "";
std::string Global::_DEFAULTBACKGROUND = "";

bool Global::useGUI = false;

int main(int argc, char* argv[])
{
	std::string inpath = "";
	std::string outpath = "";

	//Check Argument length
	if (argc > 3)
	{
		printf("[ERROR]: Too many arguments\n");
		printf("[USAGE]: bitPresent <input_path> [<output_path>]\n");
		return -1;
	}

	if (argc < 2) Global::useGUI = true;
	else
	{
		inpath = argv[1];
		if (argc == 3) outpath = argv[2];
		else outpath = "presentation.pdf";
	}

	//Initialize SDL for future Ops
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP);
	TTF_Init();

	//Load default font
	Global::_DEFAULTFONT = { {"title", TTF_OpenFont("dat/defaultFont.ttf", 68)}, {"subtitle", TTF_OpenFont("dat/defaultFont.ttf", 46)}, {"normal", TTF_OpenFont("dat/defaultFont.ttf", 34)}, {"footer", TTF_OpenFont("dat/defaultFont.ttf", 12)} };
	if (Global::_DEFAULTFONT["title"] == NULL || Global::_DEFAULTFONT["subtitle"] == NULL || Global::_DEFAULTFONT["normal"] == NULL)
	{
		printf("[ERROR]: Loading font: %s\n", TTF_GetError());
		return -1;
	}
	Global::_FONT = Global::_DEFAULTFONT;

	//Crate default Textcolor
	Global::_DEFAULTTEXTCOLOR = new SDL_Color{ 33, 33, 33 };
	Global::_TEXTCOLOR = Global::_DEFAULTTEXTCOLOR;

	//Create default Background
	Global::_DEFAULTBACKGROUND = "none";
	Global::_BACKGROUND = Global::_DEFAULTBACKGROUND;

	//Create Presentation
	//if(Global::useGUI) gtkInit(&argc, &argv);
	//else if(createPresent(inpath, outpath) == -1) return -1;

	//Clear Fonts
	TTF_CloseFont(Global::_FONT["title"]);
	TTF_CloseFont(Global::_FONT["subtitle"]);
	TTF_CloseFont(Global::_FONT["normal"]);

	//Exit SDL
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
