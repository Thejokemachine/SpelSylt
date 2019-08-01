using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnimationDataFileCreator
{
    enum EMenuResult
    {
        Selection,
        Bundle,
        Close
    }

    class Menu
    {
        private int CurrentSelectedIndex;
        List<string> MenuEntries;

        public Menu()
        {
            CurrentSelectedIndex = 0;
            MenuEntries = new List<string>();
        }

        public void AddMenuEntry(string InEntry)
        {
            MenuEntries.Add(InEntry);
        }

        public void MarkFinishedAddingEntries()
        {
            MenuEntries.Add("**Bundle Folder**");
            MenuEntries.Add("**Close**");
        }

        public EMenuResult ShowMenu(string InWorkingDir)
        {
            Console.CursorVisible = false;

            int Selected = -1;

            while (Selected < 0)
            {
                Console.SetCursorPosition(0, 0);

                Console.WriteLine("Working in: " + InWorkingDir);
                Console.WriteLine("Select animation to create data:\n");

                for (int i = 0; i < MenuEntries.Count; ++i)
                {
                    if (i == CurrentSelectedIndex)
                    {
                        Console.Write(">");
                    }
                    Console.WriteLine("\t" + MenuEntries[i]);
                }


                switch (Console.ReadKey().Key)
                {
                    case ConsoleKey.UpArrow:
                        CurrentSelectedIndex = Math.Max(0, CurrentSelectedIndex - 1);
                        break;
                    case ConsoleKey.DownArrow:
                        CurrentSelectedIndex = Math.Min(MenuEntries.Count - 1, CurrentSelectedIndex + 1);
                        break;
                    case ConsoleKey.Enter:
                        Selected = CurrentSelectedIndex;
                        break;
                    default:
                        continue;
                }
            }

            Console.CursorVisible = true;

            if (Selected == MenuEntries.Count - 2)
            {
                return EMenuResult.Bundle;
            }
            if (Selected == MenuEntries.Count - 1)
            {
                return EMenuResult.Close;
            }

            return EMenuResult.Selection;
        }

        public string GetSelectedEntry()
        {
            return MenuEntries[CurrentSelectedIndex];
        }
    }
}
