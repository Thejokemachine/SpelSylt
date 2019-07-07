using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpelSyltEventGenerator
{
    class Program
    {
        static int Main(string[] args)
        {
            string ReadFile = args[0];
            string OutFile = args[1];

            List<Event> EventList = new List<Event>();

            Console.WriteLine("Starting events read from file: " + ReadFile);
            EventReader Reader = new EventReader();
            bool ReadResult = Reader.ReadEvents(ReadFile, ref EventList);

            if(!ReadResult)
            {
                Console.WriteLine("Failed to read file '" + ReadFile + "'");
                return -1;
            }

            EventDuplicateRemover DuplicateRemover = new EventDuplicateRemover();
            DuplicateRemover.RemoveAllDuplicates(ref EventList);

            Console.WriteLine("Parsing events to file: " + OutFile);
            EventParser Parser = new EventParser();
            Parser.ParseEvents(ref EventList, OutFile);

            return 0;
        }
    }
}
