
#include "GameOfChess.h"

const char* AssetsPath = "Assets\\";

//SDL_Texture* playerTexture;
SDL_Rect srcR, destR;
SDLHelper sdlHelper;

void GameOfChess::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem has initilized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
			m_isRunning = true;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
	}
	else
		m_isRunning = false;


	//SDL_Surface* tmpSurface = IMG_Load("Assets/picture.png");
	//playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	//SDL_FreeSurface(tmpSurface);
	//playerTexture = sdlHelper.LoadImage("Assets/n.bmp", renderer);
	
	for (int i = 0; i < 24; i++)
		sprites[i] = nullptr;
	sprites[9] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wking.bmp", renderer); //9 WKing
	sprites[10] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wpawn.bmp", renderer); //10 WPawn
	sprites[11] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wknight.bmp", renderer); //11 WKnight
	sprites[13] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wbishop.bmp", renderer); //13 WBishop
	sprites[14] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wrook.bmp", renderer); //14 WRook
	sprites[15] = sdlHelper.LoadImage(std::string(AssetsPath) + "Wqueen.bmp", renderer); //15 WQueen
	sprites[17] = sdlHelper.LoadImage(std::string(AssetsPath) + "Bking.bmp", renderer); //17 BKing
	sprites[18] = sdlHelper.LoadImage(std::string(AssetsPath) + "Bpawn.bmp", renderer); //18 BPawn
	sprites[19] = sdlHelper.LoadImage(std::string(AssetsPath) + "Bknight.bmp", renderer); //19 BKnight
	sprites[21] = sdlHelper.LoadImage(std::string(AssetsPath) + "Bbishop.bmp", renderer); //21 BBishop
	sprites[22] = sdlHelper.LoadImage(std::string(AssetsPath) + "Brook.bmp", renderer); //22 BRook
	sprites[23] = sdlHelper.LoadImage(std::string(AssetsPath) + "Bqueen.bmp", renderer); //23 BQueen
}

void GameOfChess::HandleEvents()
{	
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		default:
			break;
		}



		/*




		if (mouse down)
			piecetype = board
			pieceindex = index
			mouseDown = true
		else if (motion)
		mouseXYPos = x and y
			mousedraging = false
			if piece != 0
				piecebeing draged = 0;
			else
				?piece being draged = 1;
		else if (mouseup)
			click(xy)

			ispeiecedrag = false
			mousedrag = false



		*/

		int x = event.button.x / 100;
		int y = event.button.y / 100;
		int clickedPos = x + (y * 8);

		// could be that the screem will be made wider or taller
		// so just for playing chess
		if (x < 0 || y < 0 || x > 8 || y > 8)
			return;

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			std::cout << "mouseDown" << std::endl;
			xMousePos = event.button.x;
			yMousePos = event.button.y;
			SomethingHappend = true;
			MouseDraging = true;
			m_PieceTypeBeingDraged = board.GetPos(clickedPos);
			m_piecePickedIndex = clickedPos;
			m_IsPieceBeingDraged = true;
			pieceHaveBeenPicked = true;
			if ((board.GetPos(x + (y * 8)) & 0b11000) != board.GetPlayerColour())
			{
				m_IsPieceBeingDraged = false;
				MouseDraging = 0;
				//pieceHaveBeenPicked = false;
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (m_IsPieceBeingDraged)
				SomethingHappend = true;
			xMousePos = event.motion.x;
			yMousePos = event.motion.y;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{

			//Move move();
			//board.MakeMove();

			SomethingHappend = true;
			m_IsPieceBeingDraged = false;
			MouseDraging = 0;
			//pieceHaveBeenPicked = false;

			if ((xMousePos / 100) + ((yMousePos / 100) * 8) == m_piecePickedIndex) // peice landed on same square
			{
				pieceHaveBeenPicked = true;
			}
		}
	}
}

void GameOfChess::Update()
{
	m_Count++;

	//std::cout << m_Count << std::endl
}

void GameOfChess::Render()
{
	SDL_RenderClear(renderer);

	RenderBackGround();

	if (pieceHaveBeenPicked)
		std::cout << "true" << std::endl;
	if (pieceHaveBeenPicked)
		RenderPossibleMoves();

	if (m_IsPieceBeingDraged)
		RenderAllPieces(m_piecePickedIndex);
	else
		RenderAllPieces();


	SDL_Rect r{ xMousePos - 50,yMousePos - 50,100,100 };
	if (MouseDraging)
		RenderPiece(&r, sprites[m_PieceTypeBeingDraged]);

	SDL_RenderPresent(renderer);
}

void GameOfChess::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// delete all textures
	for (int i = 0; i < 24; i++)
		if (sprites[i] != nullptr)
			SDL_DestroyTexture(sprites[i]);



	SDL_Quit;
	std::cout << "finished cleanup\n";
}

bool GameOfChess::Running() { return m_isRunning; }

void GameOfChess::RenderBackGround()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			SDL_Rect rect;
			rect.w = 100;
			rect.h = 100;
			rect.x = j * 100;
			rect.y = i * 100;

			if ((i + j) % 2 == 0) // light square
				SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
			else
				SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void GameOfChess::RenderPossibleMoves()
{
	Move* moves = board.GetMovePointer();
	int movesCount = board.GetMovesCount();
	for (int i = 0; i < movesCount; i++)
	{
		if (moves[i].StartSquare == m_piecePickedIndex)
		{
			SDL_Rect rect;
			rect.w = 100;
			rect.h = 100;
			rect.x = (moves[i].TargetSquare % 8) * 100;
			rect.y = (moves[i].TargetSquare >> 3) * 100;
			if (((moves[i].TargetSquare >> 3) + (moves[i].TargetSquare % 8)) % 2 == 0) // light square
				SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
			else
				SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void GameOfChess::RenderAllPieces(int PieceToLeaveOut)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int pos = (i*8)+j;
	
			if (board.GetPos(pos) == 0)
				continue;

			if (pos == PieceToLeaveOut) // instead of removing it, just put another tranparent layer on it, so its ghost like
				continue;
	
			SDL_Rect rect;
			rect.x = j * 100;
			rect.y = i * 100;
			rect.h = 100;
			rect.w = 100;
	
			RenderPiece(&rect, sprites[board.GetPos(pos)]);
		}
	}
}

void GameOfChess::RenderPiece(SDL_Rect* rect, SDL_Texture* sprite)
{
	SDL_RenderCopy(renderer, sprite, NULL, rect);
}

GameOfChess::GameOfChess()
{
}

GameOfChess::~GameOfChess()
{
}