using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.WindowsAPICodePack.Dialogs;

namespace AnimationDataFileCreator
{
    static class DirectoryHelper
    {
        public static bool PromptForDirectory(ref string OutDirPath)
        {
            CommonOpenFileDialog DirectoryPicker = new CommonOpenFileDialog();
            DirectoryPicker.DefaultDirectory = Directory.GetCurrentDirectory();
            DirectoryPicker.IsFolderPicker = true;

            if(DirectoryPicker.ShowDialog() == CommonFileDialogResult.Ok)
            {
                OutDirPath = DirectoryPicker.FileName;
                OutDirPath += "\\";
                return true;
            }

            return false;
        }

        public static List<string> GetAllFilesWithExtension(string InPath, string InExtension)
        {
            List<string> CollectedList = new List<string>();

            string[] AllFiles = Directory.GetFiles(InPath);

            foreach(string FilePath in AllFiles )
            {
                if(Path.GetExtension(FilePath) == InExtension)
                {
                    string FileName = Path.GetFileName(FilePath);
                    CollectedList.Add(FileName);
                }
            }

            return CollectedList;
        }

        public static string GetFileNameNoExtension(string InFile)
        {
            return Path.GetFileNameWithoutExtension(InFile);
        }
    }
}
