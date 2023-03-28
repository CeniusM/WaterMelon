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

void PrintArrayBytes(string type, string name, byte[] values)
{
    StringBuilder output = new StringBuilder(values.Length * 10);
    output.Append(type + " " + name + "[]" + "\n");
    output.Append("{\n");
    for (int i = 0; i < values.Length; i++)
    {
        output.Append(values[i].ToString() + ',');
    }
    output.Remove(output.Length - 1, 1);
    output.Append("\n};");
    Console.WriteLine(output.ToString());
}

ulong ImprentBitOnBoard(ulong bitboard, int pos)
{
    uint newPos = (uint)pos;
    ulong posBitboard = (ulong)(0b1 << (int)newPos);
    return (bitboard | posBitboard);
}

ulong SetBit(ulong board, int x, int y)
{
    board |= (0b1UL << (x + y * 8));
    return board;
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

//Bishop
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(Diretions.OffsetsIndexed, Diretions.LineDiffs);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "BishopSquareToAllDir", combined);
//PrintArray("constexpr Bitboard", "BishopSquareToDir", diretions);
//return;

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
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { -7, -9 }, new int[] { -1, -1 }, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "BlackPawnSquareToAllDir", combined);
///*PrintArray("constexpr Bitboard", "BlackPawnSquareToDir", diretions);*/

// DotBiboards
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { 0 }, new int[] { 0 }, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//PrintArray("constexpr Bitboard", "DotBiboards", combined);
///*PrintArray("constexpr Bitboard", "DotBiboards", diretions);*/

// InverseDotBiboards
//var boards = SlidingBitmapGenerator.GetBoardsFromSquareInDirection(new int[] { 0 }, new int[] { 0 }, 1);
//Bitboard[] combined = boards.AllCombinned;
//Bitboard[] diretions = boards.Diretions;
//for (int i = 0; i < combined.Length; i++)
//    combined[i] ^= 0xffffffffffffffff;
//PrintArray("constexpr Bitboard", "InverseDotBiboards", combined);
///*PrintArray("constexpr Bitboard", "InverseDotBiboards", diretions);*/


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


//for (int i = 0; i < 64; i++)
//{
//    PrintBitboardColored(combined[i], i);
//    Console.WriteLine();
//}
//PrintArray("Bitboard", "QueenSlidingMovesFromSquareAllDir", combined);




//// -- Lengths to side of board
//int[,] LenghtToSide = new int[64, 8];
//for (int i = 0; i < 8; i++)
//{
//    for (int j = 0; j < 8; j++)
//    {
//        int North = j;
//        int East = 7 - i;
//        int South = 7 - j;
//        int West = i;
//        int NorthEast = North < East ? North : East;
//        int SouthEast = South < East ? South : East;
//        int SouthWest = South < West ? South : West;
//        int NorthWest = North < West ? North : West;

//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.NorthI] = North;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.EastI] = East;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.SouthI] = South;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.WestI] = West;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.NorthEastI] = NorthEast;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.SouthEastI] = SouthEast;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.SouthWestI] = SouthWest;
//        LenghtToSide[i + (j << 3), (int)Diretions.DirectionIndexs.NorthWestI] = NorthWest;
//    }
//}
//byte[] bytes = new byte[64 * 8];
//for (int i = 0; i < 64; i++)
//{
//    for (int j = 0; j < 8; j++)
//    {
//        bytes[i + (j << 6)] = (byte)LenghtToSide[i, j];
//    }
//}

//Console.WriteLine(LenghtToSide[1,5]);

//PrintArrayBytes("constexpr char", "DistanceToBoardInDirection", bytes);


// -- Direction index from square to square -- DIDENT WORK; ONLY MOVED ONE OUT 
//byte[] bytes = new byte[0b111111111111 + 1];
//for (int i = 0; i < 64; i++)
//{
//    for (int j = 0; j < 64; j++)
//    {
//        // Debuging
//        //if (i == 9 && j == 17)
//        //    Console.Write("");

//        // First find the direction from start square to end square
//        // If there is no direction, just make it invalid
//        int startRank = i >> 3;
//        int startCollum = i % 8;
//        int endRank = j >> 3;
//        int endCollum = j % 8;

//        Diretions.DirectionIndexs index = Diretions.DirectionIndexs.InvalidIndexI;

//        if (startRank == endRank)
//        {
//            if (startCollum > endCollum)
//                index = Diretions.DirectionIndexs.WestI;
//            else if (startCollum < endCollum)
//                index = Diretions.DirectionIndexs.EastI;
//            else
//                index = Diretions.DirectionIndexs.InvalidIndexI;
//        }
//        else if (startCollum == endCollum)
//        {
//            if (startRank > endRank)
//                index = Diretions.DirectionIndexs.NorthI;
//            else if (startRank < endRank)
//                index = Diretions.DirectionIndexs.SouthI;
//            else
//                index = Diretions.DirectionIndexs.InvalidIndexI;
//        }
//        else if (endRank - startRank == -1 && endCollum - startCollum == -1)
//        {
//            index = Diretions.DirectionIndexs.NorthWestI;
//        }
//        else if (endRank - startRank == -1 && endCollum - startCollum == 1)
//        {
//            index = Diretions.DirectionIndexs.NorthEastI;
//        }
//        else if (endRank - startRank == 1 && endCollum - startCollum == 1)
//        {
//            index = Diretions.DirectionIndexs.SouthEastI;
//        }
//        else if (endRank - startRank == 1 && endCollum - startCollum == -1)
//        {
//            index = Diretions.DirectionIndexs.SouthWestI;
//        }
//        else
//            index = Diretions.DirectionIndexs.InvalidIndexI;

