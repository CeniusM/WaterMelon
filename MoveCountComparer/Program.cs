
using static System.Console;
using static System.ConsoleColor;
using System.Collections.Generic;
using System.Linq;

WriteLine("Input");

//WriteLine("string 1");
//List<string> str1 = ReadLine()!.Split("\n").ToList();
//WriteLine("string 2");
//List<string> str2 = ReadLine()!.Split("\n").ToList();

List<string> str1 =
    "f3f2: 20\r\nd6d5: 22\r\nc7c6: 23\r\nc7c5: 7\r\nf3e2: 18\r\nf3g2: 18\r\nh5b5: 5\r\nh5c5: 20\r\nh5d5: 22\r\nh5e5: 22\r\nh5f5: 22\r\nh5g5: 22\r\nh5h6: 22\r\nh5h7: 22\r\nh5h8: 22\r\nh4g3: 20\r\nh4g5: 22\r\nh4g4: 21"
    .Split("\n").ToList();
List<string> str2 =
    "h4g3: 20\r\nh4g4: 21\r\nh4g5: 22\r\nc7c6: 23\r\nc7c5: 6\r\nd6d5: 22\r\nf3e2: 18\r\nf3g2: 18\r\nf3f2: 20\r\nh5h6: 22\r\nh5h7: 22\r\nh5h8: 22\r\nh5g5: 22\r\nh5f5: 22\r\nh5e5: 22\r\nh5d5: 22\r\nh5c5: 20\r\nh5b5: 5"
    .Split("\n").ToList();


int str1Count = str1.Count;
int str2Count = str2.Count;
List<(string Move, int Count)> moves1 = new();
List<(string Move, int Count)> moves2 = new();

for (int i = 0; i < str1Count; i++)
    moves1.Add((str1[i].Split(": ")[0], int.Parse(str1[i].Split(": ")[1])));
for (int i = 0; i < str2Count; i++)
    moves2.Add((str2[i].Split(": ")[0], int.Parse(str2[i].Split(": ")[1])));

WriteLine("Compare");

if (str1Count != str2Count)
{
    List<string> moves1Names = new List<string>();
    List<string> moves2Names = new List<string>();
    for (int i = 0; i < str1Count; i++)
        moves1Names.Add(moves1[i].Move);
    for (int i = 0; i < str2Count; i++)
        moves2Names.Add(moves2[i].Move);

    ForegroundColor = Red;
    WriteLine("Move counts dont match");
    WriteLine("nr 1: " + str1Count);
    WriteLine("nr 2: " + str2Count);

    if (str1Count > str2Count)
    {
        for (int i = 0; i < str1Count; i++)
        {
            if (!moves2Names.Contains(moves1Names[i]))
            {
                WriteLine("nr 2 missing: " + moves1Names[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < str2Count; i++)
        {
            if (!moves1Names.Contains(moves2Names[i]))
            {
                WriteLine("nr 1 missing: " + moves2Names[i]);
            }
        }
    }

    ResetColor();
    goto Start;
}

bool Failed = false;
for (int i = 0; i < str1Count; i++)
{
    int count = moves1[i].Count;
    string move = moves1[i].Move;

    for (int j = 0; j < str2Count; j++)
    {
        if (move != moves2[j].Move)
            continue;
        if (count != moves2[j].Count)
        {
            ForegroundColor = Red;
            Failed = true;
            WriteLine("Move failed: " + move + ". first: " + count + ". second: " + moves2[j].Count);
        }
    }
}

if (Failed)
{
    ResetColor();
    goto Start;
}
else
{
    ForegroundColor = Green;
    WriteLine("Succes");
    ResetColor();
    goto Start;
}

// Originaly at top
Start:
Console.WriteLine();
Console.ReadLine();