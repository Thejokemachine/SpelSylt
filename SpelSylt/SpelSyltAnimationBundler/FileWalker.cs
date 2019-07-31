using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace SpelSyltAnimationBundler
{
    class FileWalker
    {
        public string DirectoryPath;
        public string[] Extensions;
        private int BundleCount;
        public FileWalker()
        {
            DirectoryPath = "";
            Extensions = new string[2];
            Extensions[0] = ".json";
            Extensions[1] = ".png";
            BundleCount = 1;
        }

        public void SetDirectoryPath(string InDirPath)
        {
            DirectoryPath = InDirPath;
        }

        public void WalkFiles(ref AnimationBundleBuilder InBundler)
        {
            string[] FilePaths = Directory.GetFiles(DirectoryPath);
            HashSet<string> VisitedFiles = new HashSet<string>();

            foreach(string FilePath in FilePaths)
            {
                string FileName = Path.GetFileNameWithoutExtension(FilePath);
                if(VisitedFiles.Contains(FileName))
                {
                    continue;
                }

                string FileExtension = Path.GetExtension(FilePath);
                if(!Extensions.Contains(FileExtension))
                {
                    continue;
                }

                string PathToMatching = "";
                if(!FindMatchingFile(FileName + FileExtension, ref PathToMatching))
                {
                    continue;
                }

                string PathToBundle = DirectoryPath + FileName + ".anmbndl";
                string PathToImg = "";
                string PathToData = "";

                if(FileExtension == ".png")
                {
                    PathToImg = FilePath;
                    PathToData = PathToMatching;
                }
                else
                {
                    PathToImg = PathToMatching;
                    PathToData = FilePath;
                }

                InBundler.BundleAnimation(PathToImg, PathToData, PathToBundle);
                VisitedFiles.Add(FileName);
                Console.WriteLine("[" + BundleCount.ToString() + "] Bundled " + FileName);
            }
        }

        private bool FindMatchingFile(string InFileToMatch, ref string OutMatchingFilePath)
        {
            string ExtensionOfFileToMatch = "";
            foreach(string Extension in Extensions)
            {
                if(Extension == Path.GetExtension(InFileToMatch))
                {
                    continue;
                }

                ExtensionOfFileToMatch = Extension;
            }

            string FileToLookFor = Path.GetFileNameWithoutExtension(InFileToMatch) + ExtensionOfFileToMatch;
            if(!File.Exists(DirectoryPath + FileToLookFor))
            {
                return false;
            }

            OutMatchingFilePath = DirectoryPath + FileToLookFor;
            return true;
        }


    }
}
