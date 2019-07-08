using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpelSyltAnimationBundler
{
    class Program
    {
        static void Main(string[] args)
        {
            string AnimationFolderPath = args[0];

            if(!AnimationFolderPath.EndsWith("/"))
            {
                AnimationFolderPath += "/";
            }

            AnimationBundleBuilder Bundler = new AnimationBundleBuilder();
            FileWalker Walker = new FileWalker();
            Walker.SetDirectoryPath(AnimationFolderPath);
            Walker.WalkFiles(ref Bundler);

        }
    }
}
