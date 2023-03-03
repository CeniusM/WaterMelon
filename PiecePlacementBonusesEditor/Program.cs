using SDL2;

// SDL

bool PrintValueChange = true;


int[] values = new int[64];
int min = -100;
int max = 100;
int increment = 5;

void ClampValues()
{
    for (int i = 0; i < 64; i++)
        values[i] = Math.Clamp(values[i], min, max);
}

int ClampValue(int value)
{
    return Math.Clamp(value, min, max);
}

void PrintBoard()
{
    string str = "";
    for (int i = 0; i < 64; i++)
    {
        str += values[i];
        if (i != 63)
            str += ",";
    }
    Console.WriteLine(str);
}

//void PrintBoard()
//{
//    string str = "constexpr EvaluationF PiecePlacementBonuses[]\n";
//    str += "{";
//    for (int i = 0; i < 64; i++)
//    {
//        str += values[i];
//        if (i != 63)
//            str += ",";
//    }
//    str += "\n";
//    str += "};";
//    Console.WriteLine(str);
//}

bool Running = true;

Thread thread = new Thread(() =>
{
    Console.WriteLine("GUI instructs");
    Console.WriteLine("You can left click a square to increase the value of that square by the Inc");
    Console.WriteLine("Or press right click to decrease the squares value");
    Console.WriteLine("Blue is positiv, red is negativ");
    Console.WriteLine("You can also press spacebar while hovering over a square to reset it");
    Console.WriteLine("And press \"v\" to print out the square value");
    Console.WriteLine("And press \"r\" to reset the board");
    Console.WriteLine();
    Console.WriteLine("This is the command interface");
    Console.WriteLine("Use Max, Min and Inc to change the editor");
    Console.WriteLine("\"exit\" or \"quit\" to quit the aplication");
    Console.WriteLine("\"Max {value}\" Used to change the max value");
    Console.WriteLine("\"Min {value}\" Used to change the min value");
    Console.WriteLine("\"Inc {value}\" Used to change the increment of the clicks");
    Console.WriteLine("\"Stat\" Used to print the current Max, Min and Inc parameters");
    Console.WriteLine("\"Print\" Used to print the current board values in a c++ constexpr format");
    Console.WriteLine();
    Console.WriteLine("Note: 100 is around a pawns material value");

    while (Running)
    {
        string input = Console.ReadLine()!.ToLower();
        if (!Running)
            break;
        if (input == "exit" || input == "quit")
        {
            Running = false;
            break;
        }

        if (input == "stat")
        {
            Console.WriteLine("Max: " + max);
            Console.WriteLine("Min: " + min);
            Console.WriteLine("Inc: " + increment);
            continue;
        }

        if (input == "print")
        {
            PrintBoard();
            continue;
        }

        if (input.Length < 4 || input[3] != ' ')
        {
            Console.WriteLine("Invalid input");
            continue;
        }

        string keyword = new string(input.Take(3).ToArray());
        string strValue = input.Remove(0, 4);
        int value = 0;

        if (int.TryParse(strValue, out int val))
        {
            value = val;
        }
        else
        {
            Console.WriteLine("Invalid input");
            continue;
        }

        if (keyword == "max")
        {
            if (value < 1)
            {
                Console.WriteLine("Max can not be below 1");
                continue;
            }
            max = value;
            Console.WriteLine("Max is now and all values will be clamped: " + max);
            ClampValues();
        }
        else if (keyword == "min")
        {
            if (value > -1)
            {
                Console.WriteLine("Min can not be above -1");
                continue;
            }
            min = value;
            Console.WriteLine("Min is now and all values will be clamped: " + min);
            ClampValues();
        }
        else if (keyword == "inc")
        {
            if (value < 1)
            {
                Console.WriteLine("Inc can not be below 1");
                continue;
            }
            if (value > max)
            {
                Console.WriteLine("Inc can not be above or equal Max");
                continue;
            }
            increment = value;
            Console.WriteLine("Inc is now: " + increment);
        }
        else
        {
            Console.WriteLine("Invalid input");
            continue;
        }
    }
});
thread.Start();


