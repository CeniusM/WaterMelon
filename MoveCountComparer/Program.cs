
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
    "b4b3: 49\r\ng6g5: 49\r\nc7c6: 51\r\nd7d6: 49\r\nc7c5: 51\r\nh3g2: 48\r\nb4a3: 51\r\ne6d5: 50\r\nb4c3: 48\r\nb6a4: 49\r\nb6c4: 48\r\nb6d5: 50\r\nb6c8: 50\r\nf6e4: 53\r\nf6g4: 49\r\nf6d5: 51\r\nf6h5: 51\r\nf6h7: 51\r\nf6g8: 51\r\na6e2: 43\r\na6d3: 48\r\na6c4: 48\r\na6b5: 49\r\na6b7: 50\r\na6c8: 50\r\ng7h6: 50\r\ng7f8: 50\r\na8b8: 50\r\na8c8: 50\r\na8d8: 50\r\nh8h4: 50\r\nh8h5: 50\r\nh8h6: 50\r\nh8h7: 50\r\nh8f8: 50\r\nh8g8: 50\r\ne7c5: 50\r\ne7d6: 49\r\ne7d8: 50\r\ne7f8: 50\r\ne8d8: 50\r\ne8f8: 50\r\ne8g8: 50\r\ne8c8: 50"
    .Split("\n").ToList();
List<string> str2 =
    "e8d8: 51\r\ne8f8: 51\r\nb4a3: 51\r\nb4c3: 49\r\nb4b3: 50\r\ng6g5: 50\r\nd7d6: 50\r\nc7c6: 52\r\nc7c5: 52\r\ne6d5: 51\r\nh3g2: 48\r\nb6a4: 50\r\nb6c4: 49\r\nb6d5: 51\r\nb6c8: 51\r\nf6e4: 54\r\nf6g4: 50\r\nf6d5: 52\r\nf6h5: 52\r\nf6h7: 52\r\nf6g8: 52\r\na8b8: 51\r\na8c8: 51\r\na8d8: 51\r\nh8h7: 51\r\nh8h6: 51\r\nh8h5: 51\r\nh8h4: 51\r\nh8g8: 51\r\nh8f8: 51\r\ng7h6: 51\r\ng7f8: 51\r\na6b5: 50\r\na6c4: 49\r\na6d3: 49\r\na6e2: 44\r\na6b7: 51\r\na6c8: 51\r\ne7f8: 51\r\ne7d8: 51\r\ne7d6: 50\r\ne7c5: 51\r\ne8g8: 51\r\ne8c8: 51"
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