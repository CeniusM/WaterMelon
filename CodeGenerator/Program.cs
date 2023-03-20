
// This is used to take in the code for a multible functions and switch out some of the code snippets with something else

string func = "void UnsafeWaterMelon::AddQueenMoves()\r\n{\r\n\tPiece pieceKey = OurQueenKey;\r\n\tint count = PieceLists[pieceKey].PieceNum;\r\n\tfor (size_t num = 0; num < count; num++)\r\n\t{\r\n\t\tSquare pos = PieceLists[pieceKey].OccupiedSquares[num];\r\n\t\tfor (size_t dir = 0; dir < 8; dir++)\r\n\t\t{\r\n\t\t\tOffset offset = offsetsIndexed[dir];\r\n\t\t\tint distance = GetDistanceToBoardInDirection(pos, dir);\r\n\t\t\tint ray = pos;\r\n\t\t\tfor (size_t i = 0; i < distance; i++)\r\n\t\t\t{\r\n\t\t\t\tray += offset;\r\n\r\n\t\t\t\tif (BitboardContains(AllPiecePosBitboard, ray))\r\n\t\t\t\t{\r\n\t\t\t\t\tif (BitboardContains(AllEnemyPosBitboard, ray))\r\n\t\t\t\t\t\tPushMoveIfPinnsAllowAndBlocksCheck(pos, ray, NoFlagCapture);\r\n\t\t\t\t\tbreak;\r\n\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t{\r\n\t\t\t\t\tPushMoveIfPinnsAllowAndBlocksCheck(pos, ray, NoFlag);\r\n\t\t\t\t}\r\n\t\t\t}\r\n\t\t}\r\n\t}\r\n}";

string Replaceble = "PushMoveIfPinnsAllowAndBlocksCheck";

Console.WriteLine(new string(func.Replace(Replaceble, "PushMove")));
Console.WriteLine(new string(func.Replace(Replaceble, "PushMoveIfPinnsAllow")));
Console.WriteLine(new string(func.Replace(Replaceble, "PushMoveIfPinnsAllowAndBlocksCheck")));
Console.WriteLine(new string(func.Replace(Replaceble, "PushMoveIfBlocksCheck")));

