
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
    "e2e3: 11427551\r\ng2g3: 4190119\r\na5a6: 16022983\r\ne2e4: 8853383\r\ng2g4: 13629805\r\nb4b1: 19481757\r\nb4b2: 12755330\r\nb4b3: 15482610\r\nb4a4: 11996400\r\nb4c4: 17400108\r\nb4d4: 15996777\r\nb4e4: 14187097\r\nb4f4: 3069955\r\na5a4: 14139786"
    .Split("\n").ToList();
List<string> str2 =
    "a4a5: 14139786\r\na4a3: 16022990\r\ng7g6: 4190119\r\ng7g5: 13629788\r\ne7e6: 11427551\r\ne7e5: 8853383\r\nb5a5: 11996400\r\nb5b6: 15482610\r\nb5b7: 12755330\r\nb5b8: 19481757\r\nb5c5: 17400108\r\nb5d5: 15996777\r\nb5e5: 14187097\r\nb5f5: 3069955"
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