//        bytes[i + (j << 6)] = (byte)index;
//    }
//}
//int GetSquare(int rank, int collum) => (rank << 3) + collum;
//byte GetIndex(int startSquare, int endSquare) => bytes[startSquare + (endSquare << 6)];
//string GetIndexName(byte index) => ((Diretions.DirectionIndexs)index).ToString();
////Console.WriteLine(GetIndexName(GetIndex(GetSquare(1, 1), GetSquare(1, 7))));

//PrintArrayBytes("constexpr char", "DirectionIndexFromSquareToSquare", bytes);



// -- Bitboard from square to square -- DIDENT WORK; ONLY MOVED ONE OUT 

//ulong[] bitboards = new ulong[0b111111111111 + 1];
//for (int i = 0; i < 64; i++)
//{
//    for (int j = 0; j < 64; j++)
//    {
//        int startRank = i >> 3;
//        int startCollum = i % 8;
//        int endRank = j >> 3;
//        int endCollum = j % 8;

//        if (startRank == 1 && startCollum == 1 && endRank == 4 && endCollum == 4)
//            Console.Write("");

//        Diretions.DirectionIndexs index = Diretions.DirectionIndexs.InvalidIndexI;

//        if (startRank == endRank)
//        {
//            if (startCollum > endCollum)
//                index = Diretions.DirectionIndexs.WestI;
//            else if (startCollum < endCollum)
//                index = Diretions.DirectionIndexs.EastI;
//            else
//                index = Diretions.DirectionIndexs.InvalidIndexI;
//        }
//        else if (startCollum == endCollum)
//        {
//            if (startRank > endRank)
//                index = Diretions.DirectionIndexs.NorthI;
//            else if (startRank < endRank)
//                index = Diretions.DirectionIndexs.SouthI;
//            else
//                index = Diretions.DirectionIndexs.InvalidIndexI;
//        }
//        else if (endRank - startRank == -1 && endCollum - startCollum == -1)
//        {
//            index = Diretions.DirectionIndexs.NorthWestI;
//        }
//        else if (endRank - startRank == -1 && endCollum - startCollum == 1)
//        {
//            index = Diretions.DirectionIndexs.NorthEastI;
//        }
//        else if (endRank - startRank == 1 && endCollum - startCollum == 1)
//        {
//            index = Diretions.DirectionIndexs.SouthEastI;
//        }
//        else if (endRank - startRank == 1 && endCollum - startCollum == -1)
//        {
//            index = Diretions.DirectionIndexs.SouthWestI;
//        }
//        else
//            index = Diretions.DirectionIndexs.InvalidIndexI;

//        if (index == Diretions.DirectionIndexs.InvalidIndexI)
//        {
//            bitboards[i + (j << 6)] = (ulong)index;
//            continue;
//        }


//        int start = i;
//        int end = j;
//        int offset = Diretions.OffsetsIndexed[(int)index];
//        ulong bitboard = ImprentBitOnBoard(0, start);
//        while (true)
//        {
//            start += offset;
//            bitboard = ImprentBitOnBoard(bitboard, start);
//            if (start == end)
//                break;
//        }

//        bitboards[i + (j << 6)] = bitboard;
//    }
//}
//int GetSquare(int rank, int collum) => (rank << 3) + collum;
//ulong GetIndex(int startSquare, int endSquare) => bitboards[startSquare + (endSquare << 6)];

//PrintBitboard(GetIndex(GetSquare(1, 1), GetSquare(5, 1)));
//PrintBitboard(GetIndex(GetSquare(1, 1), GetSquare(5, 5)));

//PrintArray("constexpr char", "BitboardFromSquareToSquare", bitboards);



// Create row and collum arrays
ulong[] rows = new ulong[8];
ulong[] collums = new ulong[8];
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        rows[i] = SetBit(rows[i], j, i);
        collums[i] = SetBit(collums[i], i, j);
    }
}

//PrintBitboardColored(collums[0]);
//PrintBitboardColored(collums[1]);
//PrintBitboardColored(collums[2]);
//PrintBitboardColored(collums[3]);
//PrintBitboardColored(collums[4]);
//PrintBitboardColored(collums[5]);
//PrintBitboardColored(collums[6]);
//PrintBitboardColored(collums[7]);

PrintArray("Bitboard", "RowBitboards", rows);
PrintArray("Bitboard", "CollumBitboards", collums);