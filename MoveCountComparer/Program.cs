
using static System.Console;
using static System.ConsoleColor;
using System.Collections.Generic;

WriteLine("Input");

//WriteLine("string 1");
//List<string> str1 = ReadLine()!.Split("\n").ToList();
//WriteLine("string 2");
//List<string> str2 = ReadLine()!.Split("\n").ToList();

List<string> str1 =
    "a7a6: 566\r\nb7b6: 621\r\nc7c6: 625\r\nd7d6: 781\r\ne7e6: 891\r\nf7f6: 547\r\ng7g6: 625\r\nh7h6: 562\r\na7a5: 624\r\nb7b5: 604\r\nc7c5: 652\r\nd7d5: 866\r\ne7e5: 835\r\nf7f5: 623\r\ng7g5: 622\r\nh7h5: 624\r\nb8a6: 591\r\nb8c6: 654\r\ng8f6: 654\r\ng8h6: 593"
    .Split("\n").ToList();
List<string> str2 =
    "f2f3: 508\r\nf2f4: 536\r\nh2h3: 509\r\nh2h4: 563\r\nc2c3: 566\r\nc2c4: 590\r\na2a3: 513\r\na2a4: 565\r\ng2g3: 563\r\ng2g4: 564\r\nd2d3: 705\r\nd2d4: 733\r\ne2e3: 805\r\ne2e4: 806\r\nb2b3: 562\r\nb2b4: 545\r\ng1f3: 590\r\ng1h3: 536\r\nb1a3: 535\r\nb1c3: 592"
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
    ForegroundColor = Red;
    WriteLine("Move counts dont match");
    WriteLine("nr 1: " + str1Count);
    WriteLine("nr 2: " + str2Count);

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