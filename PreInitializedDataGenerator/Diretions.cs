

namespace PreInitializedDataGenerator;

/// <summary>
/// Copied from engine
/// </summary>
internal class Diretions
{
    public enum DirectionIndexs
    {
        NorthI = 0,
        EastI = 1,
        SouthI = 2,
        WestI = 3,
        NorthEastI = 4,
        SouthEastI = 5,
        SouthWestI = 6,
        NorthWestI = 7,
    }

    public enum DirectionOffsets
    {
        NorthO = -8,
        EastO = 1,
        SouthO = 8,
        WestO = -1,
        NorthEastO = -7,
        SouthEastO = 9,
        SouthWestO = 7,
        NorthWestO = -9,
    }

    public static int[] OffsetsIndexed =
    {
        (int)DirectionOffsets.NorthO,
        (int)DirectionOffsets.EastO,
        (int)DirectionOffsets.SouthO,
        (int)DirectionOffsets.WestO,
        (int)DirectionOffsets.NorthEastO,
        (int)DirectionOffsets.SouthEastO,
        (int)DirectionOffsets.SouthWestO,
        (int)DirectionOffsets.NorthWestO,
    };

    public static int[] LineDiffs =
    {
        -1,
        0,
        1,
        0,
        -1,
        1,
        1,
        -1,
    };
}