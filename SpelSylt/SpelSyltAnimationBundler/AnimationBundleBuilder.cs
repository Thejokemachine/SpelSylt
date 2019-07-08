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
        private FileStream ImgStream;
        private FileStream DataStream;
        private FileStream BundleStream;

        readonly int HeaderByteSize = 8;
        public void BundleAnimation(string InAnimImgPath, string InAnimDataPath, string InBundleFilePath)
        {
            if(OpenStreams(InAnimImgPath, InAnimDataPath, InBundleFilePath))
            {
                try { WriteHeader(ImgStream.Length); }
                catch (ArgumentOutOfRangeException) { Console.WriteLine("Img file " + InAnimImgPath + " is too large to be bundled!"); goto OnExcept; }

                int HeaderOffset = HeaderByteSize;
                try { WriteData(ref ImgStream, HeaderOffset); }
                catch (IOException) { Console.WriteLine("Failed to write img data to Bundle"); goto OnExcept; }

                int HeaderAndImgOffset = HeaderOffset + (int)ImgStream.Length;
                try { WriteData(ref DataStream, HeaderAndImgOffset); }
                catch (IOException) { Console.WriteLine("Failed to write anim data to Bundle"); goto OnExcept; }
            }

            OnExcept:
            CloseStreams();
        }

        private bool OpenStreams(string InAnimImgPath, string InAnimDataPath, string InBundleFilePath)
        {
            try { ImgStream = new FileStream(InAnimImgPath, FileMode.Open, FileAccess.Read); }
            catch (FileNotFoundException) { PrintFileNotFoundError(InAnimImgPath); return false; }

            try { DataStream = new FileStream(InAnimDataPath, FileMode.Open, FileAccess.Read); }
            catch(FileNotFoundException){ PrintFileNotFoundError(InAnimDataPath); return false; }

            BundleStream = new FileStream(InBundleFilePath, FileMode.OpenOrCreate, FileAccess.Write);
            return true;
        }

        private void PrintFileNotFoundError(string InFilePath)
        {
            Console.WriteLine("Could not open file " + InFilePath + " - File not found?");
        }

        private void CloseStreams()
        {
            ImgStream.Close();
            DataStream.Close();
            BundleStream.Close();
        }

        private void WriteHeader(long InAnimImgFileSize)
        {
            byte[] AsBytes = BitConverter.GetBytes(InAnimImgFileSize);

            if(AsBytes.Length > HeaderByteSize)
            {
                throw new ArgumentOutOfRangeException();
            }

            BundleStream.Write(AsBytes, 0, HeaderByteSize);
        }

        private void WriteData(ref FileStream InStreamToWriteFrom, int InOffset)
        {
            byte[] Data = new byte[InStreamToWriteFrom.Length];
            InStreamToWriteFrom.Read(Data, 0, Data.Length);

            try { BundleStream.Write(Data, 0, Data.Length); }
            catch(IOException)
            {
                throw new IOException();
            }
        }

    }
}
