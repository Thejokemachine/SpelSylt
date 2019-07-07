using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace SpelSyltEventGenerator
{
    class EventParser
    {
        public void ParseEvents(ref List<Event> InEventList, string OutFilePath)
        {
            StreamWriter OutStream = new StreamWriter(OutFilePath, false);

            WriteHeader(OutStream);

            foreach(Event E in InEventList)
            {
                WriteEvent(E, OutStream);
                OutStream.WriteLine();
            }

            OutStream.Close();
        }

        private void WriteHeader(StreamWriter InOutStream)
        {
            InOutStream.WriteLine("#pragma once");
            InOutStream.WriteLine("#include \"BaseMessage.h\" ");
        }

        private void WriteEvent(Event InEvent, StreamWriter InOutStream)
        {
            InOutStream.Write("DEFINE_MSG");

            int ParamCount = InEvent.ParamTypes.Count;

            switch(ParamCount)
            {
                case 0:
                    WriteEventZeroParam(InEvent, InOutStream);
                    break;
                case 1:
                    WriteEventOneParam(InEvent, InOutStream);
                    break;
                case 2:
                    WriteEventTwoParam(InEvent, InOutStream);
                    break;
                case 3:
                    WriteEventThreeParam(InEvent, InOutStream);
                    break;
                default:
                    Console.WriteLine("Found event " + InEvent.EventName + " with more than 3 params!");
                    break;
            }

        }

        private void WriteEventZeroParam(Event InEvent, StreamWriter InOutStream)
        {
            InOutStream.Write("(" + InEvent.EventName + ");");
        }

        private void WriteEventOneParam(Event InEvent, StreamWriter InOutStream)
        {
            InOutStream.Write("_ONEPARAM(" + InEvent.EventName + "," + XmlEventNameToCPP(InEvent.ParamTypes[0]) + ");");
        }

        private void WriteEventTwoParam(Event InEvent, StreamWriter InOutStream)
        {
            InOutStream.Write("_TWOPARAM(" + InEvent.EventName + "," + XmlEventNameToCPP(InEvent.ParamTypes[0]) + "," + XmlEventNameToCPP(InEvent.ParamTypes[1]) + ");");
        }

        private void WriteEventThreeParam(Event InEvent, StreamWriter InOutStream)
        {
            InOutStream.Write("_THREEPARAM(" + InEvent.EventName + "," + XmlEventNameToCPP(InEvent.ParamTypes[0]) + "," + XmlEventNameToCPP(InEvent.ParamTypes[1]) + "," + XmlEventNameToCPP(InEvent.ParamTypes[2]) + ");");
        }

        private string XmlEventNameToCPP(string EventName)
        {
            if(EventName == "string")
            {
                return "std::string";
            }

            return EventName;
        }
    }
}
