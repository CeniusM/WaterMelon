using System.Text;

void PrintArray(int[] offsets)
{
    StringBuilder output = new StringBuilder(offsets.Length * 10);

    for (int i = 0; i < offsets.Length; i++)
    {
        output.Append(offsets[i].ToString() + ',');
    }
    output.Remove(output.Length - 1, 1);
    Console.WriteLine(output.ToString());
}


PrintArray(new int[] { 1, 124, 125, 54 });
Console.ReadLine();
