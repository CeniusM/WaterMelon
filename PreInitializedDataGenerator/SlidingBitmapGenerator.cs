using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Bitboard = System.UInt64;

namespace PreInitializedDataGenerator;

/// <summary>
/// NOTE, For cache coherence, we put the diretions next to each other, becous if you have the square pos as the small bits, and the diretions as the large bits.
/// You have to jump alot to look at all the queen moves for example, 8 times 63 * 8 byte jumps, i dont acually know if that is significant but ow well.
/// It can atlist be alot more significant with larger arrays of other types
/// </summary>
internal class SlidingBitmapGenerator
{
    private static bool PosInBounds(int pos)
    {
        return (pos & 0xFFC0) == 0;
    }

    private static bool LineDiffMatch(int start, int end, int lineDiff)
    {
        return (end >> 3) - (start >> 3) == lineDiff;
    }

    private static Bitboard SetBitOnBoard(int pos, Bitboard board)
    {
        return (board | (0b1UL << pos));
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns>an array of 64 | (directionOffsets.Length << 6 && another array that combines all the diretions</returns>
    public static (Bitboard[] Diretions, Bitboard[] AllCombinned) GetBoardsFromSquareInDirection(int[] directionOffsets, int[] lineOffsets, int maxSteps = 1000)
    {
        if (directionOffsets.Length != lineOffsets.Length)
            throw new ArgumentException("Both arrays need to be same length");

        int diretionCount = directionOffsets.Length;
        Bitboard[] bitboards = new Bitboard[64 | (diretionCount << 6)];
        Bitboard[] combinedBitboards = new Bitboard[64];

        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < directionOffsets.Length; j++)
            {
                int pos = i;
                int offSet = directionOffsets[j];
                int lineOffSet = lineOffsets[j];
                int stepsToGo = maxSteps;
                while (LineDiffMatch(pos, pos + offSet, lineOffSet) && PosInBounds(pos + offSet) && stepsToGo > 0)
                {
                    stepsToGo--;
                    pos += offSet;
                    bitboards[i | (j << 6)] |= SetBitOnBoard(pos, 0UL);
                }
            }
        }

        for (int i = 0; i < 64; i++)
            for (int j = 0; j < diretionCount; j++)
                combinedBitboards[i] |= bitboards[i | (j << 6)];

        return (bitboards, combinedBitboards);
    }




    /// <summary>
    /// 
    /// </summary>
    /// <returns>Bitboard array length 4095</returns>
    public static Bitboard[] GetBoardsFromSquareToSquare(bool Diagonals, bool Paralels)
    {
        throw new NotImplementedException();
        // 4095
        Bitboard[] bitboards = new Bitboard[63 | (63 << 6)];

        for (int start = 0; start < 64; start++)
        {
            for (int end = 0; end < 64; end++)
            {
                int index = start | (end << 6);

                // Find offset
                int offset = int.MinValue;
                if (Paralels)
                {
                    if (start >> 3 == end >> 3) // on same rank
                    {
                        if (start < end)
                            offset = 1;
                        else
                            offset = -1;
                    }
                    else if (start % 8 == end % 8) // on same collum
                    {
                        if (start < end)
                            offset = 8;
                        else
                            offset = -8;
                    }
                }

                if (Diagonals)
                {

                }

                if (offset == int.MinValue)
                    break;





            }
        }
        return bitboards;
    }
}


/*
 * 
 * 
 * 
 * 
 * 
 */