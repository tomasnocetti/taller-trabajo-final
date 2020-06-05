#include "CApp.h"

CApp::CApp() {
  Running = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //return false;
  }
  window = SDL_CreateWindow(
    GAME_TITLE,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP
  );

  if( window == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    //return false;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if( renderer == NULL ) {
    printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
    //return false;
  }

	//Initialize renderer color
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  //Initialize PNG loading
  int imgFlags = IMG_INIT_JPG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    //return false;
  }
}

void CApp::OnExecute() {
  OnInit();

  SDL_Event Event;
  while(Running) {
      while(SDL_PollEvent(&Event)) {
          OnEvent(Event);
      }

      OnLoop();
      OnRender();
  }

  OnCleanup();
}

void CApp::OnEvent(const SDL_Event& Event) {
  if(Event.type == SDL_QUIT) {
    Running = false;
  }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
  SDL_RenderPresent(renderer);
}

void CApp::OnInit() {
  InitMainIterface();
}

void CApp::InitMainIterface() {
  LTexture main_conteiner(renderer);

  main_conteiner.loadFromFile(MAIN_SCREEN_PATH);
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  std::cout << "w: " << DM.w << " h: " << DM.h << std::endl;
  SDL_Rect renderQuad = { 0, 0, DM.w, DM.h };
  main_conteiner.render(0, 0, &renderQuad);
}

void CApp::OnCleanup() {
  SDL_DestroyWindow( window );
  SDL_Quit();
}