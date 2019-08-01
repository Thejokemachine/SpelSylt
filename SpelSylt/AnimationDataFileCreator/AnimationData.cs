using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Newtonsoft.Json;

namespace AnimationDataFileCreator
{
    struct AnimationFrame
    {
        public float time;
        public int x,y,w,h;
    }

    struct AnimationData
    {
        public List<AnimationFrame> frames;
    }

    static class AnimationDataJsonParser
    {
        public static void Parse(string InFullPath, AnimationData InDataToWrite)
        {
            StreamWriter WriterText = new StreamWriter(InFullPath, false);
            JsonSerializer Serializer = new JsonSerializer();
            string JsonData = JsonConvert.SerializeObject(InDataToWrite);
            WriterText.Write(JsonData);
            WriterText.Close();
        }
    }
}
