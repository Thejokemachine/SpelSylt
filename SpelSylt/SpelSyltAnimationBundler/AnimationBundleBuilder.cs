using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace SpelSyltAnimationBundler
{
    class AnimationBundleBuilder
    {
        private byte[] ImgStream;
        private byte[] DataStream;
        private FileStream BundleStream;

        readonly int HeaderByteSize = 8;
        public void BundleAnimation(string InAnimImgPath, string InAnimDataPath, string InBundleFilePath)
        {
            if(OpenStreams(InAnimImgPath, InAnimDataPath, InBundleFilePath))
            {
                try { WriteHeader((ulong)ImgStream.Length); }
                catch (ArgumentOutOfRangeException) { Console.WriteLine("Img file " + InAnimImgPath + " is too large to be bundled!"); goto OnExcept; }

                int HeaderOffset = HeaderByteSize;
                try { WriteData(ref ImgStream); }
                catch (IOException) { Console.WriteLine("Failed to write img data to Bundle"); goto OnExcept; }

                int HeaderAndImgOffset = HeaderOffset + (int)ImgStream.Length;
                try { WriteData(ref DataStream); }
                catch (IOException) { Console.WriteLine("Failed to write anim data to Bundle"); goto OnExcept; }
            }

            OnExcept:
            CloseStreams();
        }

        private bool OpenStreams(string InAnimImgPath, string InAnimDataPath, string InBundleFilePath)
        {
            ImgStream = File.ReadAllBytes(InAnimImgPath);

            DataStream = File.ReadAllBytes(InAnimDataPath);

            BundleStream = new FileStream(InBundleFilePath, FileMode.OpenOrCreate | FileMode.Truncate, FileAccess.Write);
            return true;
        }

        private void PrintFileNotFoundError(string InFilePath)
        {
            Console.WriteLine("Could not open file " + InFilePath + " - File not found?");
        }

        private void CloseStreams()
        {
            BundleStream.Close();
        }

        private void WriteHeader(ulong InAnimImgFileSize)
        {
            byte[] AsBytes = BitConverter.GetBytes(InAnimImgFileSize);

            if(AsBytes.Length > HeaderByteSize)
            {
                throw new ArgumentOutOfRangeException();
            }

            BundleStream.Write(AsBytes, 0, HeaderByteSize);
        }

        private void WriteData(ref byte[] InStreamToWriteFrom)
        {
            try { BundleStream.Write(InStreamToWriteFrom, 0, InStreamToWriteFrom.Length); }
            catch(IOException)
            {
                throw new IOException();
            }
        }

    }
}
