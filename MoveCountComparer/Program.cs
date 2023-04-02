
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
    "a2a3: 420\r\nb2b3: 462\r\nc2c3: 462\r\nd2d3: 586\r\ne2e3: 650\r\nf2f3: 420\r\ng2g3: 462\r\nh4h5: 478\r\na2a4: 462\r\nb2b4: 463\r\nc2c4: 484\r\nd2d4: 608\r\ne2e4: 651\r\nf2f4: 442\r\ng2g4: 463\r\nb1a3: 441\r\nb1c3: 483\r\ng1f3: 483\r\ng1h3: 462\r\nh1h2: 441\r\nh1h3: 567"
    .Split("\n").ToList();
List<string> str2 =
    "a7a6: 440\r\na7a5: 484\r\nb7b6: 485\r\nb7b5: 486\r\nc7c6: 485\r\nc7c5: 508\r\nd7d6: 615\r\nd7d5: 638\r\ne7e6: 682\r\ne7e5: 683\r\nf7f6: 441\r\nf7f5: 464\r\nh7h6: 419\r\nh7h5: 442\r\ng6g5: 502\r\nb8a6: 463\r\nb8c6: 507\r\ng8f6: 507\r\ng8h6: 442\r\nf8g7: 593\r\nf8h6: 507"
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