// Now the SDL part
SDL.SDL_Init(SDL.SDL_INIT_VIDEO);
IntPtr window = SDL.SDL_CreateWindow("My SDL Window",
                                             SDL.SDL_WINDOWPOS_UNDEFINED,
                                             SDL.SDL_WINDOWPOS_UNDEFINED,
                                             800,
                                             800,
                                             SDL.SDL_WindowFlags.SDL_WINDOW_SHOWN);
IntPtr renderer = SDL.SDL_CreateRenderer(window, 0, 0);

SDL.SDL_Event e;
int mouse_x = 0;
int mouse_y = 0;

void IncreaseValue()
{
    int x = mouse_x / 100;
    int y = mouse_y / 100;
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        values[x + y * 8] = ClampValue(values[x + y * 8] + increment);
        if (PrintValueChange)
            Console.WriteLine(values[x + y * 8]);
    }
}
void DecreaseValue()
{
    int x = mouse_x / 100;
    int y = mouse_y / 100;
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        values[x + y * 8] = ClampValue(values[x + y * 8] - increment);
        if (PrintValueChange)
            Console.WriteLine(values[x + y * 8]);
    }
}
void SetValueToZero()
{
    int x = mouse_x / 100;
    int y = mouse_y / 100;
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        values[x + y * 8] = 0;
    }
}
void PrintValue()
{
    int x = mouse_x / 100;
    int y = mouse_y / 100;
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        Console.WriteLine($"Value: {values[x + y * 8]} at x: {x}, y: {y}");
    }
}
while (Running)
{
    while (SDL.SDL_PollEvent(out e) != 0)
    {
        if (e.type == SDL.SDL_EventType.SDL_QUIT)
        {
            Running = false;
        }

        else if (e.type == SDL.SDL_EventType.SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL.SDL_BUTTON_LEFT)
            {
                IncreaseValue();
            }
            else if (e.button.button == SDL.SDL_BUTTON_RIGHT)
            {
                DecreaseValue();
            }
        }

        else if (e.type == SDL.SDL_EventType.SDL_MOUSEWHEEL)
        {
            int amount = e.wheel.y;
            //Console.WriteLine("Amount: " + amount);
            //Console.WriteLine("Dir: " + dir);

            if (amount < 0)
                while (amount++ < 0)
                    DecreaseValue();
            else
                while (amount-- > 0)
                    IncreaseValue();
        }

        else if (e.type == SDL.SDL_EventType.SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDL.SDL_Keycode.SDLK_SPACE)
            {
                SetValueToZero();
            }
            else if (e.key.keysym.sym == SDL.SDL_Keycode.SDLK_v)
            {
                PrintValue();
            }
            else if (e.key.keysym.sym == SDL.SDL_Keycode.SDLK_r)
            {
                values = new int[64];
            }
        }

        else if (e.type == SDL.SDL_EventType.SDL_MOUSEMOTION)
        {
            mouse_x = e.motion.x;
            mouse_y = e.motion.y;
        }
    }

    // Render
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // Calculate the position of the square
            int x = col * 100;
            int y = row * 100;

            int value = values[col + row * 8];

            int blue = Math.Max((int)((double)value / (double)max * 255), 0);
            int red = Math.Max((int)((double)value / (double)min * 255), 0);

            // Draw the square
            SDL.SDL_SetRenderDrawColor(renderer, (byte)red, 0, (byte)blue, 255);
            SDL.SDL_Rect rect = new SDL.SDL_Rect() { x = x, y = y, w = 100, h = 100 };
            SDL.SDL_RenderFillRect(renderer, ref rect);
        }
    }

    // Draw lines
    for (int row = 0; row < 7; row++)
    {
        int y = row * 100 + 100;

        // Draw the square
        SDL.SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL.SDL_RenderDrawLine(renderer, 0, y, 800, y);
    }
    for (int col = 0; col < 7; col++)
    {
        int x = col * 100 + 100;

        // Draw the square
        SDL.SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL.SDL_RenderDrawLine(renderer, x, 0, x, 800);
    }

    SDL.SDL_RenderPresent(renderer);

    Thread.Sleep(16);
}

SDL.SDL_DestroyWindow(window);
SDL.SDL_DestroyRenderer(renderer);
SDL.SDL_Quit();