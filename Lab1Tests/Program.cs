using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace Lab1Tests
{ 
    class Program
    {

        [DllImport("user32.dll")]
        public static extern int MessageBox(IntPtr hWnd, String text, String caption, int options);

        static string PROJECT_NAME = "Lab1Tests";

        //C:\Users\aqua\source\repos\C_Lab1\x64\Release\C_Lab1.exe

        static void Main(string[] args)
        {
            string eax = Directory.GetCurrentDirectory();
            string[] raw = eax.Split(PROJECT_NAME);
            string DIR = raw[0] + "\\x64\\Release\\";
            Console.Write("Full path to your '.exe' file> ");
            string program_path = Console.ReadLine();
            if (program_path == null) {
                Console.WriteLine("BAD PATH");
                return;
            }
            if (program_path.Length < 5) {
                Console.WriteLine("BAD PATH");
                return;
            }
            if (!File.Exists(program_path)) {
                Console.WriteLine("BAD PATH :: this '.exe' file don't exists");
                return;
            }
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
                "1232a879",
                "123456789", // should work
                "9123456789",
                "2147999999",
                "100000000000000000000000000000000000000000000000000000000000000000000000000000000",
                "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                "32i940923423890fj34598j3408tj2349hj",
                "3321334\n3492398423842\n34234238942389",
                "10000000000000000000000",
                "1000000000000000000000",
                "10000000000",
                "1000000000",
                "100000000"
            };
            foreach (string str in inputs)
            {
                Console.WriteLine("=-=-=-=-INPUT.TXT-=-=-=-=-\n"+ str + "\n-=-=-=-=-=-=-=-=-=-=-=EOF");
                File.WriteAllText(input_path, str);
                int a = callMain(program_path);
                if (a < -5) {
                    MessageBox(IntPtr.Zero, "Weird ErrorCode: " + a, "Error", 0);
                    return;
                }
                Console.WriteLine("");
            }
            MessageBox(IntPtr.Zero, "All tests are passed!", "Congratulations!", 0);
        }

        static int callMain(string path) {
            Process exe = Process.Start(path, "input.txt output.txt");
            exe.WaitForExit();
            return exe.ExitCode;
        }
    }
}
