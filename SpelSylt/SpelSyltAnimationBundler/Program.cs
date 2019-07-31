using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.WindowsAPICodePack.Dialogs;
using System.IO;

namespace SpelSyltAnimationBundler
{
    class Program
    {

        static string ConfigFileName = "ssab.cfg";
        static string GetSavedPath()
        {
            string ExpectedCfgPath = Directory.GetCurrentDirectory() + "\\" + ConfigFileName;
            if (!File.Exists(ExpectedCfgPath))
            {
                return Directory.GetCurrentDirectory();
            }

            StreamReader Reader = new StreamReader(ExpectedCfgPath);
            string Path = Reader.ReadLine();
            Reader.Close();
            return Path;
        }

        static void SavePath(string InPathToSave)
        {
            string CfgPath = Directory.GetCurrentDirectory() + "\\" + ConfigFileName;
            StreamWriter Writer = new StreamWriter(CfgPath, false);
            Writer.WriteLine(InPathToSave);
            Writer.Close();
        }

        static bool GotDirectory(ref string OutDir)
        {
            CommonOpenFileDialog DirectoryPicker = new CommonOpenFileDialog();
            DirectoryPicker.Title = "Pick directory of animation files";
            DirectoryPicker.IsFolderPicker = true;
            DirectoryPicker.InitialDirectory = GetSavedPath();
            if (DirectoryPicker.ShowDialog() == CommonFileDialogResult.Ok)
            {
                OutDir = DirectoryPicker.FileName + "\\";
                SavePath(OutDir);
                return true;
            }

            OutDir = "";
            return false;
        }

        [STAThread]
        static void Main()
        {
            Console.WriteLine("Started SpelSylt Animation Bundler");
            Console.WriteLine("Awaiting Directory pick");

            string AnimationFolderPath = "";

            if (GotDirectory(ref AnimationFolderPath))
            {
                AnimationBundleBuilder Bundler = new AnimationBundleBuilder();
                FileWalker Walker = new FileWalker();
                Walker.SetDirectoryPath(AnimationFolderPath);
                Walker.WalkFiles(ref Bundler);

                Console.WriteLine("Bundle operation finished");
            }
            else
            {
                Console.WriteLine("Bundle operation failed");
            }

            Console.WriteLine("\nPress any key to end...");
            Console.ReadKey();

        }
    }
}
