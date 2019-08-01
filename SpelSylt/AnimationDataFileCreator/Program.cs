using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace AnimationDataFileCreator
{
    /*  Error code ref
     *  0 Successfully parsed and saved
     *  -1 Did not receive directory from user
     */

    class Program
    {
        static void FindAndStartBundler(string InPathToAnimFiles)
        {
            string ApplicationPath = Directory.GetCurrentDirectory();
            DirectoryInfo ToolsPath = Directory.GetParent(ApplicationPath);
            string BundlerPath = ToolsPath.FullName + "\\" + "AnimationBundler\\";

            if(File.Exists(BundlerPath + "SpelSyltAnimationBundler.exe"))
            {
                ProcessStartInfo BundlerStarter = new ProcessStartInfo();
                BundlerStarter.FileName = BundlerPath + "SpelSyltAnimationBundler.exe";
                BundlerStarter.Arguments = InPathToAnimFiles;

                try
                {
                    Process ProcessHandle = Process.Start(BundlerStarter);
                    ProcessHandle.WaitForExit();
                }
                catch
                {
                    Console.WriteLine("Failed to start Bundler");
                }

            }
            else
            {
                Console.WriteLine("Could not find bundler?");
            }
        }
        static AnimationData SetAnimationDataFlow(string InFileName)
        {
            AnimationData Data = new AnimationData();
            int FrameCount = 0;

            Console.Clear();
            Console.WriteLine("Creating animation for " + InFileName);
            Console.Write("Frame count: ");
            FrameCount = int.Parse(Console.ReadLine());

            Data.frames = new List<AnimationFrame>();

            for (int i = 0; i < FrameCount; ++i)
            {
                Console.Clear();
                AnimationFrame CreatedFrame = new AnimationFrame();

                Console.WriteLine("Creating animation for " + InFileName);
                Console.WriteLine("\nSetting frame data for frame no. " + (i + 1).ToString());

                Console.Write("X: ");
                CreatedFrame.x = int.Parse(Console.ReadLine());
                Console.Write("Y: ");
                CreatedFrame.y = int.Parse(Console.ReadLine());
                Console.Write("W: ");
                CreatedFrame.w = int.Parse(Console.ReadLine());
                Console.Write("H: ");
                CreatedFrame.h = int.Parse(Console.ReadLine());

                Console.Write("Milliseconds: ");
                int Milliseconds = int.Parse(Console.ReadLine());

                CreatedFrame.time = ((float)Milliseconds) / 1000.0f;

                Data.frames.Add(CreatedFrame);
            }

            return Data;
        }

        [STAThread]
        static int Main()
        {
            Console.WriteLine("Starting Spel Sylt Animation Data Generator");
            Console.WriteLine("Please select a directory for your image files");

            string DirectoryPath = "";
            bool DirectoryResult = DirectoryHelper.PromptForDirectory(ref DirectoryPath);

            if (!DirectoryResult)
            {
                return -1;
            }

            Menu MainMenu = new Menu();

            List<string> AllValidFiles = DirectoryHelper.GetAllFilesWithExtension(DirectoryPath, ".png");

            foreach (string FileToAddAsEntry in AllValidFiles)
            {
                MainMenu.AddMenuEntry(FileToAddAsEntry);
            }
            MainMenu.MarkFinishedAddingEntries();

            bool ShouldRun = true;
            while (ShouldRun)
            {
                Console.Clear();
                EMenuResult Result = MainMenu.ShowMenu(DirectoryPath);

                if (Result == EMenuResult.Selection)
                {
                    var SelectedEntry = MainMenu.GetSelectedEntry();
                    AnimationData CreatedAnimation = SetAnimationDataFlow(SelectedEntry);
                    AnimationDataJsonParser.Parse(DirectoryPath + DirectoryHelper.GetFileNameNoExtension(SelectedEntry) + ".json", CreatedAnimation);
                }
                else if(Result == EMenuResult.Bundle)
                {
                    FindAndStartBundler(DirectoryPath);
                }
                else if(Result == EMenuResult.Close)
                {
                    Console.WriteLine("Closing");
                    ShouldRun = false;
                }
            }

            return 0;
        }
    }
}
