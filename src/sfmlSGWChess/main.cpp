#include "pch.h"
#include "main.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void ChangePlayerTurn(COLOR* turn) {
	if (*turn == WHITE) *turn = BLACK;
	else *turn = WHITE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = nullptr;
	wcex.lpszClassName  = L"WinAppClass";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if ( RegisterClassExW(&wcex)==0 )
		return 0;

	HWND hWnd = CreateWindowW(L"WinAppClass", L"Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if ( hWnd==NULL )
		return 0;

	sf::RenderWindow test(hWnd);
	test.create(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Board board;
	board.Init();

	SFMLHandler handler(&test, &board);
	handler.Init();

	bool runing = true;
	COLOR playerTurn = WHITE;
	Cell* currentTarget = nullptr;

	MSG msg;
	while ( GetMessage(&msg, nullptr, 0, 0) )
	{
		sf::Event evnt;
		while (test.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				test.close();
				break;
			case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i pos = sf::Mouse::getPosition(test);
				int x = pos.x / 40;
				int y = pos.y / 40;
				Cell* cell = board.GetCellAt(x, y);

				if (cell == nullptr) break;

				if (cell->playable) {
					board.MoveFromTo(currentTarget, cell);
					board.ResetPlayableCells();
					currentTarget = nullptr;
					ChangePlayerTurn(&playerTurn);
				}
				else if (cell->occupedBy != nullptr) {
					board.ResetPlayableCells();
					if (cell->occupedBy->_color == playerTurn) {
						currentTarget = cell;
						cell->occupedBy->SetAccesibleCellsToPlayable(&board);
					}
				}
				break;
			}
			default:
				break;
			}
		}
		handler.Update();
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			int notif = HIWORD(wParam);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}
	return 0;
}
