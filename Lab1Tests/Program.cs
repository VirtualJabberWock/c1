using System;
using System.Diagnostics;
using System.IO;

namespace Lab1Tests
{
    class Program
    {

        static string PROJECT_NAME = "Lab1Tests";

        static void Main(string[] args)
        {
            string eax = Directory.GetCurrentDirectory();
            string[] raw = eax.Split(PROJECT_NAME);
            Console.WriteLine(raw[0]);
            string DIR = raw[0] + "\\x64\\Release\\";

            string program_path = DIR + "C_Lab1.exe";
            string input_path = eax + "\\input.txt";
            string output_path = eax + "\\output.txt";

            string[] inputs =
            {
                "0",
                "1",
                "-1",
                "64",
                "-64",
                "32767",
                "-32767",
                "2147483647",
                "-2147483648",
                //special
                "12312a",
                "123456789", // should work
                "9123456789",
                "2147999999",
                "100000000000000000000000000000000000000000000000000000000000000000000000000000000",
                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                "32i940923423890fj34598j3408tj2349hj",
                "3321334901233409231\n3492398423842\n34234238942389",
                "10000000000000000000000",
                "1000000000000000000000",
                "10000000000",
                "1000000000",
                "100000000",
                "32\0CAVE" // should work but 32
            };
            foreach (string str in inputs)
            {
                Console.WriteLine(str + ":");
                File.WriteAllText(input_path, str);
                callMain(program_path);
                Console.WriteLine("");
            }
        }

        static int callMain(string path) {
            Process exe = Process.Start(path, "input.txt output.txt");
            exe.WaitForExit();
            return exe.ExitCode;
        }
    }
}
