using PreInitializedDataGenerator;
using System.Text;
using Bitboard = System.UInt64;

void PrintArray(string type, string name, ulong[] offsets)
{
    StringBuilder output = new StringBuilder(offsets.Length * 10);
    output.Append(type + " " + name + "[]" + "\n");
    output.Append("{\n");
    for (int i = 0; i < offsets.Length; i++)
    {
        output.Append(offsets[i].ToString() + ',');
    }
    output.Remove(output.Length - 1, 1);
    output.Append("\n};");
    Console.WriteLine(output.ToString());
}

// Would only work for 1d
//void PrintArrayAndMethod(string type, string name, ulong[] offsets)
//{
//    StringBuilder output = new StringBuilder(offsets.Length * 10);
//    output.Append("" +
//        "constexpr Bitboard Get" + name + "(Square square)\r\n" +
//        "{\r\n\t" +
//        "return " + name + "[square];\r\n" +
//        "}\r\n");

//    output.Append(type + " " + name + "[]" + "\n");
//    output.Append("{\n");
//    for (int i = 0; i < offsets.Length; i++)
//    {
//        output.Append(offsets[i].ToString() + ',');
//    }
//    output.Remove(output.Length - 1, 1);
//    output.Append("\n};");
//    Console.WriteLine(output.ToString());
//}

void PrintBitboard(Bitboard board)
{
    StringBuilder output = new StringBuilder(64);
    for (int i = 0; i < 64; i++)
    {
        output.Append((board >> i) & 0b1);
        if (i % 8 == 7)
            output.Append('\n');
    }
    Console.WriteLine(output.ToString());
}

void PrintBitboardColored(Bitboard board, int start = -1)
{
    for (int i = 0; i < 64; i++)
    {
        var val = (board >> i) & 0b1;
        if (i == start)
            Console.ForegroundColor = ConsoleColor.Blue;
        else if (val == 1)
            Console.ForegroundColor = ConsoleColor.Red;
        else
            Console.ForegroundColor = ConsoleColor.Gray;
        if (i % 8 == 7)
            Console.WriteLine(val);
        else
            Console.Write(val);
    }
    Console.ResetColor();
    Console.WriteLine();
}

//PrintArray("Bitboard", "ArrayOfSomeKind", new ulong[] { 1, 124, 125, 54 });
//PrintBitboard(0b111100001100110011001101);
//Console.ReadLine();


// Queen
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(Diretions.OffsetsIndexed, Diretions.LineDiffs);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "QueenSquareToAllDir", combined);
//PrintArray("constexpr Bitboard", "QueenSquareToDir", diretions);

// Rook
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(Diretions.OffsetsIndexed.Take(new Range(0, 4)).ToArray(), Diretions.LineDiffs.Take(new Range(0, 4)).ToArray());
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "RookSquareToAllDir", combined);
//PrintArray("constexpr Bitboard", "RookSquareToDir", diretions);

// Bishop
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(Diretions.OffsetsIndexed.Take(new Range(4, 8)).ToArray(), Diretions.LineDiffs.Take(new Range(4, 8)).ToArray());
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "BishopSquareToAllDir", combined);
//PrintArray("constexpr Bitboard", "BishopSquareToDir", diretions);

// King
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(Diretions.OffsetsIndexed, Diretions.LineDiffs, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "KingSquareToAllDir", combined);
///*PrintArray("constexpr Bitboard", "KingSquareToDir", diretions);*/

// Knight
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { -10, -17, -15, -6, 10, 17, 15, 6 }, new int[] { -1, -2, -2, -1, 1, 2, 2, 1 }, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "KnightSquareToAllDir", combined);
///*PrintArray("constexpr Bitboard", "KnightSquareToDir", diretions);*/

// WhitePawn
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { 7, 9 }, new int[] { 1, 1 }, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "WhitePawnSquareToAllDir", combined);
///*PrintArray("constexpr Bitboard", "WhitePawnSquareToDir", diretions);*/

// BlackPawn
var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { -7, -9 }, new int[] { -1, -1 }, 1);
Bitboard[] combined = boards.AllCombinned;
Bitboard[] diretions = boards.Diretions;
PrintArray("constexpr Bitboard", "BlackPawnSquareToAllDir", combined);
/*PrintArray("constexpr Bitboard", "BlackPawnSquareToDir", diretions);*/


// -- For debuging --
//PrintBitboardColored(diretions[36 | (0 << 6)], 36);
//PrintBitboardColored(diretions[36 | (1 << 6)], 36);
//PrintBitboardColored(diretions[36 | (2 << 6)], 36);
//PrintBitboardColored(diretions[36 | (3 << 6)], 36);
//PrintBitboardColored(diretions[36 | (4 << 6)], 36);
//PrintBitboardColored(diretions[36 | (5 << 6)], 36);
//PrintBitboardColored(diretions[36 | (6 << 6)], 36);
//PrintBitboardColored(diretions[36 | (7 << 6)], 36);

//PrintBitboardColored(combined[36], 36);


for (int i = 0; i < 64; i++)
{
    PrintBitboardColored(combined[i], i);
    Console.WriteLine();
}
//PrintArray("Bitboard", "QueenSlidingMovesFromSquareAllDir", combined);