using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpelSyltEventGenerator
{
    class EventDuplicateRemover
    {
        public void RemoveAllDuplicates(ref List<Event> InEventList)
        {
            List<string> EncounteredEventNames = new List<string>();
            List<int> IndexesToRemove = new List<int>();

            for(int i = 0; i < InEventList.Count; ++i)
            {
                string EventName = InEventList[i].EventName;

                if(EncounteredEventNames.Contains(EventName))
                {
                    IndexesToRemove.Add(i);
                }
                else
                {
                    EncounteredEventNames.Add(EventName);
                }
            }

            for(int i = 0; i < IndexesToRemove.Count; ++i)
            {
                InEventList.RemoveAt(IndexesToRemove[i]);
            }
        }
    }
}
