using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Xml;


namespace SpelSyltEventGenerator
{
    class EventReader
    {
        private XmlDocument Document;
        public bool ReadEvents(string InFile, ref List<Event> InEventList)
        {
            if(OpenFile(InFile) == false)
            {
                return false;
            }

            XmlNode RootNode = Document.FirstChild;
            ReadAllNodes(RootNode, ref InEventList);

            return true;
        }

        private void ReadAllNodes(XmlNode InNode, ref List<Event> InEventList)
        {
            for (int i = 0; i < InNode.ChildNodes.Count; ++i)
            {
                ReadAllNodes(InNode.ChildNodes[i], ref InEventList);
            }

            XmlElement NodeElement = (XmlElement)InNode;

            string EventName = "";
            if (TryReadAttribute(NodeElement, "event", ref EventName)) //We could find an event!!
            {
                InEventList.Add(new Event());
                Event ThisEvent = InEventList.Last();
                ThisEvent.EventName = EventName;

                //See if we have any params
                for(int Param = 1; Param <= 3; Param++)
                {
                    string ParamName = "p" + Param.ToString();
                    string ParamType = "";
                    if(TryReadAttribute(NodeElement, ParamName, ref ParamType))
                    {
                        ThisEvent.ParamTypes.Add(ParamType);
                    }
                }
            }
        }

        private bool TryReadAttribute(XmlElement InElement, string InAttributeName, ref string InAttributeValue)
        {
            XmlAttribute Attribute = InElement.GetAttributeNode(InAttributeName);

            if (Attribute == null)
            {
                return false;
            }

            InAttributeValue = Attribute.InnerXml;

            return true;
        }

        private bool OpenFile(string InFile)
        {
            Document = new XmlDocument();
            try
            {
                Document.Load(InFile);
            }
            catch(System.IO.FileNotFoundException)
            {
                Console.WriteLine("Could not find document " + InFile);
                return false;
            }

            return true;
        }


    }
}
