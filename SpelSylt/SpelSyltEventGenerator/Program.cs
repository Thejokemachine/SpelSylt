using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpelSyltEventGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            string ReadFile = args[0];
            string OutFile = args[1];

            List<Event> EventList = new List<Event>();

            EventReader Reader = new EventReader();
            Reader.ReadEvents(ReadFile, ref EventList);

            EventDuplicateRemover DuplicateRemover = new EventDuplicateRemover();
            DuplicateRemover.RemoveAllDuplicates(ref EventList);

            EventParser Parser = new EventParser();
            Parser.ParseEvents(ref EventList, OutFile);
        }
    }
}
